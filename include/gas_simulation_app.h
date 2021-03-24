#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int kWindowSize = 1200;
  const int kMargin = 100;

  /**
   * Initializes the gas_container with a certain number of particles.
   */
 private:
  /**
   * Number of particles in the container.
   */
  const size_t kNumParticles = 150;

  /**
   * Constructor to initialize a gas container with a certain number of particles.
   */
  GasContainer container_ = GasContainer(kNumParticles);
};

}  // namespace idealgas
