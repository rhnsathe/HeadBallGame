//
// Created by Rohan Sathe on 4/19/21.
//
#pragma once

#include "cinder/gl/gl.h"

namespace finalproject {
 class BackgroundDesign {
  public:
   /**
    * Default constructor for BackgroundDesign.
    */
   BackgroundDesign();

   /**
    * Displays the field.
    */
   void Display();

   /**
    * Draws the left side goal posts.
    */
   void DrawLeftSideGoalposts();

   /**
    * Draws the left side side nets.
    */
   void DrawLeftSideSideNet();

   /**
    * Draws the left side top nets.
    */
   void DrawLeftSideTopNet();

   /**
    * Draws the soccer field.
    */
   void DrawField();

   /**
    * Draws the right side goal posts.
    */
   void DrawRightSideGoalposts();

   /**
    * Draws the right side side nets.
    */
   void DrawRightSideSideNet();

   /**
    * Draws the right side top nets.
    */
   void DrawRightSideTopNet();

   /**
    * Draws scoreboard.
    */
   void DrawScoreBoard(size_t player_one_score, size_t player_two_score);

   /**
    * Gets the window size.
    * @return window size.
    */
   size_t getKXWindowSize();

   ci::Rectf left_rotated_rectangle_;

   ci::Rectf right_rotated_rectangle_;
  private:
   /**
    * X length of Window.
    */
   size_t kXWindowSize = 1800;

   /**
    * Goalpost width.
    */
   size_t rect_width = 10;

   /**
    * Initial position.
    */
   size_t initial_position = 100;

   /**
    * Interval between two goalposts.
    */
   size_t interval = 150;

};
}
