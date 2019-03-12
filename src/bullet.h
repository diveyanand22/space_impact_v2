#pragma once
#include <ofMain.h>

class Bullet {
public:
	ofImage sprite;
	ofPoint pos;

	float speed;
	float width; //width of the sprite
	float height; //height of the sprite

	//parametrized constructor
	Bullet(ofPoint pos, float speed);
	void draw();
	void update();
};