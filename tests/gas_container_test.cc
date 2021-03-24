//
// Created by Rohan Sathe on 3/17/21.
//

#include <catch2/catch.hpp>
#include <gas_container.h>
#include "particle.h"
#include "cinder/gl/gl.h"

using idealgas::GasContainer;
using idealgas::Particle;
using glm::vec2;

TEST_CASE("Constructor tests") {
  SECTION("Appropriate number of particles in particles_") {
    GasContainer container_ = GasContainer(100);
    REQUIRE(container_.GetParticles().size() == 100);
  }
}

TEST_CASE("Helper Method tests") {
  SECTION("Validate AddParticle(Particle particle) method") {
    GasContainer container_ = GasContainer(0);
    idealgas::Particle particle;
    container_.AddParticle(particle);
    REQUIRE(container_.GetParticles().size() == 1);
  }
  SECTION("Validate TryUpdate, No collision with wall") {
    GasContainer container_ = GasContainer(0);
    Particle particle = Particle(glm::vec2(250, 250), glm::vec2(20, -25));
    glm::vec2 position = particle.position_;
    glm::vec2 velocity = particle.velocity_;
    position += velocity;
    container_.AddParticle(particle);
    container_.AdvanceOneFrame();
    REQUIRE(container_.GetParticles().at(0).position_.x == position.x);
  }
  SECTION("Validate TryUpdate, Right side vertical wall") {
    GasContainer container_ = GasContainer(0);
    Particle particle = Particle(glm::vec2(800, 250), glm::vec2(20, -25));
    container_.AddParticle(particle);
    container_.TryUpdate(0);
    REQUIRE(container_.GetParticles().at(0).velocity_.x == -20);
  }
  SECTION("Validate TryUpdate, Horizontal Top Wall") {
    GasContainer container_ = GasContainer(0);
    Particle particle = Particle(glm::vec2(500, 0), glm::vec2(20, -25));
    container_.AddParticle(particle);
    container_.TryUpdate(0);
    REQUIRE(container_.GetParticles().at(0).velocity_.y == 25);
  }
  SECTION("Validate TryUpdate, Right side vertical wall, no collision due to incorrect x velocity") {
    GasContainer container_ = GasContainer(0);
    Particle particle = Particle(glm::vec2(700, 250), glm::vec2(-20, -25));
    container_.AddParticle(particle);
    container_.TryUpdate(0);
    REQUIRE(container_.GetParticles().at(0).velocity_.x == -20);
  }
  SECTION("Validate TryUpdate, Horizontal Top Wall") {
    GasContainer container_ = GasContainer(0);
    Particle particle = Particle(glm::vec2(500, 0), glm::vec2(20, 25));
    container_.AddParticle(particle);
    container_.TryUpdate(0);
    REQUIRE(container_.GetParticles().at(0).velocity_.y == 25);
  }
  SECTION("Validate CheckForCollison & CommenceCollision - Particles collide") {
    GasContainer container_ = GasContainer(0);
    Particle particle1 = Particle(glm::vec2(250, 250), glm::vec2(20, -25));
    container_.AddParticle(particle1);
    Particle particle2 = Particle(glm::vec2(250, 256), glm::vec2(20, 25));
    container_.AddParticle(particle2);
    container_.CheckForCollisions();
    glm::vec2 velocity1 = particle1.velocity_ -
                          glm::vec2(((glm::dot((particle1.velocity_ - particle2.velocity_),(particle1.position_ - particle2.position_))) /
                                     (pow(glm::distance(particle1.position_, particle2.position_), 2)))) * (particle1.position_ - particle2.position_);
    REQUIRE(container_.GetParticles().at(0).velocity_.x == velocity1.x);
  }
  SECTION("Validate CheckForCollison - Particles DON'T collide") {
    GasContainer container_ = GasContainer(0);
    Particle particle1 = Particle(glm::vec2(250, 250), glm::vec2(20, -25));
    container_.AddParticle(particle1);
    Particle particle2 = Particle(glm::vec2(256, 256), glm::vec2(20, 25));
    container_.AddParticle(particle2);
    container_.CheckForCollisions();
    glm::vec2 velocity1 = particle1.velocity_ -
                          glm::vec2(((glm::dot((particle1.velocity_ - particle2.velocity_),(particle1.position_ - particle2.position_))) /
                                     (pow(glm::distance(particle1.position_, particle2.position_), 2)))) * (particle1.position_ - particle2.position_);
    REQUIRE(container_.GetParticles().at(0).velocity_.x != velocity1.x);
  }
}
