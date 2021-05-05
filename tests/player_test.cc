#include <catch2/catch.hpp>

#include "player.h"

using finalproject::Player;
using glm::vec2;

TEST_CASE("Test ball constructor") {
  Player player = Player(0);
  REQUIRE(player.ball_position_.x == 900);
  REQUIRE(player.ball_position_.y == 500);
}

TEST_CASE("Test player constructor - purple") {
  SECTION("lowercase p") {
    Player player = Player('p');
    REQUIRE(player.player_top_position_ == glm::vec2(1350, 535));
    REQUIRE(player.player_bottom_position_ == glm::vec2(1350,610));
  }
  SECTION("Uppercase P") {
    Player player = Player('P');
    REQUIRE(player.player_top_position_ == glm::vec2(1350, 535));
    REQUIRE(player.player_bottom_position_ == glm::vec2(1350,610));
  }
}

TEST_CASE("Test player constructor - orange") {
  SECTION("lowercase o") {
    Player player = Player('o');
    REQUIRE(player.player_top_position_ == glm::vec2(450,535));
    REQUIRE(player.player_bottom_position_ == glm::vec2(450,610));
  }
  SECTION("Uppercase O") {
    Player player = Player('o');
    REQUIRE(player.player_top_position_ == glm::vec2(450,535));
    REQUIRE(player.player_bottom_position_ == glm::vec2(450,610));
  }
}

TEST_CASE("Test kick methods") {
  SECTION("Test left kick") {
    Player player = Player('p');
    Player ball = Player(0);
    player.InitiateSpecialLeftKick(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-30,-20));
    player.InitiateSpecialLeftKick(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-60,-40));
  }
  SECTION("Test right kick") {
    Player player = Player('p');
    Player ball = Player(0);
    player.InitiateSpecialRightKick(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(30,-20));
    player.InitiateSpecialRightKick(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(60,-40));
  }
}

TEST_CASE("Test move methods") {
  SECTION("Move player left") {
    Player player = Player('p');
    player.MovePlayerLeft();
    REQUIRE(player.player_top_position_.x == 1338);
    REQUIRE(player.player_bottom_position_.x == 1338);
    REQUIRE(player.player_top_velocity_.x == -12);
    REQUIRE(player.player_bottom_velocity_.x == -12);
    player.MovePlayerLeft();
    REQUIRE(player.player_top_position_.x == 1326);
    REQUIRE(player.player_bottom_position_.x == 1326);
    REQUIRE(player.player_top_velocity_.x == -24);
    REQUIRE(player.player_bottom_velocity_.x == -24);
  }
  SECTION("Move player right") {
    Player player = Player('p');
    player.MovePlayerRight();
    REQUIRE(player.player_top_position_.x == 1362);
    REQUIRE(player.player_bottom_position_.x == 1362);
    REQUIRE(player.player_top_velocity_.x == 12);
    REQUIRE(player.player_bottom_velocity_.x == 12);
    player.MovePlayerRight();
    REQUIRE(player.player_top_position_.x == 1374);
    REQUIRE(player.player_bottom_position_.x == 1374);
    REQUIRE(player.player_top_velocity_.x == 24);
    REQUIRE(player.player_bottom_velocity_.x == 24);
  }
  SECTION("Move player up & down") {
    Player player = Player('p');
    player.MovePlayerUp();
    REQUIRE(player.player_top_position_.y == 385);
    REQUIRE(player.player_bottom_position_.y == 460);
    REQUIRE(player.player_top_velocity_.y == -12);
    REQUIRE(player.player_bottom_velocity_.y == -12);
    player.MovePlayerWithGravity();
    REQUIRE(player.player_top_position_.y == 392.5);
    REQUIRE(player.player_bottom_position_.y == 467.5);
    REQUIRE(player.player_top_velocity_.y == -11.5);
    REQUIRE(player.player_bottom_velocity_.y == -11.5);
  }
}

TEST_CASE("Test collision with ball") {
  Player purple_player = Player('p');
  //Player orange_player = Player('o');
  Player ball = Player(0);
  SECTION("Ensure false when temp_disablement != 0") {
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,1) == false);
  }
  SECTION("Ensure false at initialization") {
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == false);
  }
  SECTION("Ball collision with top of purple head - double positive velocity") {
    purple_player.player_top_position_ = glm::vec2(450,450);
    ball.ball_position_ = glm::vec2(440,460);
    purple_player.player_top_velocity_.x = 10;
    ball.ball_velocity_.x = 10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(20,0));
  }
  SECTION("Ball collision with top of purple head - double negative velocity") {
    purple_player.player_top_position_ = glm::vec2(450,450);
    ball.ball_position_ = glm::vec2(440,460);
    purple_player.player_top_velocity_.x = -10;
    ball.ball_velocity_.x = -10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(-20,0));
  }
  SECTION("Ball collision with top of purple head - velocities with opposite signs") {
    purple_player.player_top_position_ = glm::vec2(450,450);
    ball.ball_position_ = glm::vec2(440,460);
    purple_player.player_top_velocity_.x = -10;
    ball.ball_velocity_.x = 10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(-10,0));
  }
  SECTION("Ball collision with bottom of purple head - double positive velocity") {
    purple_player.player_bottom_position_ = glm::vec2(450,600);
    ball.ball_position_ = glm::vec2(440,610);
    purple_player.player_bottom_velocity_.x = 10;
    ball.ball_velocity_.x = 10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(20,0));
  }
  SECTION("Ball collision with bottom of purple head - double negative velocity") {
    purple_player.player_bottom_position_ = glm::vec2(450,600);
    ball.ball_position_ = glm::vec2(440,620);
    purple_player.player_bottom_velocity_.x = -10;
    ball.ball_velocity_.x = -10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(-20,0));
  }
  SECTION("Ball collision with bottom of purple head - velocities with opposite signs") {
    purple_player.player_bottom_position_ = glm::vec2(450,450);
    ball.ball_position_ = glm::vec2(440,460);
    purple_player.player_bottom_velocity_.x = -10;
    ball.ball_velocity_.x = 10;
    REQUIRE(ball.CheckForCollisionWithBall(purple_player,ball,0) == true);
    REQUIRE(ball.ball_velocity_ == vec2(-10,0));
  }
}

TEST_CASE("Test ball collision with ball") {
  Player ball = Player(0);
  SECTION("Collision with right wall w/ correct velocity") {
    ball.ball_position_ = glm::vec2(1780,300);
    ball.ball_velocity_ = glm::vec2(10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-10,5));
  }
  SECTION("Collision with right wall w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(1780,300);
    ball.ball_velocity_ = glm::vec2(-10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-10,5));
  }
  SECTION("Collision with left wall w/ correct velocity") {
    ball.ball_position_ = glm::vec2(20,300);
    ball.ball_velocity_ = glm::vec2(-10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,5));
  }
  SECTION("Collision with left wall w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(20,300);
    ball.ball_velocity_ = glm::vec2(10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,5));
  }
  SECTION("Collision with upper wall w/ correct velocity") {
    ball.ball_position_ = glm::vec2(500,20);
    ball.ball_velocity_ = glm::vec2(10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,5));
  }
  SECTION("Collision with upper wall w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(20,300);
    ball.ball_velocity_ = glm::vec2(10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,5));
  }
  SECTION("Collision with lower wall w/ correct velocity") {
    ball.ball_position_ = glm::vec2(500,640);
    ball.ball_velocity_ = glm::vec2(10,5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,-5));
  }
  SECTION("Collision with lower wall w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(500,640);
    ball.ball_velocity_ = glm::vec2(10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,-5));
  }
  SECTION("Collision with left crossbar w/ correct velocity") {
    ball.ball_position_ = glm::vec2(200,200);
    ball.ball_velocity_ = glm::vec2(-10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,-5));
  }
  SECTION("Collision with left crossbar w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(200,200);
    ball.ball_velocity_ = glm::vec2(10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(10,-5));
  }
  SECTION("Collision with right crossbar w/ correct velocity") {
    ball.ball_position_ = glm::vec2(1600,200);
    ball.ball_velocity_ = glm::vec2(10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-10,-5));
  }
  SECTION("Collision with right crossbar w/ incorrect velocity") {
    ball.ball_position_ = glm::vec2(1600,200);
    ball.ball_velocity_ = glm::vec2(-10,-5);
    ball.CheckForCollisionWithWall(ball);
    REQUIRE(ball.ball_velocity_ == glm::vec2(-10,-5));
  }
}

TEST_CASE("Test regulate player velocity") {
  SECTION("Test player x velocity > 0") {
    Player player = Player('p');
    player.player_top_velocity_ = glm::vec2(5,0);
    player.player_bottom_velocity_ = glm::vec2(5,0);
    player.RegulatePlayerVelocity(player);
    REQUIRE(player.player_top_velocity_.x == 3.5);
    REQUIRE(player.player_bottom_velocity_.x == 3.5);
  }
  SECTION("Test player x velocity < 0") {
    Player player = Player('p');
    player.player_top_velocity_ = glm::vec2(-5,0);
    player.player_bottom_velocity_ = glm::vec2(-5,0);
    player.RegulatePlayerVelocity(player);
    REQUIRE(player.player_top_velocity_.x == -3.5);
    REQUIRE(player.player_bottom_velocity_.x == -3.5);
  }
}