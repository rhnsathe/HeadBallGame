//
// Created by Rohan Sathe on 3/13/21.
//
#include "cinder/gl/gl.h"
#include "particle.h"
#include <stdlib.h>
#include <time.h>

using glm::vec2;

namespace idealgas {

Particle::Particle() {
  // Default radius for default particle
  radius_ = kBlueRadius;

  // This was taken from https://www.codegrepper.com/code-examples/cpp/randomize+a+number+between+1+and+100+C%2B%2B;
  // Creates random positions from range of positions.
  double random_x_position = rand() % (abs(radius_) + abs(kWidth - radius_) + 1);

  double random_y_position = rand() % (abs(radius_) + abs(kHeight - radius_) + 1);
  position_ = glm::vec2(random_x_position, random_y_position);

  // Creates random velocities from range of velocities.

  double random_x_velocity = rand() % kVelocityRange + kLowerVelocityBound;

  double random_y_velocity = rand() % kVelocityRange + kLowerVelocityBound;
  velocity_ = glm::vec2(random_x_velocity, random_y_velocity);

  // Default color is blue
  color_ = ci::Color("blue");
  mass_ = kBlueMass;
}

Particle::Particle(glm::vec2 position, glm::vec2 velocity) {
  // Default radius for default particle
  radius_ = kBlueRadius;

  position_ = position;
  velocity_ = velocity;

  // Default color is blue.
  color_ = ci::Color("blue");
  mass_ = kBlueMass;
}

Particle::Particle(ci::Color &color) {
  color_ = color;
  InitializeParticleMassAndRadiusWithColor(color);

  // Creates random positions from range of positions.
  double random_x_position = rand() % (abs(radius_) + abs(kWidth - radius_) + 1);

  double random_y_position = rand() % (abs(radius_) + abs(kHeight - radius_) + 1);
  position_ = glm::vec2(random_x_position, random_y_position);


  // Creates random velocities from range of velocities.
  double random_x_velocity = rand() % kVelocityRange + kLowerVelocityBound;

  double random_y_velocity = rand() % kVelocityRange + kLowerVelocityBound;
  velocity_ = glm::vec2(random_x_velocity, random_y_velocity);
}

Particle::Particle(ci::Color color, size_t radius, size_t mass) {
  color_ = color;
  radius_ = radius;
  mass_ = mass;

  // Creates random positions from range of positions.
  double random_x_position = rand() % (abs(radius_) + abs(kWidth - radius_) + 1);

  double random_y_position = rand() % (abs(radius_) + abs(kHeight - radius_) + 1);
  position_ = glm::vec2(random_x_position, random_y_position);


  // Creates random velocities from range of velocities.
  double random_x_velocity = rand() % kVelocityRange + kLowerVelocityBound;

  double random_y_velocity = rand() % kVelocityRange + kLowerVelocityBound;
  velocity_ = glm::vec2(random_x_velocity, random_y_velocity);
}



double Particle::GetKLowerVelocityBound() {
  return kLowerVelocityBound;
}

double Particle::GetKVelocityRange() {
  return kVelocityRange;
}

void Particle::UpdateOverall(double time) {
  // Sets bound to ensure no infinite loop.
  if (time < 0.001) {
    return;
  }
  double new_x_position = position_.x + velocity_.x * time;
  double new_y_position = position_.y + velocity_.y * time;

  // Ensures that there is a collision, otherwise changes the position of the particle.
  if (CheckExistenceOfCollision(new_x_position, new_y_position)) {
    CollideWithWalls(time, new_x_position, new_y_position);
  }
  position_ = glm::vec2(new_x_position, new_y_position);
  return;
}

void Particle::CollideWithWalls(double time, double new_x_position, double new_y_position) {
  double x_time_to_collide = 0.0;
  double y_time_to_collide = 0.0;
  if (CheckVerticalWalls()) {
    // Ensures that the x velocity is positive.
    if (velocity_.x < 0) {
      x_time_to_collide = abs((position_.x - radius_)/velocity_.x);
    } else {
      return;
    }
  }
  if (!CheckVerticalWalls()) {
    // Ensures that the x velocity is negative.
    if (velocity_.x > 0) {
      x_time_to_collide = abs((position_.x - (kWidth - radius_)/velocity_.x));
    } else {
      return;
    }
  }
  if (CheckHorizontalWalls()) {
    // Ensures that the y velocity is positive.
    if (velocity_.y < 0) {
      y_time_to_collide = abs((position_.y - radius_)/velocity_.y);
    } else {
      return;
    }
  }
  if (!CheckHorizontalWalls()) {
    // Ensures that the y velocity is negative.
    if (velocity_.y > 0) {
      y_time_to_collide = abs((position_.y - (kHeight - radius_))/velocity_.y);
    } else {
      return;
    }

  }
  // Checks to see which time is faster to collide with a wall.
  if (x_time_to_collide == y_time_to_collide) {
    CollideWithBothWalls(time, x_time_to_collide, new_x_position, new_y_position);
  } else if (x_time_to_collide < y_time_to_collide) {
    CollideWithVerticalWalls(time, x_time_to_collide, new_x_position, new_y_position);
  } else {
    CollideWithHorizontalWalls(time, y_time_to_collide, new_x_position, new_y_position);
  }

}
void Particle::CollideWithBothWalls(double time, double x_time_to_collide, double new_x_position, double new_y_position) {
  position_ = glm::vec2(position_.x - velocity_.x * x_time_to_collide, position_.y - velocity_.y * x_time_to_collide);
  velocity_ = glm::vec2(-1, -1) * velocity_;
  // Displays the remaining time after the collision happened.
  double remaining_time = time - x_time_to_collide;
  UpdateOverall(remaining_time);

}
void Particle::CollideWithHorizontalWalls(double time, double y_time_to_collide, double new_x_position, double new_y_position) {
  position_ = glm::vec2(position_.x, position_.y - velocity_.y * y_time_to_collide);
  velocity_ = glm::vec2(1, -1) *  velocity_;
  // Displays the remaining time after the collision happened.
  double remaining_time = time - y_time_to_collide;
  UpdateOverall(remaining_time);
}
void Particle::CollideWithVerticalWalls(double time, double x_time_to_collide, double new_x_position, double new_y_position) {
  position_ = glm::vec2(position_.x - velocity_.x * x_time_to_collide , position_.y);
  velocity_ = glm::vec2(-1, 1) *  velocity_;
  // Displays the remaining time after the collision happened.
  double remaining_time = time - x_time_to_collide;
  UpdateOverall(remaining_time);
}

bool Particle::CheckExistenceOfCollision(double new_x_position, double new_y_position) {
  // Ensures that there is some collision with walls.
  if (new_x_position <= radius_ || new_y_position <= radius_ ||
      new_x_position >= kWidth - radius_ || new_y_position >= kHeight - radius_) {
    return true;
  }
  return false;
}

bool Particle::CheckVerticalWalls() {
  // Checks which vertical wall collision happens faster, so as to check which vertical wall the collision happened with.
  double x_time_to_collide_with_left = abs((position_.x - radius_)/velocity_.x);
  double x_time_to_collide_with_right = abs((position_.x - (kWidth - radius_)/velocity_.x));
  if (x_time_to_collide_with_left < x_time_to_collide_with_right) {
    return true;
  } else {
    return false;
  }
}

bool Particle::CheckHorizontalWalls() {
  // Checks which horizontal wall collision happens faster, so as to check which vertical wall the collision happened with.
  double y_time_to_collide_with_top = abs((position_.y - radius_)/velocity_.y);
  double y_time_to_collide_with_bottom = abs((position_.y - (kHeight - radius_))/velocity_.y);
  if (y_time_to_collide_with_top < y_time_to_collide_with_bottom) {
    return true;
  } else {
    return false;
  }
}

void Particle::DrawParticle(ci::Color &color) {
  // Dictates the color, position, and radius of the particles.
  if (color == ci::Color("blue")) {
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(position_, radius_);
  } else if (color == ci::Color("green")) {
    ci::gl::color(ci::Color("green"));
    ci::gl::drawSolidCircle(position_, radius_);
  } else if (color == ci::Color("orange")) {
    ci::gl::color(ci::Color("orange"));
    ci::gl::drawSolidCircle(position_, radius_);
  } else {
    ci::gl::color(ci::Color("blue"));
    ci::gl::drawSolidCircle(position_, radius_);
  }
}

void Particle::InitializeParticleMassAndRadiusWithColor(ci::Color color) {
  if (color == ci::Color("blue")) {
    radius_ = kBlueRadius;
    mass_ = kBlueMass;
  } else if (color == ci::Color("green")) {
    radius_ = kGreenRadius;
    mass_ = kGreenMass;
  } else if (color == ci::Color("orange")) {
    radius_ = kOrangeRadius;
    mass_ = kOrangeMass;
  } else {
    radius_ = kBlueRadius;
    mass_ = kBlueMass;
  }
}



}