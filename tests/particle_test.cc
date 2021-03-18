#include <catch2/catch.hpp>

#include <particle.h>

using idealgas::Particle;

TEST_CASE("Position and velocity test") {
  Particle particle;
  SECTION("Position fits x upper bound") {
    REQUIRE(particle.position_.x < (particle.kHeightAndWidth - particle.kRadius));
  }
  SECTION("Position fits x lower bound") {
    REQUIRE(particle.position_.x > particle.kRadius);
  }
  SECTION("Velocity fits x lower bound") {
    REQUIRE(particle.velocity_.x >= particle.GetKLowerVelocityBound());
  }
  SECTION("Velocity fits x upper bound") {
    REQUIRE(particle.velocity_.x < particle.GetKLowerVelocityBound() + particle.GetKVelocityRange());
  }
  SECTION("Position fits y upper bound") {
    REQUIRE(particle.position_.y < (particle.kHeightAndWidth - particle.kRadius));
  }
  SECTION("Position fits y lower bound") {
    REQUIRE(particle.position_.y > particle.kRadius);
  }
  SECTION("Velocity fits y lower bound") {
    REQUIRE(particle.velocity_.y >= particle.GetKLowerVelocityBound());
  }
  SECTION("Velocity fits y upper bound") {
    REQUIRE(particle.velocity_.y < particle.GetKLowerVelocityBound() + particle.GetKVelocityRange());
  }
}
