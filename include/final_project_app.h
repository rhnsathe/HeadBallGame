#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
//#include "gas_container.h"
#include "background_design.h"
#include "player.h"

namespace finalproject {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class FinalProjectApp : public ci::app::App {
 public:
  FinalProjectApp();

  void draw() override;
  void update() override;
  void keyDown(ci::app::KeyEvent event) override;
  void checkIfPlayerUp();
  bool checkIfGoalScored();

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
   bool player_one_move_up_ = false;
   bool player_two_move_up_ = false;
   size_t player_one_score_ = 0;
   size_t player_two_score_ = 0;
   double distanceBetweenRadii = 0.0;
   double distanceBetweenRadii2 = 0.0;
   finalproject::Player ball_ = Player(1);
   finalproject::Player player_one_ = Player('p');
   finalproject::Player player_two_ = Player('o');
};

}  // namespace idealgas
