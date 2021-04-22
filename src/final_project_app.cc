#include "final_project_app.h"

#include "cinder/gl/gl.h"

namespace finalproject {

FinalProjectApp::FinalProjectApp() {
  ci::app::setWindowSize(kXWindowSize, kYWindowSize);
}

void FinalProjectApp::draw() {
  ci::Color background_color("dodgerblue");
  ci::gl::clear(background_color);

  backgroundDesign_.Display();
}

void FinalProjectApp::update() {
  //container_.AdvanceOneFrame();
}

}  // namespace idealgas
