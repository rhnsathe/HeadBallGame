#include "gas_container.h"
#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(int num_particles) {
  for (size_t i = 0; i < num_particles; i++) {
    Particle particle;
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  for (Particle particle: particles_) {
    particle.DrawParticle();
  }
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(0, 0), vec2(kLengthAndWidth, kLengthAndWidth)));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    TryUpdate(i);
  }
  CheckForCollisions();
}

void GasContainer::CheckForCollisions() {
  // Ensures that the particles vector has at least 1 particle in it.
  if (particles_.size() > 0) {
    for (size_t present_index = 0; present_index < particles_.size() - 1; present_index++) {
      for (size_t check_index = present_index + 1; check_index < particles_.size(); check_index++) {
        Particle& particle1 = particles_[present_index];
        Particle& particle2 = particles_[check_index];
        double distanceBetweenRadii = glm::distance(particle1.position_, particle2.position_);
        // Ensures that the distance between the radii is less than the 2 * kRadius.
        if (distanceBetweenRadii < particle1.kRadius + particle2.kRadius) {
          // Checks to make sure the dot product of the sum of the velocity vectors
          // and the sum of the position vectors is less than 0.
          if (glm::dot((particle1.velocity_ - particle2.velocity_), (particle1.position_ - particle2.position_)) < 0) {
            CommenceCollision(present_index, check_index, distanceBetweenRadii);
          }
        }
      }
    }
  }
}

void GasContainer::CommenceCollision(size_t present_index, size_t check_index, double distanceBetweenRadii) {
  Particle& particle1 = particles_[present_index];
  Particle& particle2 = particles_[check_index];
  // Utilizes formula provided to create result velocities for particles after collision.
  glm::vec2 new_velocity_1 = particle1.velocity_ -
      glm::vec2(((glm::dot((particle1.velocity_ - particle2.velocity_),(particle1.position_ - particle2.position_))) /
                              (pow(distanceBetweenRadii, 2)))) * (particle1.position_ - particle2.position_);
  glm::vec2 new_velocity_2 = particle2.velocity_ -
                             glm::vec2(((glm::dot((particle2.velocity_ - particle1.velocity_),(particle2.position_ - particle1.position_))) /
                                        (pow(distanceBetweenRadii, 2)))) * (particle2.position_ - particle1.position_);
  particles_[present_index].velocity_ = new_velocity_1;
  particles_[check_index].velocity_ = new_velocity_2;
}

void GasContainer::TryUpdate(size_t i) {
  // Checks potential collision with right vertical wall.
  if (particles_[i].position_.x + particles_[i].kRadius > particles_[i].kHeightAndWidth) {
    // Ensures that the particle has a positive x velocity.
    if (particles_[i].velocity_.x > 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
    // Checks potential collision with left vertical wall.
  } else if (particles_[i].position_.x < particles_[i].kRadius) {
    // Ensures that the particle has a negative x velocity.
    if (particles_[i].velocity_.x < 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
    // Checks potential collision with top horizontal wall.
  } else if (particles_[i].position_.y + particles_[i].kRadius > particles_[i].kHeightAndWidth) {
    // Ensures that the particle has a positive y velocity.
    if (particles_[i].velocity_.y > 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
    // Checks potential collision with bottom horizontal wall.
  } else if (particles_[i].position_.y < particles_[i].kRadius) {
    // Ensures that the particle has a negative y velocity.
    if (particles_[i].velocity_.y < 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
    // Moves particle to new position if no collision with walls occurred.
  } else {
    particles_[i].position_ +=  particles_[i].velocity_;
  }
}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::AddParticle(Particle particle) {
  particles_.push_back(particle);
}

}  // namespace idealgas
