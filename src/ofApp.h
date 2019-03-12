#pragma once

#include "ofMain.h"
#include "player.h"
#include "bullet.h"
#include "monster.h"

// Enum to represent the current state of the game
enum GameState {
	IN_PROGRESS = 0,
	PAUSED,
	FINISHED
};

class ofApp : public ofBaseApp{
private:
	GameState current_state_; // The current state of the game, used to determine possible actions
	Player ship;

public:
	//data objects used as game assets
	ofImage space;
	ofImage explosion;
	ofPoint explode_point;
	ofSoundPlayer bg_music;
	ofSoundPlayer laser;
	ofSoundPlayer explosion_sound;
	ofSoundPlayer damage;
	ofSoundPlayer game_over;
	ofTrueTypeFont score_font;

	int score;
	float start_time;
	float interval_time = 1000; //interval between spawning a new monster
	vector<Bullet> bullets;
	vector<Monster> monsters;
	bool is_explode;
	vector<int> high_scores;

	void setup();
	void update();
	void draw();
	void reset();
	void updateBullets();

	void loadSprites();
	void loadMusic();
	void loadFonts();

	void drawGamePaused();
	void drawGameOver();
	void drawSpace();
	void drawShip();
	void drawScores();
	void drawLives();
	void drawExplosion(ofPoint);
	
	// Event driven functions, called on appropriate user action
	void keyPressed(int key);

	bool shouldSpawn();
	void checkBulletCollision();
	void checkShipCollision();
	void calculateScore();
	void updateHighScores(int score_to_be_added);
};
