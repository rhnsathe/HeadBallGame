#include "gas_container.h"
#include "cinder/gl/gl.h"
#include "cinder/Text.h"
#include "particle.h"
#include "histogram.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(size_t num_particles) {
  for (size_t i = 0; i < num_particles; i++) {
    size_t random_number = rand() % 3 + 1;
    if (random_number == 1) {
      ci::Color color = "blue";
      Particle particle = Particle(color);
      particles_.push_back(particle);
    } else if (random_number == 2) {
      ci::Color color = "green";
      Particle particle = Particle(color);
      particles_.push_back(particle);
    } else if (random_number == 3) {
      ci::Color color = "orange";
      Particle particle = Particle(color);
      particles_.push_back(particle);
    } else {
      ci::Color color = "blue";
      Particle particle = Particle(color);
      particles_.push_back(particle);
    }
  }
}

void GasContainer::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(2, 2), vec2(kWidth, kHeight)));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    size_t check_value = TryUpdate(i);

    // Moves particle if no collision occurs.
    if (check_value == 0) {
      particles_[i].position_ +=  particles_[i].velocity_;
    }
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
        if (distanceBetweenRadii < particle1.radius_ + particle2.radius_) {
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
      glm::vec2((2*particle2.mass_)/(particle1.mass_ + particle2.mass_)) * glm::vec2(((glm::dot((particle1.velocity_ - particle2.velocity_),(particle1.position_ - particle2.position_))) /
                              (pow(distanceBetweenRadii, 2)))) * (particle1.position_ - particle2.position_);
  glm::vec2 new_velocity_2 = particle2.velocity_ -
  glm::vec2((2*particle1.mass_)/(particle1.mass_ + particle2.mass_)) * glm::vec2(((glm::dot((particle2.velocity_ - particle1.velocity_),(particle2.position_ - particle1.position_))) /
                                        (pow(distanceBetweenRadii, 2)))) * (particle2.position_ - particle1.position_);
  particles_[present_index].velocity_ = new_velocity_1;
  particles_[check_index].velocity_ = new_velocity_2;
}

size_t GasContainer::TryUpdate(size_t i) {
  size_t value = 0;
  // Checks potential collision with right vertical wall.
  if (particles_[i].position_.x + particles_[i].radius_ > particles_[i].kWidth) {
    // Ensures that the particle has a positive x velocity.
    if (particles_[i].velocity_.x > 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
      value++;
    }
    // Checks potential collision with left vertical wall.
  }
  if (particles_[i].position_.x < particles_[i].radius_) {
    // Ensures that the particle has a negative x velocity.
    if (particles_[i].velocity_.x < 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
      value++;
    }
    // Checks potential collision with top horizontal wall.
  }
  if (particles_[i].position_.y + particles_[i].radius_ > particles_[i].kHeight) {
    // Ensures that the particle has a positive y velocity.
    if (particles_[i].velocity_.y > 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
      value++;
    }
    // Checks potential collision with bottom horizontal wall.
  }
  if (particles_[i].position_.y < particles_[i].radius_) {
    // Ensures that the particle has a negative y velocity.
    if (particles_[i].velocity_.y < 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
      value++;
    }
  }

  // If returned value > 0, there was a collision.
  return value;
}

std::vector<Particle> GasContainer::GetParticles() {
  return particles_;
}

void GasContainer::AddParticle(Particle &particle) {
  particles_.push_back(particle);
}

}  // namespace idealgas
