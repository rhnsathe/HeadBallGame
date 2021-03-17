#include "gas_container.h"
#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

GasContainer::GasContainer(int num_particles) {
  for (size_t i = 0; i < num_particles; i++) {
    Particle particle;
    //std::cout << particle.velocity_;
    particles_.push_back(particle);
  }
}

void GasContainer::Display() const {
  for (Particle particle: particles_) {
    particle.DrawParticle();
  }
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(0, 0), vec2(700, 700)));
}

void GasContainer::AdvanceOneFrame() {
  for (size_t i = 0; i < particles_.size(); i++) {
    //Particle &particle = particles_[i];
    TryUpdate(i);
    std::cout << particles_[1].position_;
    //std::cout <<particles_[1].velocity_;
  }
  CheckForCollisions();

}

void GasContainer::CheckForCollisions() {
  if (particles_.size() > 0) {
    for (size_t present_index = 0; present_index < particles_.size() - 1; present_index++) {
      for (size_t check_index = present_index + 1; check_index < particles_.size(); check_index++) {
        Particle& particle1 = particles_[present_index];
        Particle& particle2 = particles_[check_index];
        double distanceBetweenRadii = glm::distance(particle1.position_, particle2.position_);
        if (distanceBetweenRadii < particle1.kRadius + particle2.kRadius) {
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
  if (particles_[i].position_.x + particles_[i].kRadius > particles_[i].kHeightAndWidth) {
    if (particles_[i].velocity_.x > 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
  } else if (particles_[i].position_.x < particles_[i].kRadius) {
    if (particles_[i].velocity_.x < 0) {
      particles_[i].velocity_ = glm::vec2(-1, 1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
  } else if (particles_[i].position_.y + particles_[i].kRadius > particles_[i].kHeightAndWidth) {
    if (particles_[i].velocity_.y > 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
  } else if (particles_[i].position_.y < particles_[i].kRadius) {
    if (particles_[i].velocity_.y < 0) {
      particles_[i].velocity_ = glm::vec2(1, -1) * particles_[i].velocity_;
      particles_[i].position_ += particles_[i].velocity_;
    }
  } else {
    particles_[i].position_ +=  particles_[i].velocity_;
  }

}

}  // namespace idealgas
