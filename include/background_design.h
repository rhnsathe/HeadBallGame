//
// Created by Rohan Sathe on 4/19/21.
//
#pragma once

#include "cinder/gl/gl.h"

namespace finalproject {
 class BackgroundDesign {
  public:
   BackgroundDesign();
   void Display();
   void DrawLeftSideGoalposts();
   void DrawLeftSideSideNet();
   void DrawLeftSideTopNet();
  private:
   //size_t kXWindowSize = 1800;
   size_t rect_width = 10;
   size_t initial_position = 100;
   size_t interval = 150;

};
}
