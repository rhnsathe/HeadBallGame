//
// Created by Rohan Sathe on 4/19/21.
//

#include "background_design.h"
#include "final_project_app.h"
#include <math.h>

namespace finalproject {

using glm::vec2;

BackgroundDesign::BackgroundDesign() {
}

void BackgroundDesign::Display() {
  DrawLeftSideGoalposts();
  DrawLeftSideSideNet();
  DrawLeftSideTopNet();

  // Draws Field
  ci::gl::color(ci::Color("green"));
  ci::gl::drawSolidTriangle(vec2(320,460), vec2(320,760), vec2(170, 760));
  ci::gl::drawSolidRect(ci::Rectf(vec2(320,460), vec2(1480, 760)));
  ci::gl::drawSolidTriangle(vec2(1480,460), vec2(1480,760), vec2(1630, 760));

  ci::Color postColorRight("white");
  ci::gl::color(postColorRight);
  //finalproject::FinalProjectApp finalProjectApp;
  ci::gl::drawSolidRect(ci::Rectf(vec2(1800 - 250, 100), vec2(1800, 110)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(1800 - 150, 300), vec2(1800, 310)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(1800 - 150, 700), vec2(1800, 710)));
  ci::gl::pushModelMatrix();
  ci::gl::translate(1800-250,110);
  double turn_value_2 = atan(200/100);
  ci::gl::rotate((1/2)*M_PI + turn_value_2);
  ci::gl::drawSolidRect(ci::Rectf(vec2(0,0), vec2(223.607,10)));
  ci::gl::popModelMatrix();
  ci::gl::drawSolidRect(ci::Rectf(vec2(1800 - 250 - 10,100), vec2(1800 - 250,510)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(1800 - 150 -10,300), vec2(1800 - 150,710)));

  // Draw right side net
  size_t rsp= 1800-150;
  ci::gl::drawLine(vec2(rsp,310), vec2(rsp,710));
  //ci::gl::drawLine(vec2(15,310), vec2(15,710));
  ci::gl::drawLine(vec2(rsp + 28,310), vec2(rsp + 28,710));
  //ci::gl::drawLine(vec2(45,310), vec2(45,710));
  ci::gl::drawLine(vec2(rsp + 56,310), vec2(rsp + 56,710));
  //ci::gl::drawLine(vec2(75,310), vec2(75,710));
  ci::gl::drawLine(vec2(rsp + 84,310), vec2(rsp + 84,710));
  //ci::gl::drawLine(vec2(105,310), vec2(105,710));
  ci::gl::drawLine(vec2(rsp + 112,310), vec2(rsp + 112,710));
  //ci::gl::drawLine(vec2(135,310), vec2(135,710));
  ci::gl::drawLine(vec2(rsp + 140,310), vec2(rsp + 140,710));

  //Draws right side of the net
  ci::gl::drawLine(vec2(rsp,310 + 400/6), vec2(1800,310 + 400/6));
  ci::gl::drawLine(vec2(rsp,310 + (400/6) * 2), vec2(1800,310 + (400/6) * 2));
  ci::gl::drawLine(vec2(rsp,310 + (400/6) * 3), vec2(1800,310 + (400/6) * 3));
  ci::gl::drawLine(vec2(rsp,310 + (400/6) * 4), vec2(1800,310 + (400/6) * 4));
  ci::gl::drawLine(vec2(rsp,310 + (400/6) * 5), vec2(1800,310 + (400/6) * 5));

  int tsp1 = 1800 - 240;
  int tsp2 = 1800 - 140;
  // Draws the top of the net
  ci::gl::drawLine(vec2(tsp1 + 28*8,110), vec2(tsp2 + 28*8, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*7,110), vec2(tsp2 + 28*7, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*6,110), vec2(tsp2 + 28*6, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*5,110), vec2(tsp2 + 28*5, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*4,110), vec2(tsp2 + 28*4, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*3,110), vec2(tsp2 + 28*3, 310));
  ci::gl::drawLine(vec2(tsp1 + 28*2,110), vec2(tsp2 + 28*2, 310));
  ci::gl::drawLine(vec2(tsp1 + 28,110), vec2(tsp2 + 28, 310));
  ci::gl::drawLine(vec2(tsp1,110), vec2(tsp2, 310));

  // Draws the top of the net - horizontal
  ci::gl::drawLine(vec2(1800,130), vec2(1800-230, 130));
  ci::gl::drawLine(vec2(1800,150), vec2(1800-220, 150));
  ci::gl::drawLine(vec2(1800,170), vec2(1800-210, 170));
  ci::gl::drawLine(vec2(1800,190), vec2(1800-200, 190));
  ci::gl::drawLine(vec2(1800,210), vec2(1800-190, 210));
  ci::gl::drawLine(vec2(1800,230), vec2(1800-180, 230));
  ci::gl::drawLine(vec2(1800,250), vec2(1800-170, 250));
  ci::gl::drawLine(vec2(1800,270), vec2(1800-160, 270));
  ci::gl::drawLine(vec2(1800,290), vec2(1800-150, 290));

  // Draws the left six-yard box lines
  ci::gl::drawLine(vec2(296, 510), vec2(500,510));
  ci::gl::drawLine(vec2(196, 710), vec2(396,710));
  ci::gl::drawLine(vec2(500, 510), vec2(396,710));

  // Draws the right six-yard box lines
  ci::gl::drawLine(vec2(1800 - 296, 510), vec2(1800 - 296 - 204,510));
  ci::gl::drawLine(vec2(1800 - 196, 710), vec2(1800 - 196 - 200,710));
  ci::gl::drawLine(vec2(1800 - 296 - 204, 510), vec2(1800 - 196 - 200,710));

  ci::gl::color(ci::Color("crimson"));
  ci::gl::drawSolidEllipse(vec2(900,610), 100,50);
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedEllipse(vec2(900,610), 100,50);
  ci::gl::drawLine(vec2(900,560), vec2(900,460));
  ci::gl::drawLine(vec2(900,660), vec2(900,760));
}

void BackgroundDesign::DrawLeftSideGoalposts() {
  ci::Color postColor("white");
  ci::gl::color(postColor);
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position), vec2(initial_position + interval, initial_position + rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position + 200), vec2(interval, initial_position + rect_width + 200)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position + 600), vec2(interval, initial_position + rect_width + 600)));
  ci::gl::pushModelMatrix();
  ci::gl::translate(initial_position + interval,initial_position + rect_width);
  size_t numerator = initial_position + rect_width + 200 - initial_position + rect_width;
  size_t denominator = initial_position + interval - interval;
  double turn_value = atan(numerator/denominator);
  ci::gl::rotate(M_PI - turn_value);
  double hypotenuse = sqrt(200*200 + 100*100);
  ci::gl::drawSolidRect(ci::Rectf(vec2(0,0), vec2(hypotenuse,rect_width)));
  ci::gl::popModelMatrix();
  ci::gl::drawSolidRect(ci::Rectf(vec2(initial_position + interval - rect_width,initial_position),
                                  vec2(initial_position + interval,initial_position + rect_width + 400)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(interval - rect_width,initial_position * 3), vec2(interval,initial_position + rect_width + 600)));
}

void BackgroundDesign::DrawLeftSideSideNet() {
  // Draws left side of the net - vertical
  size_t num_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_intervals;
  size_t y_value_1 = initial_position * 3 + rect_width;
  size_t y_value_2 = initial_position * 7 + rect_width;
  for (size_t x = 0; x < num_intervals + 1; x++) {
    ci::gl::drawLine(vec2(0 + x*abridged_interval_value,y_value_1), vec2(0 + x*abridged_interval_value,y_value_2));
  }
  size_t difference = y_value_2 - y_value_1;
  size_t num_horizontal_intervals = 6;
  size_t horizontal_intervals = difference/num_horizontal_intervals;
  for (size_t y = 0; y < num_intervals + 1; y++) {
    ci::gl::drawLine(vec2(0,y_value_1 + horizontal_intervals * y),
                     vec2(interval,y_value_1 + horizontal_intervals * y));
  }
}

void BackgroundDesign::DrawLeftSideTopNet() {
  // Draw top of net - vertical
  size_t num_v_and_h_intervals = 9;
  size_t num_total_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_total_intervals;
  int left_x_value = interval + initial_position - rect_width;
  int right_x_value = interval - rect_width;
  size_t y_value_1 = initial_position + rect_width;
  size_t y_value_2 = initial_position * 3 + rect_width;
  for (size_t x = 0; x < num_v_and_h_intervals; x++) {
    ci::gl::drawLine(vec2(left_x_value - abridged_interval_value * x,y_value_1),
                     vec2(right_x_value - abridged_interval_value * x, y_value_2));
  }

  // Draw top of net - horizontal
  size_t x_width_interval = 10;
  size_t y_width_interval = 20;
  size_t initial_right_x_position = initial_position + interval - rect_width * 2;
  size_t initial_y_position = interval - rect_width * 2;
  for (size_t y = 0; y < num_v_and_h_intervals; y++) {
    ci::gl::drawLine(vec2(0,initial_y_position + y_width_interval * y),
                     vec2(initial_right_x_position - x_width_interval * y, initial_y_position + y_width_interval * y));
  }
}
}