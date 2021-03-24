//
// Created by Rohan Sathe on 3/13/21.
//
#pragma once
#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {
  class Particle {
   public:
    /**
     * Default constructor that creates a particle with a random position and velocity.
     */
    Particle();

    /**
     * Creates a particle with a specific position and velocity.
     * @param position
     * @param velocity
     */
    Particle(glm::vec2 position, glm::vec2 velocity);

    /**
     * Initializes a particle with a specific color.
     * @param color_
     */
    Particle(ci::Color &color_);

    /**
     * Initializes a particle with a specific color.
     * @param color_
     */
    Particle(ci::Color color_, size_t radius, size_t mass);

    /**
     * Returns the kLowerVelocityBound value.
     * @return double.
     */
    double GetKLowerVelocityBound();

    /**
     * Returns the kVelocityRange value.
     * @return double.
     */
    double GetKVelocityRange();

    /**
     * Updates box with a specific time.
     * @param time.
     */
    void UpdateOverall(double time);

    /**
     * Draws particle using Cinder.
     */
    void DrawParticle(ci::Color &color);

    /**
     * Initializes a specific mass and radius of a colored particle.
     * @param color
     */
    void InitializeParticleMassAndRadiusWithColor(ci::Color color);

    /**
     * Vec2 with x and y positions of particle.
     */
    glm::vec2 position_;

    /**
     * Vec2 with x and y velocities of particle.
     */
    glm::vec2 velocity_;

    /**
     * Radius of particles.
     */
    int radius_;

    /**
     * Height of the box.
     */
    const int kHeight = 700;

    /**
     * Width of the box.
     */
    const int kWidth = 800;

    /**
     * Represents the color of the particle.
     */
    ci::Color color_;

    /**
     * Represents the mass of the particle.
     */
    size_t mass_;


   private:
    /**
     * Double that holds the lowest possible value for the velocity.
     */
    const double kLowerVelocityBound = 0.0;

    /**
     * Double that holds the range of possible velocity values.
     */
    const int kVelocityRange = 5;

    /**
     * Radius of blue particle, also serves as default radius of any other particle.
     */
    const size_t kBlueRadius = 8;

    /**
     * Mass of blue particle, also serves as default mass of any other particle.
     */
    const size_t kBlueMass = 5;

    /**
     * Radius of green particle.
     */
    const size_t kGreenRadius = 10;

    /**
     * Mass of green particle.
     */
    const size_t kGreenMass = 25;

    /**
     * Radius of orange particle.
     */
    const size_t kOrangeRadius = 12;

    /**
     * Mass of orange particle.
     */
    const size_t kOrangeMass = 45;


    /**
     * Called if there is a particle collision with the walls.
     * @param time
     * @param new_x_position
     * @param new_y_position
     */
    void CollideWithWalls(double time, double new_x_position, double new_y_position);

    /**
     * Called if the particle collides with both walls.
     * @param time
     * @param x_time_to_collide
     * @param new_x_position
     * @param new_y_position
     */
    void CollideWithBothWalls(double time, double x_time_to_collide, double new_x_position, double new_y_position);

    /**
     * Called if the particle collides with a vertical wall.
     * @param time
     * @param x_time_to_collide
     * @param new_x_position
     * @param new_y_position
     */
    void CollideWithVerticalWalls(double time, double x_time_to_collide, double new_x_position, double new_y_position);

    /**
     * Called if the particle collides with a horziontal wall.
     * @param time
     * @param y_time_to_collide
     * @param new_x_position
     * @param new_y_position
     */
    void CollideWithHorizontalWalls(double time, double y_time_to_collide, double new_x_position, double new_y_position);

    /**
     * Checks if there is a collusion with a wall.
     * @param new_x_position
     * @param new_y_position
     * @return boolean.
     */
    bool CheckExistenceOfCollision(double new_x_position, double new_y_position);

    /**
     * Checks which vertical wall is collided with.
     * @return boolean.
     */
    bool CheckVerticalWalls();

    /**
     * Checks which horizontal wall is collided with.
     * @return boolean.
     */
    bool CheckHorizontalWalls();
  };
}