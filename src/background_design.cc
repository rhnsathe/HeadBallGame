//
// Created by Rohan Sathe on 4/19/21.
//

#include "background_design.h"
#include "final_project_app.h"
#include <math.h>

namespace finalproject {

using glm::vec2;

BackgroundDesign::BackgroundDesign() {}

void BackgroundDesign::Display() {
  DrawScoreBoard();
  DrawLeftSideGoalposts();
  DrawLeftSideSideNet();
  DrawLeftSideTopNet();
  DrawField();
  DrawRightSideGoalposts();
  DrawRightSideSideNet();
  DrawRightSideTopNet();
}

void BackgroundDesign::DrawLeftSideGoalposts() {
  // Sets the color of the goal posts
  ci::Color postColor("white");
  ci::gl::color(postColor);

  // Draws the top and bottom goal posts - horizontal (in 3D)
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position),
                                  vec2(initial_position + interval, initial_position + rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position * 3),
                                  vec2(interval, initial_position * 3+ rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(0, initial_position * 7),
                                  vec2(interval, initial_position * 7 + rect_width)));

  // Draws the rotated bar - for 3D purposes
  // Taken from CampusWire - https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
  ci::gl::pushModelMatrix();
  ci::gl::translate(initial_position + interval,initial_position + rect_width);
  size_t numerator = initial_position * 3 + rect_width - initial_position - rect_width;
  size_t denominator = initial_position + interval - interval;
  double turn_value = atan(numerator/denominator);
  ci::gl::rotate(M_PI - turn_value);
  double hypotenuse = sqrt(numerator*numerator + denominator*denominator);
  ci::gl::drawSolidRect(ci::Rectf(vec2(0,0), vec2(hypotenuse,rect_width)));
  ci::gl::popModelMatrix();

  // Draws the vertical goal posts
  ci::gl::drawSolidRect(ci::Rectf(vec2(initial_position + interval - rect_width,initial_position),
                                  vec2(initial_position + interval,initial_position * 5 + rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(interval - rect_width,initial_position * 3), vec2(interval,initial_position * 7 + rect_width)));
}

void BackgroundDesign::DrawLeftSideSideNet() {
  // Sets standard distance between x points
  size_t num_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_intervals;

  // Sets both constant y values
  size_t y_value_1 = initial_position * 3 + rect_width;
  size_t y_value_2 = initial_position * 7 + rect_width;

  // Draws left side of the net - vertical
  for (size_t x = 0; x < num_intervals + 1; x++) {
    ci::gl::drawLine(vec2(0 + x*abridged_interval_value,y_value_1), vec2(0 + x*abridged_interval_value,y_value_2));
  }

  // Sets difference between horizontal lines on side net
  size_t difference = y_value_2 - y_value_1;
  size_t num_horizontal_intervals = 6;
  size_t horizontal_intervals = difference/num_horizontal_intervals;

  // Draws the left side of the net - horizontal
  for (size_t y = 0; y < num_intervals + 1; y++) {
    ci::gl::drawLine(vec2(0,y_value_1 + horizontal_intervals * y),
                     vec2(interval,y_value_1 + horizontal_intervals * y));
  }
}

void BackgroundDesign::DrawLeftSideTopNet() {
  // Draw top of net - vertical

  // Sets the number of diagonal lines
  size_t num_v_and_h_intervals = 9;

  // Sets standard distance between x points
  size_t num_total_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_total_intervals;

  // Sets the initial x on the left and right side
  int left_x_value = interval + initial_position - rect_width;
  int right_x_value = interval - rect_width;

  // Sets the initial y on the left and right side
  size_t y_value_1 = initial_position + rect_width;
  size_t y_value_2 = initial_position * 3 + rect_width;

  // Draws the top of the net - horizontal
  for (size_t x = 0; x < num_v_and_h_intervals; x++) {
    ci::gl::drawLine(vec2(left_x_value - abridged_interval_value * x,y_value_1),
                     vec2(right_x_value - abridged_interval_value * x, y_value_2));
  }

  // Difference between x values
  size_t x_width_interval = 10;

  // Difference between y values
  size_t y_width_interval = 20;

  size_t initial_right_x_position = initial_position + interval - rect_width * 2;
  size_t initial_y_position = interval - rect_width * 2;

  // Draw top of net - diagonal
  for (size_t y = 0; y < num_v_and_h_intervals; y++) {
    ci::gl::drawLine(vec2(0,initial_y_position + y_width_interval * y),
                     vec2(initial_right_x_position - x_width_interval * y, initial_y_position + y_width_interval * y));
  }
}

void BackgroundDesign::DrawField() {
  // Sets color to green
  ci::gl::color(ci::Color("green"));

  // Distance between field and goals.
  size_t added_gap = 70;
  size_t initial_y = 460;
  size_t final_y = initial_y + initial_position * 3;
  size_t initial_right = kXWindowSize - initial_position - interval;
  size_t final_right = kXWindowSize - initial_position - added_gap;

  // Draws pentagonal shaped field to give 3D impression
  ci::gl::drawSolidTriangle(vec2(interval + initial_position + added_gap,initial_y),
                            vec2(interval + initial_position + added_gap,final_y),
                            vec2(interval + rect_width * 2, final_y));
  ci::gl::drawSolidRect(ci::Rectf(vec2(interval + initial_position + added_gap,initial_y),
                                  vec2(initial_right - added_gap, final_y)));
  ci::gl::drawSolidTriangle(vec2(initial_right - added_gap,initial_y),
                            vec2(initial_right - added_gap,final_y),
                            vec2(final_right, final_y));

  // Draws the left six-yard box lines
  ci::gl::color(ci::Color("white"));
  size_t first_x = initial_position * 3 - 4;
  size_t second_x = initial_position * 2 - 4;
  size_t third_x = initial_position * 5;
  size_t fourth_x = second_x + initial_position * 2;
  size_t smaller_y = 510;
  size_t bigger_y = 710;
  ci::gl::drawLine(vec2(first_x, smaller_y), vec2(third_x,smaller_y));
  ci::gl::drawLine(vec2(second_x, bigger_y), vec2(fourth_x,bigger_y));
  ci::gl::drawLine(vec2(third_x, smaller_y), vec2(fourth_x,bigger_y));

  //Draws the right six-yard box lines
  size_t fifth_x = initial_position * 2 + 4;
  ci::gl::drawLine(vec2(kXWindowSize - first_x, smaller_y),
                   vec2(kXWindowSize - first_x - fifth_x,smaller_y));
  ci::gl::drawLine(vec2(kXWindowSize - second_x, bigger_y),
                   vec2(kXWindowSize - second_x - initial_position * 2,bigger_y));
  ci::gl::drawLine(vec2(kXWindowSize - first_x - fifth_x, smaller_y),
                   vec2(kXWindowSize - second_x - initial_position * 2,bigger_y));

  //Draws center circle
  ci::gl::color(ci::Color("crimson"));
  size_t center_x = 900;
  size_t center_y = 610;
  size_t x_radius = 100;
  size_t y_radius = 50;
  ci::gl::drawSolidEllipse(vec2(center_x,center_y), x_radius,y_radius);

  // Draws boundary around center circle
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedEllipse(vec2(center_x,center_y), x_radius,y_radius);
  ci::gl::drawLine(vec2(center_x,center_y - y_radius), vec2(center_x,center_y - y_radius * 3));
  ci::gl::drawLine(vec2(center_x,center_y + y_radius), vec2(center_x,center_y + y_radius * 3));
}

void BackgroundDesign::DrawRightSideGoalposts() {
  // Sets the color of the posts
  ci::Color postColorRight("white");
  ci::gl::color(postColorRight);

  // Draws top and bottom posts
  ci::gl::drawSolidRect(ci::Rectf(vec2(kXWindowSize - initial_position - interval, initial_position),
                                  vec2(kXWindowSize, initial_position + rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(kXWindowSize - interval, initial_position * 3),
                                  vec2(kXWindowSize, initial_position * 3 + rect_width)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(kXWindowSize - interval, initial_position * 7),
                                  vec2(kXWindowSize, initial_position * 7 + rect_width)));

  // Rotation method taken from CampusWire -
  // https://discourse.libcinder.org/t/what-is-the-best-way-to-rotate-rectangles-images/410/2
  ci::gl::pushModelMatrix();
  ci::gl::translate(kXWindowSize - initial_position - interval,initial_position + rect_width);
  size_t numerator = initial_position * 3 + rect_width - initial_position - rect_width;
  size_t denominator = initial_position + interval - interval;
  double turn_value_2 = atan(numerator/denominator);
  ci::gl::rotate((1/2)*M_PI + turn_value_2);
  double hypotenuse = sqrt(numerator*numerator + denominator*denominator);
  ci::gl::drawSolidRect(ci::Rectf(vec2(0,0), vec2(hypotenuse,rect_width)));
  ci::gl::popModelMatrix();

  // Sets constant y values for the vertical posts
  size_t y_value_1 = initial_position * 5 + rect_width;
  size_t y_value_2 = initial_position * 7 + rect_width;

  // Draws the vertical posts
  ci::gl::drawSolidRect(ci::Rectf(vec2(kXWindowSize - interval - initial_position - rect_width,initial_position),
                                  vec2(kXWindowSize - interval - initial_position,y_value_1)));
  ci::gl::drawSolidRect(ci::Rectf(vec2(kXWindowSize - interval - rect_width,initial_position * 3),
                                  vec2(kXWindowSize - interval,y_value_2)));
}

void BackgroundDesign::DrawRightSideSideNet() {
  // Sets right side initial position
  size_t rsp= kXWindowSize - interval;

  // Sets initial y positions
  size_t y_value_1 = initial_position * 3 + rect_width;
  size_t y_value_2 = initial_position * 7 + rect_width;

  // Sets standard distance between x points
  size_t num_total_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_total_intervals;

  // Draw vertical lines
  for (size_t x = 0; x < num_total_intervals + 1; x++) {
    ci::gl::drawLine(vec2(rsp + abridged_interval_value * x,y_value_1), vec2(rsp + abridged_interval_value * x,y_value_2));
  }

  // Sets difference between horizontal lines
  size_t difference = y_value_2 - y_value_1;
  size_t num_horizontal_intervals = 6;
  size_t horizontal_intervals = difference/num_horizontal_intervals;

  // Draw horizontal lines
  for (size_t y = 0; y < num_total_intervals + 1; y++) {
    ci::gl::drawLine(vec2(kXWindowSize,y_value_1 + horizontal_intervals * y),
                     vec2(kXWindowSize - interval,y_value_1 + horizontal_intervals * y));
  }
}

void BackgroundDesign::DrawRightSideTopNet() {
  // Sets initial starting point positon for drawing horizontal top
  int tsp1 = kXWindowSize + rect_width - interval - initial_position;
  int tsp2 = kXWindowSize + rect_width - interval;

  // Sets standard distance between x points
  size_t num_total_intervals = 5;
  float abridged_interval_value = (interval - rect_width)/num_total_intervals;
  size_t y_value_1 = initial_position + rect_width;
  size_t y_value_2 = initial_position * 3 + rect_width;
  size_t num_v_and_h_intervals = 9;

  // Draws the top of the net - horizontal
  for (size_t x = 0; x < num_v_and_h_intervals; x++) {
    ci::gl::drawLine(vec2(tsp1 + abridged_interval_value * x,y_value_1),
                     vec2(tsp2 + abridged_interval_value * x, y_value_2));
  }

  // Sets initial x and y positions
  size_t initial_x_value = interval + initial_position - rect_width * 2;
  size_t initial_y_value = interval - rect_width * 2;

  // Sets x and y intervals
  size_t x_interval = 10;
  size_t y_interval = 20;

  // Draws the top of the net - diagonal
  for (size_t y = 0; y < num_v_and_h_intervals; y++) {
    ci::gl::drawLine(vec2(kXWindowSize,initial_y_value + y_interval * y),
                     vec2(kXWindowSize - initial_x_value + x_interval * y,
                          initial_y_value + y_interval * y));
  }
}

void BackgroundDesign::DrawScoreBoard() {
  // Sets x center position
  size_t x_center_position = kXWindowSize/2;

  // Sets initial and final x or y position
  size_t initial_x_or_y_position = 805;
  size_t final_x_or_y_position = 895;

  // Sets both intervals
  size_t x_interval = 200;
  size_t y_interval = 5;

  // Draws scoreboard label
  std::string scoreboard_label = "SCOREBOARD";
  ci::gl::drawStringCentered(scoreboard_label, vec2(x_center_position,initial_x_or_y_position - y_interval * 2), "white", ci::Font());

  // Draws scoreboard
  ci::gl::color(ci::Color("black"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(x_center_position - x_interval,initial_x_or_y_position),
                                  vec2(x_center_position + x_interval,final_x_or_y_position)));
  ci::gl::color(ci::Color("orange"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(x_center_position - x_interval + y_interval,
                                       initial_x_or_y_position + y_interval),
                                  vec2(final_x_or_y_position,
                                       final_x_or_y_position - y_interval)));
  ci::gl::color(ci::Color("purple"));
  ci::gl::drawSolidRect(ci::Rectf(vec2(final_x_or_y_position + y_interval * 2,
                                       initial_x_or_y_position + y_interval),
                                  vec2(final_x_or_y_position + x_interval,
                                       final_x_or_y_position - y_interval)));
}
}