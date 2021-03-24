#include <catch2/catch.hpp>

#include <particle.h>

using idealgas::Particle;

TEST_CASE("Position and velocity test") {
  Particle particle;
  SECTION("Position fits x upper bound") {
    REQUIRE(particle.position_.x < (particle.kWidth - particle.radius_));
  }
  SECTION("Position fits x lower bound") {
    REQUIRE(particle.position_.x > particle.radius_);
  }
  SECTION("Velocity fits x lower bound") {
    REQUIRE(particle.velocity_.x >= particle.GetKLowerVelocityBound());
  }
  SECTION("Velocity fits x upper bound") {
    REQUIRE(particle.velocity_.x < particle.GetKLowerVelocityBound() + particle.GetKVelocityRange());
  }
  SECTION("Position fits y upper bound") {
    REQUIRE(particle.position_.y < (particle.kHeight - particle.radius_));
  }
  SECTION("Position fits y lower bound") {
    REQUIRE(particle.position_.y > particle.radius_);
  }
  SECTION("Velocity fits y lower bound") {
    REQUIRE(particle.velocity_.y >= particle.GetKLowerVelocityBound());
  }
  SECTION("Velocity fits y upper bound") {
    REQUIRE(particle.velocity_.y < particle.GetKLowerVelocityBound() + particle.GetKVelocityRange());
  }
}
