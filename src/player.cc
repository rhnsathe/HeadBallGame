//
// Created by Rohan Sathe on 4/28/21.
//

#include "player.h"

namespace finalproject {

using glm::vec2;

Player::Player(int ball) {
  size_t x_ball_position = 900;
  size_t y_ball_position = 500;
  ball_position_ = glm::vec2(x_ball_position,y_ball_position);
}

Player::Player(char color) {
  // Initializes color of player
  // based on what is passed in.
  color_ = color;
  size_t purple_position = background_design_.getKXWindowSize() / 2;
  size_t purple_x_position = purple_position / 2;
  size_t increment = 10;
  size_t y_position = 660;
  size_t y_increment = 75;
  size_t smile_increment = 5;

  // Initializes a purple player in the correct positions.
  if (color_ == 'p' || color_ == 'P') {
    player_top_position_ = glm::vec2(purple_position + purple_x_position,
                                     y_position - kPlayerBottomRadius - y_increment);
    player_bottom_position_ = glm::vec2(purple_position + purple_x_position,
                                        y_position - kPlayerBottomRadius);
    player_l_eye_position_ = glm::vec2(purple_position + purple_x_position - increment,
                                       y_position - kPlayerBottomRadius - y_increment - increment);
    player_r_eye_position_ = glm::vec2(purple_position + purple_x_position + increment,
                                       y_position - kPlayerBottomRadius - y_increment - increment);
    player_l_smile_position_ = glm::vec2(purple_position + purple_x_position - increment,
                                         y_position - kPlayerBottomRadius - y_increment + increment);
    player_r_smile_position_ = glm::vec2(purple_position + purple_x_position + increment,
                                         y_position - kPlayerBottomRadius - y_increment + increment + smile_increment);
  }
  // Initializes an orange player in the correct positions.
  else {
    player_top_position_ = glm::vec2(purple_position - purple_x_position,
                                y_position - kPlayerBottomRadius - y_increment);
    player_bottom_position_ = glm::vec2(purple_position - purple_x_position,
                                   y_position - kPlayerBottomRadius);
    player_l_eye_position_ = glm::vec2(purple_position - purple_x_position - increment,
                                       y_position - kPlayerBottomRadius - y_increment - increment);
    player_r_eye_position_ = glm::vec2(purple_position - purple_x_position + increment,
                                       y_position - kPlayerBottomRadius - y_increment - increment);
    player_l_smile_position_ = glm::vec2(purple_position - purple_x_position - increment,
                                         y_position - kPlayerBottomRadius - y_increment + increment);
    player_r_smile_position_ = glm::vec2(purple_position - purple_x_position + increment,
                                         y_position - kPlayerBottomRadius - y_increment + increment + smile_increment);
  }
}

void Player::DrawBall() {
  // Ensures that there is some level of gravity acting on the ball.
  double y_threshhold = 660 - kPlayerBottomRadius - (kPlayerTopRadius/2);
  if (!(ball_position_.y > y_threshhold)) {
    ball_velocity_.y += 1;
  }
  // Changes the balls position as a result of its velocity.
  ball_position_ += ball_velocity_;

  // Draws the ball.
  ci::gl::color(ci::Color("white"));
  ci::gl::drawSolidCircle(ball_position_, kPlayerTopRadius);
}

void Player::DrawPlayer() {
  double eye_radius = 2.5;
  // Draws the purple player in the correct positions,
  // and it is called in the Draw() method, so it updates extremely frequently.
  if (color_ == 'p' || color_ == 'P') {
    ci::gl::color(ci::Color("purple"));
    ci::gl::drawSolidCircle(player_top_position_, kPlayerTopRadius);
    ci::gl::drawSolidCircle(player_bottom_position_, kPlayerBottomRadius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(player_l_eye_position_, eye_radius);
    ci::gl::drawSolidCircle(player_r_eye_position_, eye_radius);
    ci::gl::drawLine(player_l_smile_position_, player_r_smile_position_);
  }
  // Draws the purple player in the correct positions,
  // and it is called in the Draw() method, so it updates extremely frequently.
  else {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(player_top_position_, kPlayerTopRadius);
    ci::gl::drawSolidCircle(player_bottom_position_, kPlayerBottomRadius);
    ci::gl::color(ci::Color("black"));
    ci::gl::drawSolidCircle(player_l_eye_position_, eye_radius);
    ci::gl::drawSolidCircle(player_r_eye_position_, eye_radius);
    ci::gl::drawLine(player_l_smile_position_, player_r_smile_position_);
  }
}

void Player::InitiateSpecialLeftKick(Player& ball) {
  // Creates a kick in the leftward direction so
  // as to kick the ball in the air.
  int special_x = -30;
  int special_y = -20;
  ball.ball_velocity_ += glm::vec2(special_x,special_y);
}

void Player::InitiateSpecialRightKick(Player& ball) {
  // Creates a kick in the rightward direction so
  // as to kick the ball in the air.
  int special_x = 30;
  int special_y = -20;
  ball.ball_velocity_ += glm::vec2(special_x,special_y);
}

void Player::MovePlayerLeft() {
  // Appropriately changes the player's position
  // and velocity if the user seeks to move left.
  player_top_position_ += glm::vec2(-player_x_increment,0);
  player_bottom_position_ += glm::vec2(-player_x_increment,0);
  player_l_eye_position_ += glm::vec2(-player_x_increment,0);
  player_r_eye_position_ += glm::vec2(-player_x_increment,0);
  player_l_smile_position_ += glm::vec2(-player_x_increment,0);
  player_r_smile_position_ += glm::vec2(-player_x_increment,0);
  player_top_velocity_ +=  glm::vec2(-player_x_increment,0);
  player_bottom_velocity_ +=  glm::vec2(-player_x_increment,0);
}

void Player::MovePlayerRight() {
  // Appropriately changes the player's position
  // and velocity if the user seeks to move right.
  player_top_position_ += glm::vec2(player_x_increment,0);
  player_bottom_position_ += glm::vec2(player_x_increment,0);
  player_l_eye_position_ += glm::vec2(player_x_increment,0);
  player_r_eye_position_ += glm::vec2(player_x_increment,0);
  player_l_smile_position_ += glm::vec2(player_x_increment,0);
  player_r_smile_position_ += glm::vec2(player_x_increment,0);
  player_top_velocity_ +=  glm::vec2(player_x_increment,0);
  player_bottom_velocity_ +=  glm::vec2(player_x_increment,0);
}

void Player::MovePlayerUp() {
  // Appropriately changes the player's position
  // and velocity if the user seeks to move up.
  double y_increase = -150;
  player_top_position_ += glm::vec2(0,y_increase);
  player_bottom_position_ += glm::vec2(0,y_increase);
  player_l_eye_position_ += glm::vec2(0,y_increase);
  player_r_eye_position_ += glm::vec2(0,y_increase);
  player_l_smile_position_ += glm::vec2(0,y_increase);
  player_r_smile_position_ += glm::vec2(0,y_increase);
  player_top_velocity_ +=  glm::vec2(0,-player_x_increment);
  player_bottom_velocity_ +=  glm::vec2(0,-player_x_increment);
}

void Player::MovePlayerWithGravity() {
  // Appropriately changes the player's position
  // and velocity when the user is coming down
  // from being in the air.
  double y_decrease = 7.5;
  double y_velo_decrease = 0.5;
  player_top_position_ += glm::vec2(0,y_decrease);
  player_bottom_position_ += glm::vec2(0,y_decrease);
  player_l_eye_position_ += glm::vec2(0,y_decrease);
  player_r_eye_position_ += glm::vec2(0,y_decrease);
  player_l_smile_position_ += glm::vec2(0,y_decrease);
  player_r_smile_position_ += glm::vec2(0,y_decrease);
  player_top_velocity_ +=  glm::vec2(0,y_velo_decrease);
  player_bottom_velocity_ +=  glm::vec2(0,y_velo_decrease);
}

bool Player::CheckForCollisionWithBall(Player& player_one, Player& ball, size_t temp_disablement) {
  // If the there is a call to the CheckForCollisionWithBall() method and the temp_disablement is > 0,
  // then the ball is still being hit so the method is not able to be called temporarily.
  if (temp_disablement != 0) {
    return false;
  }
  // Measures distance between ball radius and player top radius.
  double distanceBetweenRadii1 = glm::distance(player_one.player_top_position_, ball.ball_position_);

  // Measures distance between ball radius and player bottom radius.
  double distanceBetweenRadii2 = glm::distance(player_one.player_bottom_position_, ball.ball_position_);

  // Checks if the distance between the radii is smaller than the sum of their respective radii
  // - this would indicate a collision
  if (distanceBetweenRadii1 < player_one.kPlayerTopRadius + ball.kPlayerTopRadius) {
    // If the ball velocity and player velocity are in the same direction,
    // then the ball takes the velocity of the player.
    if ((ball.ball_velocity_.x <= 0 && player_one.player_top_velocity_.x < 0)
        || (ball.ball_velocity_.x >= 0 && player_one.player_top_velocity_.x > 0)) {
      ball.ball_velocity_ += player_one.player_top_velocity_;
      return true;
    } // If the ball velocity and player velocity are in the opposite direction,
      // then the ball simply reverses its own velocity.
    else {
      ball.ball_velocity_ = glm::vec2(-1,1) * ball.ball_velocity_;
      return true;
    }
  }
  // Checks if the distance between the radii is smaller than the sum of their respective radii
  // - this would indicate a collision
  else if (distanceBetweenRadii2 < player_one.kPlayerBottomRadius + ball.kPlayerTopRadius) {
    // Checks if the distance between the radii is smaller than the sum of their respective radii
    // - this would indicate a collision
    if ((ball.ball_velocity_.x <= 0 && player_one.player_bottom_velocity_.x < 0)
        || (ball.ball_velocity_.x >= 0 && player_one.player_bottom_velocity_.x > 0)) {
      ball.ball_velocity_ += player_one.player_bottom_velocity_;
      return true;
    }
    // If the ball velocity and player velocity are in the opposite direction,
    // then the ball simply reverses its own velocity.
    else {
      ball.ball_velocity_ = glm::vec2(-1,1) * ball.ball_velocity_;
      return true;
    }
  }
  return false;
}

void Player::CheckForCollisionWithWall(Player& ball) {
  size_t x_window_width = 1800;
  // Checks potential collision with right vertical wall.
  if (ball.ball_position_.x + ball.kPlayerTopRadius > x_window_width) {
    // Ensures that the particle has a positive x velocity.
    if (ball.ball_velocity_.x >= 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
    }
  }

  // Checks potential collision with left vertical wall.
  if (ball.ball_position_.x < ball.kPlayerTopRadius) {
    // Ensures that the particle has a negative x velocity.
    if (ball.ball_velocity_.x < 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
    }
  }

  size_t y_window_width = 625;
  // Checks potential collision with bottom horizontal wall.
  if (ball.ball_position_.y + ball.kPlayerTopRadius > y_window_width - kPlayerTopRadius/2) {
    // Ensures that the particle has a positive y velocity.
    if (ball.ball_velocity_.y > 0) {
      ball.ball_velocity_ = glm::vec2(1, -1) * ball.ball_velocity_;
    }
  }

  // Checks potential collision with top horizontal wall.
  if (ball.ball_position_.y < ball.kPlayerTopRadius) {
    // Ensures that the particle has a negative y velocity.
    if (ball.ball_velocity_.y < 0) {
      ball.ball_velocity_ = glm::vec2(1, -1) * ball.ball_velocity_;
    }
  }
  size_t lower_y = 100;
  size_t upper_y = 310;
  size_t left_left_x = 150;
  size_t left_right_x = 250;
  size_t right_left_x = 1550;
  size_t right_right_x = 1650;

  // Checks for collision with left crossbar
  if (ball.ball_position_.y > lower_y && ball.ball_position_.y < upper_y
      && ball.ball_position_.x > left_left_x && ball.ball_position_.x < left_right_x) {
    if (ball.ball_velocity_.x < 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
    }
  }

  // Checks for collision with right crossbar
  if (ball.ball_position_.y > lower_y && ball.ball_position_.y < upper_y
          && ball.ball_position_.x > right_left_x && ball.ball_position_.x < right_right_x) {
    if (ball.ball_velocity_.x > 0) {
      ball.ball_velocity_ = glm::vec2(-1, 1) * ball.ball_velocity_;
    }
  }
}

void Player::RegulatePlayerVelocity(Player& player_one) {
  // Steadily moves player velocity
  // closer to 0 every time it is called.
  double velocity_increment = 1.5;
  if (player_one.player_top_velocity_.x < 0) {
    player_one.player_top_velocity_.x += velocity_increment;
    player_one.player_bottom_velocity_.x += velocity_increment;
  }
  if (player_one.player_top_velocity_.x > 0) {
    player_one.player_top_velocity_.x += -velocity_increment;
    player_one.player_bottom_velocity_.x += -velocity_increment;
  }
}

double Player::GetKPlayerTopRadius() {
  return kPlayerTopRadius;
}

double Player::GetKPlayerBottomRadius() {
  return kPlayerBottomRadius;
}

}