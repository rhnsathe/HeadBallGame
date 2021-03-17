//
// Created by Rohan Sathe on 3/13/21.
//
#pragma once
#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

Particle::Particle() {
  int random_x_position = rand() % (abs(kLowerPositionBound) + abs(kHeightAndWidth - kRadius) + 1);
  int random_y_position = rand() % (abs(kLowerPositionBound) + abs(kHeightAndWidth - kRadius) + 1);
  position_ = glm::vec2(random_x_position, random_y_position);
  double random_x_velocity = rand() % kVelocityRange + kLowerVelocityBound;
  double random_y_velocity = rand() % kVelocityRange + kLowerVelocityBound;
  velocity_ = glm::vec2(random_x_velocity, random_y_velocity);
}

glm::vec2 Particle::getPosition() {
  return position_;
}

glm::vec2 Particle::getVelocity() {
  return velocity_;
}

void Particle::UpdateOneSecond() {
  UpdateOverall(1.0);
}

void Particle::UpdateOverall(double time) {
  double new_x_position = position_.x + velocity_.x * time;
  double new_y_position = position_.y + velocity_.y * time;

  if (CheckExistenceOfCollision(new_x_position, new_y_position)) {
    CollideWithWalls(time, new_x_position, new_y_position);
  }
}

void Particle::CollideWithWalls(double time, double new_x_position, double new_y_position) {
  double x_time_to_collide = abs((position_.x - kRadius)/velocity_.x);
  double y_time_to_collide = abs((position_.y - kRadius)/velocity_.y);
  if (x_time_to_collide == y_time_to_collide) {
    CollideWithBothWalls(time, new_x_position, new_y_position);
  } else if (x_time_to_collide < y_time_to_collide) {
    CollideWithVerticalWalls(time, new_x_position, new_y_position);
  } else {
    CollideWithHorizontalWalls(time, new_x_position, new_y_position);
  }
}
void Particle::CollideWithBothWalls(double time, double new_x_position, double new_y_position) {
  double x_time_to_collide = abs((position_.x - kRadius)/velocity_.x);
  double y_time_to_collide = abs((position_.y - kRadius)/velocity_.y);

}
void Particle::CollideWithHorizontalWalls(double time, double new_x_position, double new_y_position) {

}
void Particle::CollideWithVerticalWalls(double time, double new_x_position, double new_y_position) {

}

bool Particle::CheckExistenceOfCollision(double new_x_position, double new_y_position) {
  if (new_x_position <= kRadius || new_y_position <= kRadius ||
      new_x_position >= kRadius + kHeightAndWidth || new_y_position >= kRadius + kHeightAndWidth) {
    return true;
  }
  return false;
}

}