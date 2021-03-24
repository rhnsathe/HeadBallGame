//
// Created by Rohan Sathe on 3/23/21.
//

#include <catch2/catch.hpp>
#include "gas_container.h"
#include "particle.h"
#include "histogram.h"

using idealgas::GasContainer;
using idealgas::Particle;
using idealgas::Histogram;
using glm::vec2;

TEST_CASE("Histogram information tests") {
  GasContainer container1 = GasContainer(0);
  idealgas::Particle particle = Particle();
  container1.AddParticle(particle);
  SECTION("Test for default characteristics - color") {
    REQUIRE(container1.GetParticles()[0].color_ == (cinder::Color)"blue");
  }
  SECTION("Test for default characteristics - mass") {
    REQUIRE(container1.GetParticles()[0].mass_ == 5);
  }
  SECTION("Test for default characteristics - radius") {
    REQUIRE(container1.GetParticles()[0].radius_ == 8);
  }
  GasContainer container2 = GasContainer(0);
  idealgas::Particle particle2 = Particle((cinder::Color)"red", 10, 9);
  container2.AddParticle(particle2);
  SECTION("Test for manual characteristics - color") {
    REQUIRE(container2.GetParticles()[0].color_ == (cinder::Color)"red");
  }
  SECTION("Test for manual characteristics - mass") {
    REQUIRE(container2.GetParticles()[0].mass_ == 9);
  }
  SECTION("Test for manual characteristics - radius") {
    REQUIRE(container2.GetParticles()[0].radius_ == 10);
  }
}

TEST_CASE("Histogram instance variable tests") {
  SECTION("Histogram - ensure num_blue_ is appropriately sized") {
    GasContainer container = GasContainer(0);
    idealgas::Particle particle = Particle((cinder::Color)"blue", 8, 5);
    container.AddParticle(particle);
    Histogram histogram = Histogram(container.GetParticles(), 1);
    REQUIRE(histogram.GetNumBlue().size() == 1);
  }
  SECTION("Histogram - ensure num_green_ is appropriately sized") {
    GasContainer container = GasContainer(0);
    idealgas::Particle particle1 = Particle((cinder::Color)"green", 8, 5);
    container.AddParticle(particle1);
    idealgas::Particle particle2 = Particle((cinder::Color)"green", 8, 5);
    container.AddParticle(particle2);
    Histogram histogram = Histogram(container.GetParticles(), 2);
    REQUIRE(histogram.GetNumGreen().size() == 2);
  }
  SECTION("Histogram - ensure num_orange_ is appropriately sized") {
    GasContainer container = GasContainer(0);
    idealgas::Particle particle1 = Particle((cinder::Color)"orange", 8, 5);
    container.AddParticle(particle1);
    idealgas::Particle particle2 = Particle((cinder::Color)"orange", 8, 5);
    container.AddParticle(particle2);
    idealgas::Particle particle3 = Particle((cinder::Color)"orange", 8, 5);
    container.AddParticle(particle3);
    Histogram histogram = Histogram(container.GetParticles(), 3);
    REQUIRE(histogram.GetNumOrange().size() == 3);
  }
}
