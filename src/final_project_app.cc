#include "final_project_app.h"

#include "cinder/gl/gl.h"
#include "player.h"
#include "iostream"

namespace finalproject {

FinalProjectApp::FinalProjectApp() {
  ci::app::setWindowSize(kXWindowSize, kYWindowSize);
}

void FinalProjectApp::draw() {
  ci::Color background_color("dodgerblue");
  ci::gl::clear(background_color);
  if (end_game_time > 0 && end_game_time < kEndGameTimeThreshold && game_over_ == true) {
    DisplayWinningMessage();
  }
  if (end_game_time == 0) {
    displayTimer();
    if (goal_animation_ == kGoalAnimationThreshold) {
      goal_animation_ = 0;
    }
    if (checkIfGoalScored()) {
      goal_animation_++;
      ResetPlayersAndBall();
    }
    player_one_.RegulatePlayerVelocity(player_one_);
    player_two_.RegulatePlayerVelocity(player_two_);
    if (goal_animation_ != 0 && goal_animation_ != kGoalAnimationThreshold) {
      displayGoalAnimation();
      goal_animation_++;
    }
    if (ball_.CheckForCollisionWithBall(player_one_, ball_, temp_disablement_)) {
      temp_disablement_ = kDisablementThreshold;
    }
    if (ball_.CheckForCollisionWithBall(player_two_, ball_, temp_disablement_)) {
      temp_disablement_ = kDisablementThreshold;
    }
    ball_.CheckForCollisionWithWall(ball_);
    backgroundDesign_.Display();
    backgroundDesign_.DrawScoreBoard(player_one_score_, player_two_score_);
    checkIfPlayerUp();
    ball_.DrawBall();
    player_one_.DrawPlayer();
    player_two_.DrawPlayer();
    DecrementTempDisablement();
  }
}

void FinalProjectApp::update() {
  if (clock_time_ > 0) {
    clock_time_ = clock_time_ - kTimeIncrement;
  } else {
    game_over_ = true;
    end_game_time++;
  }
}

void FinalProjectApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_LEFT:
      player_one_.MovePlayerLeft();
      break;
    case ci::app::KeyEvent::KEY_RIGHT:
      player_one_.MovePlayerRight();
      break;
    case ci::app::KeyEvent::KEY_UP:
      if (player_one_.player_bottom_position_.y == kPlayerPosition) {
        player_one_.MovePlayerUp();
        player_one_move_up_ = true;
      }
      break;
    case ci::app::KeyEvent::KEY_DOWN:
      distanceBetweenRadii = glm::distance(player_one_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii < player_one_.GetKPlayerBottomRadius() + ball_.GetKPlayerTopRadius() + 30) {
        ball_.InitiateSpecialLeftKick(ball_);
      }
      break;
    case ci::app::KeyEvent::KEY_a:
      player_two_.MovePlayerLeft();
      break;
    case ci::app::KeyEvent::KEY_d:
      player_two_.MovePlayerRight();
      break;
    case ci::app::KeyEvent::KEY_w:
      if (player_two_.player_bottom_position_.y == kPlayerPosition) {
        player_two_.MovePlayerUp();
        player_two_move_up_ = true;
      }
      break;
    case ci::app::KeyEvent::KEY_f:
      distanceBetweenRadii2 = glm::distance(player_two_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii2 < player_two_.GetKPlayerBottomRadius() + ball_.GetKPlayerTopRadius() + 30) {
        ball_.InitiateSpecialRightKick(ball_);
      }
  }
}

void FinalProjectApp::checkIfPlayerUp() {
  if (ball_.ball_velocity_.x <= 0) {
    ball_.ball_velocity_.x += 0.10;
  } else if (ball_.ball_velocity_.x > 0) {
    ball_.ball_velocity_.x += -0.10;
  }
  if (player_one_move_up_ && player_one_.player_bottom_position_.y < 610) {
    player_one_.MovePlayerWithGravity();
  }
  if (player_two_move_up_ && player_two_.player_bottom_position_.y < 610) {
    player_two_.MovePlayerWithGravity();
  }
}

bool FinalProjectApp::checkIfGoalScored() {
  double x_threshold = 150;
  double y_threshold = 322.5;
  if (ball_.ball_position_.x < x_threshold && ball_.ball_position_.y > y_threshold) {
    player_two_score_++;
    return true;
  } else if (ball_.ball_position_.x > kXWindowSize - x_threshold && ball_.ball_position_.y > y_threshold) {
    player_one_score_++;
    return true;
  }
  return false;
}

void FinalProjectApp::displayGoalAnimation() {
  size_t size_and_position = 200;
  const ci::Font kLabelOneFont = ci::Font("Helvetica", size_and_position);
  std::string goal_text = "GOAL!";
  ci::gl::drawStringCentered(goal_text, vec2(kXWindowSize / 2,size_and_position),
                             "white", kLabelOneFont);
}

void FinalProjectApp::displayTimer() {
  const ci::Font kLabelOneFont = ci::Font("Helvetica", 40);
  size_t y_position = 10;
  ci::gl::drawStringCentered(std::to_string(clock_time_),
                             vec2(kXWindowSize / 2,y_position), "white", kLabelOneFont);
}

void FinalProjectApp::DisplayWinningMessage() {
  const ci::Font kLabelOneFont = ci::Font("Helvetica", 75);
  std::string winner = "";
  if (player_one_score_ > player_two_score_) {
    winner = "Orange wins!";
  } else if (player_one_score_ < player_two_score_) {
    winner = "Purple wins!";
  } else {
    winner = "It's a tie!";
  }
  end_game_time++;
  if (end_game_time == kEndGameTimeThreshold - 1) {
    player_one_ = finalproject::Player('p');
    player_two_ = finalproject::Player('o');
    ball_ = finalproject::Player(0);
    game_over_ = false;
    end_game_time = 0;
    clock_time_ = 90;
    player_one_score_ = 0;
    player_two_score_ = 0;
  } else {
    std::string end_game_text = "GAME OVER!";
    ci::gl::drawStringCentered(end_game_text, vec2(kXWindowSize / 2,kMargin), "white", kLabelOneFont);
    ci::gl::drawStringCentered(winner, vec2(kXWindowSize / 2,kMargin * 2), "white", kLabelOneFont);
  }
}

void FinalProjectApp::ResetPlayersAndBall() {
  player_one_ = finalproject::Player('p');
  player_two_ = finalproject::Player('o');
  ball_ = finalproject::Player(0);
}

void FinalProjectApp::DecrementTempDisablement() {
  if (temp_disablement_ != 0) {
    temp_disablement_--;
  }
}


}  // namespace idealgas
