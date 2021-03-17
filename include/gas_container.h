#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructor that takes in whatever number
   * of particles is necessary for the simulation.
   */
  GasContainer(int num_particles);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Checks for potential collisions between particles.
   */
  void CheckForCollisions();


 private:
  /**
   * Fills with particles with random positions and velocities.
   */
  std::vector<Particle> particles_;

  /**
   * Initiates collision between particles.
   * @param present_index
   * @param check_index
   * @param distanceBetweenRadii
   */
  void CommenceCollision(size_t present_index, size_t check_index, double distanceBetweenRadii);
};

}  // namespace idealgas
