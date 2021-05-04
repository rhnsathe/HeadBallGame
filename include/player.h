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
  Player(int ball);
  Player(char color);
  void drawBall();
  void drawPlayer();
  void movePlayerLeft();
  void movePlayerRight();
  void movePlayerUp();
  void movePlayerWithGravity();
  void applyGravityToBall();
  void initiateSpecialLeftKick(Player& ball);
  void initiateSpecialRightKick(Player& ball);
  bool checkForCollisionWithBall(Player& player_one, Player& ball, size_t temp_disablement);
  void checkForCollisionWithWall(Player& ball);
  double getKPlayerTopRadius();
  double getKPlayerBottomRadius();
  glm::vec2 ball_position_;
  glm::vec2 ball_velocity_;
  glm::vec2 player_top_position_;
  glm::vec2 player_bottom_position_;
  glm::vec2 player_top_velocity_;
  glm::vec2 player_bottom_velocity_;
 private:
  char color_;
  glm::vec2 player_l_eye_position_;
  glm::vec2 player_r_eye_position_;
  glm::vec2 player_l_smile_position_;
  glm::vec2 player_r_smile_position_;
  int player_x_increment = 12;
  double kPlayerTopRadius = 25;
  double kPlayerBottomRadius = 50;
  BackgroundDesign background_design_ = BackgroundDesign();
};
}
