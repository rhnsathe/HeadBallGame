//
// Created by Rohan Sathe on 4/28/21.
//

#pragma once

#include "cinder/gl/gl.h"
#include "background_design.h"

using glm::vec2;

namespace finalproject {

class Player {
 public:
  /**
   * Initializes ball object.
   * @param ball - passed in Player ball object with position and velocity.
   */
  Player(int ball);

  /**
   * Initializes player based on character.
   * @param color - color character.
   */
  Player(char color);

  /**
   * Draws ball based on position.
   */
  void DrawBall();

  /**
   * Draws player based on position and color.
   */
  void DrawPlayer();

  /**
   * Moves player left.
   */
  void MovePlayerLeft();

  /**
   * Moves player right.
   */
  void MovePlayerRight();

  /**
   * Moves player up.
   */
  void MovePlayerUp();

  /**
   * Moves player down with gravity.
   */
  void MovePlayerWithGravity();

  /**
   * Creates a kick in the leftward and upward direction.
   * @param ball - passes in Player object reference with ball position and velocity.
   */
  void InitiateSpecialLeftKick(Player& ball);

  /**
   * Creates a kick in the rightward and upward direction.
   * @param ball - passes in Player object reference with ball position and velocity.
   */
  void InitiateSpecialRightKick(Player& ball);

  /**
   * Checks for collision between player and ball.
   * @param player_one - passed in Player object reference.
   * @param ball - passed in Player ball reference.
   * @param temp_disablement - passed in temporary displacement size_t.
   * @return true if collision, false if no collision.
   */
  bool CheckForCollisionWithBall(Player& player_one, Player& ball, size_t temp_disablement);

  /**
   * Checks for collision between ball and wall.
   * @param ball - Passed in Player object reference.
   */
  void CheckForCollisionWithWall(Player& ball);

  /**
   * Periodically regulates player velocity.
   * @param player_one
   * @param player_two
   */
  void RegulatePlayerVelocity(Player& player_one);

  /**
   * Returns top player radius.
   * @return top radius.
   */
  double GetKPlayerTopRadius();

  /**
   * Returns bottom player radius.
   * @return bottom radius.
   */
  double GetKPlayerBottomRadius();

  /**
   * Vector that stores the position of ball position.
   */
  glm::vec2 ball_position_;

  /**
   * Vector that stores the velocity of ball position.
   */
  glm::vec2 ball_velocity_;

  /**
   * Vector that stores the top player position.
   */
  glm::vec2 player_top_position_;

  /**
   * Vector that stores the bottom player position.
   */
  glm::vec2 player_bottom_position_;

  /**
   * Vector that stores the top player velocity.
   */
  glm::vec2 player_top_velocity_;

  /**
   * Vector that stores the bottom player velocity.
   */
  glm::vec2 player_bottom_velocity_;
 private:
  /**
   * Character that stores the color of the player.
   */
  char color_;

  /**
   * Vector that holds the left eye position of the player.
   */
  glm::vec2 player_l_eye_position_;

  /**
   * Vector that holds the right eye position of the player.
   */
  glm::vec2 player_r_eye_position_;

  /**
   * Vector that holds the left smile position of the player.
   */
  glm::vec2 player_l_smile_position_;

  /**
   * Vector that holds the right smile position of the player.
   */
  glm::vec2 player_r_smile_position_;

  /**
   * Integer that holds the increment of position and velocity.
   */
  int player_x_increment = 12;

  /**
   * Double that holds the top radius of player.
   */
  double kPlayerTopRadius = 25;

  /**
   * Double that holds the bottom radius of player.
   */
  double kPlayerBottomRadius = 50;

  /**
   * BackgroundDesign object that holds important components.
   */
  BackgroundDesign background_design_ = BackgroundDesign();
};
}
