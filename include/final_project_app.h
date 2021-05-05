#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "background_design.h"
#include "player.h"

namespace finalproject {

using finalproject::Player;
/**
 * An app for visualizing the behavior of an ideal gas.
 */
class FinalProjectApp : public ci::app::App {
 public:
  /**
   * Default constructor.
   */
  FinalProjectApp();

  /**
   * Draws the every object that needs to be called.
   */
  void draw() override;

  /**
   * Updates frequently.
   */
  void update() override;

  /**
   * Dictates which keys can be pressed to cause action.
   * @param event - KeyEvent
   */
  void keyDown(ci::app::KeyEvent event) override;

  /**
   * Checks if player is in the air, and accordingly applies gravity.
   */
  void checkIfPlayerUp();

  /**
   * Checks if a goal has been scored.
   * @return true if goal has been scored, false if otherwise.
   */
  bool checkIfGoalScored();

  /**
   * Displays the goal animation when a goal is scored.
   */
  void displayGoalAnimation();

  /**
   * Displays the timer of the game.
   */
  void displayTimer();

  /**
   * Displays a GAME OVER sign and shows which player won.
   */
  void DisplayWinningMessage();

  /**
   * Resets players and ball to their original positions.
   */
  void ResetPlayersAndBall();

  /**
   * Decrements the temp_disablement variable to
   * better suit the CollisionWithBall() method.
   */
  void DecrementTempDisablement();

  // provided that you can see the entire UI on your screen.
  const int kXWindowSize = 1800;
  const int kYWindowSize = 900;
  const int kMargin = 100;


 private:
  /**
   * Constructor that initializes BackgroundDesign class to display BackgroundDesign.
   */
   BackgroundDesign backgroundDesign_ = BackgroundDesign();

   /**
    * Variable that temporarily disables
    * CheckCollisionWithBall() if it is greater than 0.
    */
   size_t temp_disablement_ = 0;

   /**
    * Variable that will display the goal animation if > 0.
    */
   size_t goal_animation_ = 0;

   /**
    * Variable that displays the winning message
    * if it is > 0 and < 1001.
    */
   size_t end_game_time = 0;

   /**
    * Variable that becomes true if the timer runs out and the game ends.
    */
   bool game_over_ = false;

   /**
    * Displays how much time is on the clock.
    */
   double clock_time_ = 90;

   /**
    * Variable that is necessary to determine
    * if the first player is above the ground or not.
    */
   bool player_one_move_up_ = false;

   /**
    * Variable that is necessaru to determine if the
    * second player is above ground or not.
    */
   bool player_two_move_up_ = false;

   /**
    * Holds the player_one score.
    */
   size_t player_one_score_ = 0;

   /**
    * Holds the player_two score.
    */
   size_t player_two_score_ = 0;

   /**
    * Stores the distance between radii of ball
    * and top of player.
    */
   double distanceBetweenRadii = 0.0;

   /**
    * Stores the distance between the radii of ball
    * and bottom of player.
    */
   double distanceBetweenRadii2 = 0.0;

   /**
    * Initializes an instance of a
    * Player object that creates a ball.
    */
   finalproject::Player ball_ = Player(0);

   /**
    * Initializes an instance of a Player object
    * that creates an instance of player one.
    */
   finalproject::Player player_one_ = Player('p');

   /**
    * Initializes an instance of a Player object
    * that creates an instance of player two.
    */
   finalproject::Player player_two_ = Player('o');

   /**
    * Sets the threshold for how many calls of Draw()
    * the goal animation is displayed for.
    */
   const size_t kGoalAnimationThreshold = 50;

   /**
    * Sets the threshold for how many calls of Draw()
    * the end game message is displayed for.
    */
   const size_t kEndGameTimeThreshold = 1001;

   /**
    * Sets the increment for how much time is
    * reduced for every call of Update().
    */
   const double kTimeIncrement = 0.025;

   /**
    * Sets the threshold for the
    * temp_disablement threshold.
    */
   const size_t kDisablementThreshold = 5;

   /**
    * Sets the player position
    */
    const size_t kPlayerPosition = 610;
};

}  // namespace idealgas
