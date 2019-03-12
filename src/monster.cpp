#include "monster.h"
const int BUFFER_HEIGHT = 20;
const int BUFFER_WIDTH = 20;

Monster::Monster() {
	sprite.load("alien.png");
	width = sprite.getWidth();
	height = sprite.getHeight();

	pos.x = ofGetWidth();
	pos.y = ofRandom(2*BUFFER_HEIGHT, ofGetHeight() - 2*BUFFER_HEIGHT);

	this->speed = ofRandom(2, 7);
}

void Monster::draw() {
	sprite.draw(pos.x, pos.y);
}

void Monster::update() {
	pos.x -= speed;
}
