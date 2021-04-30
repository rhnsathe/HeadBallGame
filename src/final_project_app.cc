#include "final_project_app.h"

#include "cinder/gl/gl.h"
#include "player.h"

namespace finalproject {

FinalProjectApp::FinalProjectApp() {
  ci::app::setWindowSize(kXWindowSize, kYWindowSize);
}

void FinalProjectApp::draw() {
  ci::Color background_color("dodgerblue");
  ci::gl::clear(background_color);
  if (checkIfGoalScored()) {
    player_one_ = finalproject::Player('p');
    player_two_ = finalproject::Player('o');
    ball_ = finalproject::Player(0);
  }
  if (player_one_.player_top_velocity_.x < 0) {
    player_one_.player_top_velocity_.x += 2;
    player_one_.player_bottom_velocity_.x += 2;
  }
  if (player_one_.player_top_velocity_.x > 0) {
    player_one_.player_top_velocity_.x += -2;
    player_one_.player_bottom_velocity_.x += -2;
  }
  if (player_two_.player_top_velocity_.x < 0) {
    player_two_.player_top_velocity_.x += 2;
    player_two_.player_bottom_velocity_.x += 2;
  }
  if (player_two_.player_top_velocity_.x > 0) {
    player_two_.player_top_velocity_.x += -2;
    player_two_.player_bottom_velocity_.x += -2;
  }
  ball_.checkForCollisionWithBall(player_one_, ball_);
  ball_.checkForCollisionWithBall(player_two_, ball_);
  ball_.checkForCollisionWithWall(ball_);
  //player_two_.checkForCollisionWithWall(ball_);
  backgroundDesign_.Display();
  backgroundDesign_.DrawScoreBoard(player_one_score_, player_two_score_);
  checkIfPlayerUp();
  //ball_.applyGravityToBall();
  ball_.drawBall();
  player_one_.drawPlayer();
  player_two_.drawPlayer();
}

void FinalProjectApp::update() {

}

void FinalProjectApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      player_one_.movePlayerLeft();
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      player_one_.movePlayerRight();
      break;
    case ci::app::KeyEvent::KEY_UP:
      if (player_one_.player_bottom_position_.y == 610) {
        player_one_.movePlayerUp();
        player_one_move_up_ = true;
      }
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      distanceBetweenRadii = glm::distance(player_one_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii < player_one_.getKPlayerBottomRadius() + ball_.getKPlayerTopRadius() + 30) {
        ball_.initiateSpecialLeftKick(ball_);
      }
      break;
    case ci::app::KeyEvent::KEY_a:
      player_two_.movePlayerLeft();
      break;
    case ci::app::KeyEvent::KEY_d:
      player_two_.movePlayerRight();
      break;
    case ci::app::KeyEvent::KEY_w:
      if (player_two_.player_bottom_position_.y == 610) {
        player_two_.movePlayerUp();
        player_two_move_up_ = true;
      }
      break;
    case ci::app::KeyEvent::KEY_f:
      distanceBetweenRadii2 = glm::distance(player_two_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii2 < player_two_.getKPlayerBottomRadius() + ball_.getKPlayerTopRadius() + 30) {
        ball_.initiateSpecialRightKick(ball_);
      }
  }
}

void FinalProjectApp::checkIfPlayerUp() {
  /*if (ball_.ball_velocity_.x < .15 || ball_.ball_velocity_.x > -.15) {
    ball_.ball_velocity_.x = 0.0;
  }*/
  if (ball_.ball_velocity_.x <= 0) {
    ball_.ball_velocity_.x += 0.10;
  } else if (ball_.ball_velocity_.x > 0) {
    ball_.ball_velocity_.x += -0.10;
  }
  if (player_one_move_up_ && player_one_.player_bottom_position_.y < 610) {
    player_one_.movePlayerWithGravity();
  }
  if (player_two_move_up_ && player_two_.player_bottom_position_.y < 610) {
    player_two_.movePlayerWithGravity();
  }
}

bool FinalProjectApp::checkIfGoalScored() {
  if (ball_.ball_position_.x < 150 && ball_.ball_position_.y > 322.5) {
    player_two_score_++;
    return true;
  } else if (ball_.ball_position_.x > 1800 - 150 && ball_.ball_position_.y > 322.5) {
    player_one_score_++;
    return true;
  }
  return false;
}

}  // namespace idealgas
