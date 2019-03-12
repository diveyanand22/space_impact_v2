#include "player.h"

Player::Player() {
	sprite.load("ship.png");
	lives = 3;
	speed = 32;

	pos.x = 0;
	pos.y = 60;
}
