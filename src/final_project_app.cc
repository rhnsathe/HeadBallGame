#include "final_project_app.h"

#include "cinder/gl/gl.h"
#include "player.h"
#include "iostream"

namespace finalproject {

FinalProjectApp::FinalProjectApp() {
  ci::app::setWindowSize(kXWindowSize, kYWindowSize);
}

void FinalProjectApp::draw() {
  // Draws background
  ci::Color background_color("dodgerblue");
  ci::gl::clear(background_color);

  //Displays the background design.
  backgroundDesign_.Display();
  backgroundDesign_.DrawScoreBoard(player_one_score_, player_two_score_);
  // Checks if game has ended and calls DisplayWinningMessage()
  // until end_game_time reaches the threshold and game_over_ becomes false.
  if (end_game_time > 0 && end_game_time < kEndGameTimeThreshold && game_over_ == true) {
    DisplayWinningMessage();
  }

  // Runs the actual game as long as end_game_time is 0.
  if (end_game_time == 0) {
    // Displays the timer/clock for the game.
    displayTimer();

    // Stops displaying goal animation if goal_animation_
    // variable reaches the threshold.
    if (goal_animation_ == kGoalAnimationThreshold) {
      goal_animation_ = 0;
    }

    // Resets players and ball after goal is scored.
    if (checkIfGoalScored()) {
      goal_animation_++;
      ResetPlayersAndBall();
    }

    // Ensures that stamina exists and players lose some velocity as they move.
    player_one_.RegulatePlayerVelocity(player_one_);
    player_two_.RegulatePlayerVelocity(player_two_);

    // Displays goal animation until goal animation reaches the kGoalAnimationThreshold
    if (goal_animation_ != 0 && goal_animation_ != kGoalAnimationThreshold) {
      displayGoalAnimation();
      goal_animation_++;
    }

    // Checks if there is a collision between player and ball,
    // and then temporarily disables the call of this method.
    if (ball_.CheckForCollisionWithBall(player_one_, ball_, temp_disablement_)) {
      temp_disablement_ = kDisablementThreshold;
    }

    // Checks if there is a collision between player and ball,
    // and then temporarily disables the call of this method.
    if (ball_.CheckForCollisionWithBall(player_two_, ball_, temp_disablement_)) {
      temp_disablement_ = kDisablementThreshold;
    }

    // Checks if ball has collided with the wall.
    ball_.CheckForCollisionWithWall(ball_);


    // Checks if player is currently in the air to
    // ensure that they do not double jump.
    checkIfPlayerUp();

    // Draws ball.
    ball_.DrawBall();

    //Draws players.
    player_one_.DrawPlayer();
    player_two_.DrawPlayer();

    // Decrements temp_disablement if > 0.
    DecrementTempDisablement();
  }
}

void FinalProjectApp::update() {
  // Reduces clock everytime update is called.
  if (clock_time_ > 0) {
    clock_time_ = clock_time_ - kTimeIncrement;
  }
  // If clock time is <= 0, then game_over_ becomes true and the end game message is displayed.
  else {
    game_over_ = true;
    end_game_time++;
  }
}

void FinalProjectApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
      // Moves player one left if left arrow key is pushed.
    case ci::app::KeyEvent::KEY_LEFT:
      player_one_.MovePlayerLeft();
      break;
      // Moves player one right if right arrow key is pushed.
    case ci::app::KeyEvent::KEY_RIGHT:
      player_one_.MovePlayerRight();
      break;
      // Moves player one up if up arrow key is pushed.
    case ci::app::KeyEvent::KEY_UP:
      // Ensures that player is on the ground before initiating the jump.
      if (player_one_.player_bottom_position_.y == kPlayerPosition) {
        player_one_.MovePlayerUp();
        player_one_move_up_ = true;
      }
      break;
      // Initiates special left kick.
    case ci::app::KeyEvent::KEY_DOWN:
      // Ensures that the distance between the ball and player radius
      // plus a threshold is below the distanceBetweenRadii.
      distanceBetweenRadii = glm::distance(player_one_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii < player_one_.GetKPlayerBottomRadius() + ball_.GetKPlayerTopRadius() + 30) {
        ball_.InitiateSpecialLeftKick(ball_);
      }
      break;
      // Moves player two left if the a key is pushed.
    case ci::app::KeyEvent::KEY_a:
      player_two_.MovePlayerLeft();
      break;
      // Moves player two right if the d key is pushed.
    case ci::app::KeyEvent::KEY_d:
      player_two_.MovePlayerRight();
      break;
      // Moves player two up if the w key is pushed.
    case ci::app::KeyEvent::KEY_w:
      // Ensures that player is on the ground before initiating the jump.
      if (player_two_.player_bottom_position_.y == kPlayerPosition) {
        player_two_.MovePlayerUp();
        player_two_move_up_ = true;
      }
      break;
      // Initiates the special right kick.
    case ci::app::KeyEvent::KEY_f:
      // Ensures that the distance between the ball and player radius
      // plus a threshold is below the distanceBetweenRadii.
      distanceBetweenRadii2 = glm::distance(player_two_.player_bottom_position_, ball_.ball_position_);
      if (distanceBetweenRadii2 < player_two_.GetKPlayerBottomRadius() + ball_.GetKPlayerTopRadius() + 30) {
        ball_.InitiateSpecialRightKick(ball_);
      }
  }
}

void FinalProjectApp::checkIfPlayerUp() {
  // Decrements the balls velocity slightly.
  double ball_increment = 0.1;
  if (ball_.ball_velocity_.x <= 0) {
    ball_.ball_velocity_.x += ball_increment;
  } else if (ball_.ball_velocity_.x > 0) {
    ball_.ball_velocity_.x += -ball_increment;
  }
  // Ensures that gravity is applied to either player.
  if (player_one_move_up_ && player_one_.player_bottom_position_.y < kPlayerPosition) {
    player_one_.MovePlayerWithGravity();
  }
  if (player_two_move_up_ && player_two_.player_bottom_position_.y < kPlayerPosition) {
    player_two_.MovePlayerWithGravity();
  }
}

bool FinalProjectApp::checkIfGoalScored() {
  // Checks if ball crosses threshold for left side goal
  double x_threshold = 150;
  double y_threshold = 322.5;
  if (ball_.ball_position_.x < x_threshold && ball_.ball_position_.y > y_threshold) {
    player_two_score_++;
    return true;
  } // Checks if ball crosses threshold for right side goal
  else if (ball_.ball_position_.x > kXWindowSize - x_threshold && ball_.ball_position_.y > y_threshold) {
    player_one_score_++;
    return true;
  }
  return false;
}

void FinalProjectApp::displayGoalAnimation() {
  // Displays goal animation in the middle of the screen.
  size_t size_and_position = 200;
  const ci::Font kLabelOneFont = ci::Font("Helvetica", size_and_position);
  std::string goal_text = "GOAL!";
  ci::gl::drawStringCentered(goal_text, vec2(kXWindowSize / 2,size_and_position),
                             "white", kLabelOneFont);
}

void FinalProjectApp::displayTimer() {
  // Displays timer at the top of the screen.
  const ci::Font kLabelOneFont = ci::Font("Helvetica", 40);
  size_t y_position = 10;
  ci::gl::drawStringCentered(std::to_string(clock_time_),
                             vec2(kXWindowSize / 2,y_position), "white", kLabelOneFont);
}

void FinalProjectApp::DisplayWinningMessage() {
  // Displays winning message
  const ci::Font kLabelOneFont = ci::Font("Helvetica", 75);
  std::string winner = "";
  // Checks which player has more points and declares them the winner.
  if (player_one_score_ > player_two_score_) {
    winner = "Orange wins!";
  } else if (player_one_score_ < player_two_score_) {
    winner = "Purple wins!";
  } else {
    winner = "It's a tie!";
  }
  end_game_time++;
  // If this is called, the game gets reset.
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
  // Resets players and ball back to original position.
  player_one_ = finalproject::Player('p');
  player_two_ = finalproject::Player('o');
  ball_ = finalproject::Player(0);
}

void FinalProjectApp::DecrementTempDisablement() {
  // Decrements temp_disablement_
  if (temp_disablement_ != 0) {
    temp_disablement_--;
  }
}
}  // namespace idealgas
