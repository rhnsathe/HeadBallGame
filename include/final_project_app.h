#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
//#include "gas_container.h"
#include "background_design.h"

namespace finalproject {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class FinalProjectApp : public ci::app::App {
 public:
  FinalProjectApp();

  void draw() override;
  void update() override;

  // provided that you can see the entire UI on your screen.
  const int kXWindowSize = 1800;
  const int kYWindowSize = 900;
  const int kMargin = 100;

  /**
   * Initializes the gas_container with a certain number of particles.
   */
 private:

  /**
   * Constructor to initialize a gas container with a certain number of particles.
   */
   BackgroundDesign backgroundDesign_ = BackgroundDesign();
};

}  // namespace idealgas
