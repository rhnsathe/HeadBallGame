//
// Created by Rohan Sathe on 4/28/21.
//

#include "player.h"

namespace finalproject {

using glm::vec2;

Player::Player(int ball) {
  ball_position_ = glm::vec2(900,500);
}

Player::Player(char color) {
  color_ = color;
  if (color_ == 'p' || color_ == 'P') {
    player_top_position_ = glm::vec2(1350, 535);
    player_bottom_position_ = glm::vec2(1350,610);
    player_l_eye_position_ = glm::vec2(1340, 525);
    player_r_eye_position_ = glm::vec2(1360, 525);
    player_l_smile_position_ = glm::vec2(1340, 545);
    player_r_smile_position_ = glm::vec2(1360, 550);
  } else {
    player_top_position_ = vec2(450,535);
    player_bottom_position_ = vec2(450,610);
    player_l_eye_position_ = glm::vec2(440, 525);
    player_r_eye_position_ = glm::vec2(460, 525);
    player_l_smile_position_ = glm::vec2(440, 545);
    player_r_smile_position_ = glm::vec2(460, 550);
  }

}

void Player::drawBall() {
  if (!(ball_position_.y > 610 - 12.5)) {
    ball_velocity_.y += 1;
  }
  ball_position_ += ball_velocity_;
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidCircle(ball_position_, kPlayerTopRadius);
}

void Player::drawPlayer() {
  if (color_ == 'p' || color_ == 'P') {
    ci::gl::color(ci::Color("purple"));
    ci::gl::drawSolidCircle(player_top_position_, kPlayerTopRadius);
    ci::gl::drawSolidCircle(player_bottom_position_, kPlayerBottomRadius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(player_l_eye_position_, 1.5);
    ci::gl::drawSolidCircle(player_r_eye_position_, 1.5);
    ci::gl::drawLine(player_l_smile_position_, player_r_smile_position_);
  } else {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(player_top_position_, kPlayerTopRadius);
    ci::gl::drawSolidCircle(player_bottom_position_, kPlayerBottomRadius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(player_l_eye_position_, 1.5);
    ci::gl::drawSolidCircle(player_r_eye_position_, 1.5);
    ci::gl::drawLine(player_l_smile_position_, player_r_smile_position_);
  }
}

void Player::initiateSpecialLeftKick(Player& ball) {
  ball.ball_velocity_ += glm::vec2(-30,-20);
}

void Player::initiateSpecialRightKick(Player& ball) {
  ball_velocity_ += glm::vec2(30,-20);
}

void Player::movePlayerLeft() {
  player_top_position_ += glm::vec2(-10,0);
  player_bottom_position_ += glm::vec2(-10,0);
  player_l_eye_position_ += glm::vec2(-10,0);
  player_r_eye_position_ += glm::vec2(-10,0);
  player_l_smile_position_ += glm::vec2(-10,0);
  player_r_smile_position_ += glm::vec2(-10,0);
  player_top_velocity_ +=  glm::vec2(-10,0);
  player_bottom_velocity_ +=  glm::vec2(-10,0);
}

void Player::movePlayerRight() {
  player_top_position_ += glm::vec2(10,0);
  player_bottom_position_ += glm::vec2(10,0);
  player_l_eye_position_ += glm::vec2(10,0);
  player_r_eye_position_ += glm::vec2(10,0);
  player_l_smile_position_ += glm::vec2(10,0);
  player_r_smile_position_ += glm::vec2(10,0);
  player_top_velocity_ +=  glm::vec2(10,0);
  player_bottom_velocity_ +=  glm::vec2(10,0);
}

void Player::movePlayerUp() {
  player_top_position_ += glm::vec2(0,-150);
  player_bottom_position_ += glm::vec2(0,-150);
  player_l_eye_position_ += glm::vec2(0,-150);
  player_r_eye_position_ += glm::vec2(0,-150);
  player_l_smile_position_ += glm::vec2(0,-150);
  player_r_smile_position_ += glm::vec2(0,-150);
  player_top_velocity_ +=  glm::vec2(0,-10);
  player_bottom_velocity_ +=  glm::vec2(0,-10);
}

void Player::movePlayerWithGravity() {
  player_top_position_ += glm::vec2(0,7.5);
  player_bottom_position_ += glm::vec2(0,7.5);
  player_l_eye_position_ += glm::vec2(0,7.5);
  player_r_eye_position_ += glm::vec2(0,7.5);
  player_l_smile_position_ += glm::vec2(0,7.5);
  player_r_smile_position_ += glm::vec2(0,7.5);
  player_top_velocity_ +=  glm::vec2(0,0.5);
  player_bottom_velocity_ +=  glm::vec2(0,0.5);
}

void Player::checkForCollisionWithBall(Player& player_one, Player& ball) {
  double distanceBetweenRadii1 = glm::distance(player_one.player_top_position_, ball.ball_position_);
  double distanceBetweenRadii2 = glm::distance(player_one.player_bottom_position_, ball.ball_position_);
  if (distanceBetweenRadii1 < player_one.kPlayerTopRadius + ball.kPlayerTopRadius) {
    if ((ball.ball_velocity_.x <= 0 && player_one.player_top_velocity_.x < 0)
        || (ball.ball_velocity_.x >= 0 && player_one.player_top_velocity_.x > 0)) {
      ball.ball_velocity_ += player_one.player_top_velocity_;
    } else {
      ball.ball_velocity_ = glm::vec2(-1,1) * ball.ball_velocity_;
    }
  }
  if (distanceBetweenRadii2 < player_one.kPlayerBottomRadius + ball.kPlayerTopRadius) {
    if ((ball.ball_velocity_.x <= 0 && player_one.player_bottom_velocity_.x < 0)
        || (ball.ball_velocity_.x >= 0 && player_one.player_bottom_velocity_.x > 0)) {
      ball.ball_velocity_ += player_one.player_bottom_velocity_;
    } else {
      ball.ball_velocity_ = glm::vec2(-1,1) * ball.ball_velocity_;
    }
  }
}

void Player::checkForCollisionWithWall(Player& ball) {
  //size_t value = 0;
  // Checks potential collision with right vertical wall.
  if (ball.ball_position_.x + ball.kPlayerTopRadius > 1800) {
    // Ensures that the particle has a positive x velocity.
    if (ball.ball_velocity_.x >= 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
      //ball.ball_position_ += ball.ball_velocity_;
    }
    // Checks potential collision with left vertical wall.
  }
  if (ball.ball_position_.x < ball.kPlayerTopRadius) {
    // Ensures that the particle has a negative x velocity.
    if (ball.ball_velocity_.x < 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
      //ball.ball_position_ += ball.ball_velocity_;
    }
    // Checks potential collision with top horizontal wall.
  }
  if (ball.ball_position_.y + ball.kPlayerTopRadius > 625 - 12.5) {
    // Ensures that the particle has a positive y velocity.
    if (ball.ball_velocity_.y > 0) {
      ball.ball_velocity_ = glm::vec2(1, -1) * ball.ball_velocity_;
      //ball.ball_position_ += ball.ball_velocity_;
    }
    // Checks potential collision with bottom horizontal wall.
  }
  if (ball.ball_position_.y < ball.kPlayerTopRadius) {
    // Ensures that the particle has a negative y velocity.
    if (ball.ball_velocity_.y < 0) {
      ball.ball_velocity_ = glm::vec2(1, -1) * ball.ball_velocity_;
      //ball.ball_position_ += ball.ball_velocity_;
    }
  }
}

void Player::applyGravityToBall() {
  if (ball_position_.y < 610 - 10) {
    ball_position_.y += 10;
  }
}

double Player::getKPlayerTopRadius() {
  return kPlayerTopRadius;
}

double Player::getKPlayerBottomRadius() {
  return kPlayerBottomRadius;
}

}