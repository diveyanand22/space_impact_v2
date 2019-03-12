#pragma once
#include <ofMain.h>

class Monster{
	
public:
	ofImage sprite;
	ofPoint pos;

	float speed; //speed at which the monster travels
	float width; //width of the sprite
	float height; //height of the sprite

	//default constructor
	Monster();
	void draw();
	void update();
};