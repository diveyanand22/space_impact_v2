#include "bullet.h"

Bullet::Bullet(ofPoint p, float s) {
	sprite.load("bullet.png");
	pos = p;
	speed = s;
	width = sprite.getWidth();
	height = sprite.getHeight();
}

void Bullet::draw() {
	sprite.draw(pos.x - width / 2, pos.y - height / 2, width, height);
}

void Bullet::update() {
	pos.x += speed;
	pos.y -= 0;
}