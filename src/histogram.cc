//
// Created by Rohan Sathe on 3/22/21.
//
#include "histogram.h"

namespace idealgas {

using glm::vec2;

Histogram::Histogram(std::vector<Particle> particles, size_t num_particles) {
  for (size_t x = 0; x < num_particles; x++) {
    if (particles[x].color_ == "blue") {
      float speed = glm::length(particles[x].velocity_);

      // Checks if the measured speed is greater than the current max_blue_speed_ value.
      if (abs(speed) > abs(max_blue_speed_)) {
        max_blue_speed_ = abs(speed);
      }
      num_blue_.push_back(particles[x]);
    } else if (particles[x].color_ == "green") {
      float speed = glm::length(particles[x].velocity_);

      // Checks if the measured speed is greater than the current max_green_speed_ value.
      if (abs(speed) > abs(max_green_speed_)) {
        max_green_speed_ = abs(speed);
      }
      num_green_.push_back(particles[x]);
    } else if (particles[x].color_ == "orange") {
      float speed = glm::length(particles[x].velocity_);

      // Checks if the measured speed is greater than the current max_orange_speed_ value.
      if (abs(speed) > abs(max_orange_speed_)) {
        max_orange_speed_ = abs(speed);
      }
      num_orange_.push_back(particles[x]);
    }
  }
  //DrawHistogram("blue");
  //DrawHistogram("green");
  //DrawHistogram("orange");
}

void Histogram::DrawHistogram(ci::Color color) {
  idealgas::Particle particle;

  // Activates if the passed color is blue.
  if (color == "blue") {
    // These two commands draw the x and y axis of the histogram.
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, kInitialYPosition),
                     vec2(particle.kWidth + kStartingXAddOn, kInitialYPosition + kInterYScale));
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, kInitialYPosition + kInterYScale),
                     vec2(particle.kWidth + kStartingXAddOn * 3, kInitialYPosition + kInterYScale));

    // This writes the title of the histogram.
    size_t title_x_position = particle.kWidth + 140;
    ci::gl::drawString("Blue Particle Histogram", vec2(title_x_position, kInitialYPosition), "blue", ci::Font::getDefault());

    // This writes the y axis label of the histogram.
    size_t y_axis_label_position_x = particle.kWidth + 20;
    ci::gl::drawString("# of Particles", vec2(y_axis_label_position_x,
                                              (kInitialYPosition + kInterYScale)/2), "blue", ci::Font::getDefault());

    // This writes the x axis label of the histogram.
    size_t x_axis_label_position_x = particle.kWidth + 170;
    size_t x_axis_label_position_y = kInitialYPosition + kInterYScale + 5;
    ci::gl::drawString("Speed", vec2(x_axis_label_position_x, x_axis_label_position_y),
                       "blue", ci::Font::getDefault());

    // These dictate the width of the bars in the histogram.
    size_t starting_x = particle.kWidth + 100;
    size_t ending_x = particle.kWidth + 108;

    // These essentially count the number of velocities in the range of 1. For example, if the velocity truncated to a size_t is 2,
    // it will increment the third place in the vector by 1, as this is the 2 (inclusive) -3 range for velocities.
    std::vector<size_t> values((size_t) max_blue_speed_);
    for (size_t i = 0; i < num_blue_.size(); i++) {
      size_t mag = (size_t) glm::length(num_blue_[i].velocity_);
      if (mag == (size_t) max_blue_speed_) {
        mag--;
      }
      values[mag] = values[mag] + 1;
    }

    // This will draw the rectangles of a certain size.
    for (size_t x = 0; x < values.size(); x++) {
      size_t bar_height = (kInitialYPosition + kInterYScale) - values[x] * scale_factor_;
      ci::gl::drawSolidRect(ci::Rectf(vec2(starting_x, (bar_height)), vec2(ending_x, kInitialYPosition + kInterYScale)));
      starting_x += 15;
      ending_x += 15;
    }

    // Activates if the passed color is green.
  } else if (color == "green") {
    size_t green_starting_y_position = kInitialYPosition + kInterYScale + kIntraYScale;
    size_t green_final_y_position = kInitialYPosition + kInterYScale + kIntraYScale + kInterYScale;

    // These two commands draw the x and y axis of the histogram.
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, green_starting_y_position),
                     vec2(particle.kWidth + kStartingXAddOn, green_final_y_position));
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, green_final_y_position),
                     vec2(particle.kWidth + kStartingXAddOn * 3, green_final_y_position));

    // This writes the title of the histogram.
    size_t title_x_position = particle.kWidth + 140;
    ci::gl::drawString("Green Particle Histogram",
                       vec2(title_x_position, green_starting_y_position), "green", ci::Font::getDefault());

    // This writes the y axis label of the histogram.
    size_t y_axis_label_position_x = particle.kWidth + 20;
    ci::gl::drawString("# of Particles", vec2(y_axis_label_position_x,
                                              (green_starting_y_position + green_final_y_position)/2), "green", ci::Font::getDefault());

    // This writes the x axis label of the histogram.
    size_t x_axis_label_position_x = particle.kWidth + 170;
    size_t x_axis_label_position_y = green_final_y_position + 5;
    ci::gl::drawString("Speed", vec2(x_axis_label_position_x, x_axis_label_position_y), "green", ci::Font::getDefault());

    // These dictate the width of the bars in the histogram.
    size_t starting_x = particle.kWidth + 100;
    size_t ending_x = particle.kWidth + 108;

    // These essentially count the number of velocities in the range of 1. For example, if the velocity truncated to a size_t is 2,
    // it will increment the third place in the vector by 1, as this is the 2 (inclusive) -3 range for velocities.
    std::vector<size_t> values((size_t) max_green_speed_);
    for (size_t i = 0; i < num_green_.size(); i++) {
      size_t mag = (size_t) glm::length(num_green_[i].velocity_);
      if (mag == (size_t) max_green_speed_) {
        mag--;
      }
      values[mag] = values[mag] + 1;
    }

    // This will draw the rectangles of a certain size.
    for (size_t x = 0; x < values.size(); x++) {
      ci::gl::drawSolidRect(ci::Rectf(vec2(starting_x, (green_final_y_position - values[x] * scale_factor_)),
                                      vec2(ending_x, green_final_y_position)));
      starting_x += 15;
      ending_x += 15;
    }

    // This activates if the passed color is orange.
  } else if (color == "orange") {
    size_t orange_starting_y_position = kInitialYPosition + kInterYScale * 2 + kIntraYScale * 2;
    size_t orange_final_y_position = kInitialYPosition + kInterYScale * 3 + kIntraYScale * 2;

    // These two commands draw the x and y axis of the histogram.
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, orange_starting_y_position),
                     vec2(particle.kWidth + kStartingXAddOn, orange_final_y_position));
    ci::gl::drawLine(vec2(particle.kWidth + kStartingXAddOn, orange_final_y_position),
                     vec2(particle.kWidth + kStartingXAddOn * 3, orange_final_y_position));

    // This writes the title of the histogram.
    size_t title_x_position = particle.kWidth + 140;
    ci::gl::drawString("Orange Particle Histogram", vec2(title_x_position, orange_starting_y_position), "orange", ci::Font::getDefault());

    // This writes the y axis label of the histogram.
    size_t y_axis_label_position_x = particle.kWidth + 20;
    ci::gl::drawString("# of Particles", vec2(y_axis_label_position_x, (orange_starting_y_position + orange_final_y_position)/2),
                       "orange", ci::Font::getDefault());

    // This writes the x axis label of the histogram.
    size_t x_axis_label_position_x = particle.kWidth + 170;
    size_t x_axis_label_position_y = orange_final_y_position + 5;
    ci::gl::drawString("Speed", vec2(x_axis_label_position_x, x_axis_label_position_y), "orange", ci::Font::getDefault());

    // These dictate the width of the bars in the histogram.
    size_t starting_x = particle.kWidth + 100;
    size_t ending_x = particle.kWidth + 108;

    // These essentially count the number of velocities in the range of 1. For example, if the velocity truncated to a size_t is 2,
    // it will increment the third place in the vector by 1, as this is the 2 (inclusive) -3 range for velocities.
    std::vector<size_t> values((size_t) max_orange_speed_);
    for (size_t i = 0; i < num_orange_.size(); i++) {
      size_t mag = (size_t) glm::length(num_orange_[i].velocity_);
      if (mag == (size_t) max_orange_speed_) {
        mag--;
      }
      values[mag] = values[mag] + 1;
    }

    // This will draw the rectangles of a certain size.
    for (size_t x = 0; x < values.size(); x++) {
      ci::gl::drawSolidRect(ci::Rectf(vec2(starting_x, (orange_final_y_position - values[x] * scale_factor_)),
                                      vec2(ending_x, orange_final_y_position)));
      starting_x += 15;
      ending_x += 15;
    }
  }
}

std::vector<Particle> Histogram::GetNumBlue() {
  return num_blue_;
}

std::vector<Particle> Histogram::GetNumGreen() {
  return num_green_;
}

std::vector<Particle> Histogram::GetNumOrange() {
  return num_orange_;
}

}

