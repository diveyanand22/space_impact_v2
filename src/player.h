#include <ofMain.h>
#pragma once

class Player {
public:
	ofImage sprite;
	ofPoint pos;

	int lives;
	float width; //width of the sprite
	float height; //height of the sprite
	float speed; //speed at which the player travels

	//default constructor
	Player();
};