#include "ofApp.h"
const int BUFFER_HEIGHT = 20;
const int BUFFER_WIDTH = 20;

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Space Impact v2");
	current_state_ = IN_PROGRESS;

	score = 0;

	//used to determine if the explode animation is to be drawn or not
	is_explode = false;
	start_time = ofGetElapsedTimeMillis();

	//helper methods to load required data files
	loadSprites();
	loadMusic();
	loadFonts();
}

//--------------------------------------------------------------
/*
Update function called before every draw
If the function should update when it is called it will:
1. Check to see if the game is in progress, if it is paused or over it should not update.
2. Populize the monster and bullet vectors in accordance to the user's commands
3. Check to see if new enemies should be spawned
4. Determine whether the player has died or not and switch game states accordingly
*/
void ofApp::update() {
	//disables windows resizing
	int window_width = ofGetWidth();
	int window_height = ofGetHeight();

	if (window_width != 640 || window_height != 480) {
		ofSetWindowShape(640, 480);
	}

	if (!(current_state_ == PAUSED || current_state_ == FINISHED)) {
		updateBullets();
		checkShipCollision();

		for (int i = 0; i < monsters.size(); i++) {
			monsters[i].update();
		}

		if (shouldSpawn()) {
			for (int i = 0; i < ofRandom(0, 2); i++) {
				Monster m;
				monsters.push_back(m);
			}
		}

		calculateScore();

		if (ship.lives <= 0) {
			current_state_ = FINISHED;
			updateHighScores(score);
			bg_music.setPaused(true);
			game_over.play();
		}
	}
}

//--------------------------------------------------------------
/*
Draws the current state of the game with the following logic
1. If the game is paused draw the pause screen with a list of high scores
2. If the game is finished draw the game over screen and final score
3. Draw the current position of the player, bullets and enemies (if any)
*/

void ofApp::draw() {
	drawSpace();
	drawLives();
	drawScores();
	drawShip();

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].draw();
	}

	for (int i = 0; i < monsters.size(); i++) {
		monsters[i].draw();
	}

	//draws the explode animation and plays the accompanying sound in accordance to the is_explode boolean variable
	if (is_explode) {
		drawExplosion(explode_point);
		explosion_sound.play();
		explode_point = ofPoint(0, 0);
		is_explode = false;
	}

	if (current_state_ == PAUSED) {
		drawGamePaused();
	}
	else if (current_state_ == FINISHED) {
		drawGameOver();
	}
}

void ofApp::reset() {
	ship = Player();
	bullets.clear();
	monsters.clear();
	score = 0;
	start_time = 0;
	ofResetElapsedTimeCounter();
	bg_music.setPaused(false);
	current_state_ = IN_PROGRESS;
}

//updates the vector of bullets in real time
void ofApp::updateBullets() {
	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].update();

		if (bullets[i].pos.x - bullets[i].width / 2 > ofGetWidth()) {
			bullets.erase(bullets.begin() + i);
		}
	}
	checkBulletCollision();
}

//checks to see if the sprite of a bullet shot by a player has collided with a monster sprite using the ofDist method. If true, erases both the bullet and the monster from their respective vectors and triggers an explosion
void ofApp::checkBulletCollision() {
	for (int i = 0; i < bullets.size(); i++) {
		for (int e = 0; e < monsters.size(); e++) {
			if (ofDist(bullets[i].pos.x, bullets[i].pos.y, monsters[e].pos.x, monsters[e].pos.y) < (monsters[e].width + bullets[i].width) / 2) {
				explode_point = monsters[e].pos;

				monsters.erase(monsters.begin() + e);
				bullets.erase(bullets.begin() + i);

				is_explode = true;
				break;
			}
		}
	}
}

//checks to see if the sprite of the player's ship has collided with a monster sprite using the ofDist method. If true, the player loses a life and the monster is erased.
void ofApp::checkShipCollision() {
	for (int e = 0; e < monsters.size(); e++) {
		if (ofDist(ship.pos.x, ship.pos.y, monsters[e].pos.x, monsters[e].pos.y) < (monsters[e].width + ship.width) / 2) {
			monsters.erase(monsters.begin() + e);
			ship.lives--;
			damage.play();
			break;
		}
	}
}

//determines whether a monster should be drawn on screen or not deoending the elapsed time
bool ofApp::shouldSpawn() {
	if (ofGetElapsedTimeMillis() - start_time > interval_time) {
		start_time = ofGetElapsedTimeMillis();
		return true;
	}
	return false;
}

/*
Function that handles actions based on user key presses
1. if key == p and game is not over, toggle pause
2. if game is in progress handle WASD action
3. if key == r and game is over reset it

WASD logic:
Let dir be the direction that corresponds to a key
Update direction of the ship and force a game update as appropriate to dir
*/
void ofApp::keyPressed(int key) {
	int upper_key = toupper(key); // Standardize on upper case

	if ((upper_key == 'P') && current_state_ != FINISHED) {
		// Pause or unpause
		if (current_state_ == IN_PROGRESS) {
			current_state_ = PAUSED;
			bg_music.setPaused(true); //pauses music when the game is paused
		}
		else {
			current_state_ = IN_PROGRESS;
			bg_music.setPaused(false); //continues playing music when the game is unpaused
		}
	}
	else if (current_state_ == IN_PROGRESS) {
		// If current direction has changed to a valid new one, force an immediate update and skip the next frame update
		if (upper_key == 'A' && ship.pos.x > 0.0) {
			ship.pos.x = ship.pos.x - ship.sprite.getWidth();
		}
		else if (upper_key == 'D' && (ship.pos.x + ship.sprite.getWidth() < ofGetWidth() - BUFFER_WIDTH)) {
			ship.pos.x = ship.pos.x + ship.sprite.getWidth();
		}
		else if (upper_key == 'W' && (ship.pos.y - ship.sprite.getHeight() > 2 * BUFFER_HEIGHT)) {
			ship.pos.y = ship.pos.y - ship.sprite.getHeight();
		}
		else if (upper_key == 'S' && (ship.pos.y + ship.sprite.getHeight() < ofGetHeight() - BUFFER_HEIGHT)) {
			ship.pos.y = ship.pos.y + ship.sprite.getHeight();
		}

		if (key == ' ') {
			Bullet b(ship.pos, ship.speed);
			bullets.push_back(b);
			laser.play();
		}
	}
	else if (upper_key == 'R' && current_state_ == FINISHED) {
		reset();
	}
}

void ofApp::loadSprites() {
	space.load("space.png");
}

void ofApp::loadMusic() {
	bg_music.load("space-music.mp3");
	laser.load("laser.wav");
	explosion_sound.load("explosion.wav");
	damage.load("damage.mp3");
	game_over.load("gameover.mp3");

	bg_music.play();
}

void ofApp::loadFonts() {
	score_font.load("arcade.ttf", 20);
}

void ofApp::drawSpace() {
	space.draw(0, 0);
}

void ofApp::drawShip() {
	ship.sprite.draw(ship.pos.x, ship.pos.y);
}

//draws the player's health bar at the top left side of the game windows
void ofApp::drawLives() {
	for (int i = 0; i < ship.lives; i++) {
		ship.sprite.draw(30 + (i * 35), 20);
	}
}

//draws the player's score at the top right side of the game windows
void ofApp::drawScores() {
	if (current_state_ == IN_PROGRESS) {
		string scorestring = "Score: " + ofToString(score);
		score_font.drawString(scorestring, 500, 40);
	}
	else if (current_state_ == FINISHED) {
		float string_width = score_font.stringWidth(ofToString(score));
		score_font.drawString(ofToString(score), ofGetWidth() / 2 - string_width / 2, ofGetHeight() / 2);
	}
}

//draws an explosion at the specified position
void ofApp::drawExplosion(ofPoint pos) {
	explosion.load("explosion2.png");
	explosion.draw(pos.x, pos.y);
	explosion.clear();
}

//draws pause screen and displays a list of high scores
void ofApp::drawGamePaused() {
	string pause_message = "P to Unpause!\n High SCORES:";
	float string_width = score_font.stringWidth(pause_message);
	score_font.drawString(pause_message, ofGetWindowWidth() / 2 - string_width / 2, ofGetWindowHeight() / 2);

	int count = 0;
	int y_pos = 2.5*BUFFER_HEIGHT + ofGetWindowHeight() / 2;
	while (count < high_scores.size()) {
		string high_score_string = std::to_string(count + 1) + ": " + std::to_string(high_scores.at(count));
		float string_width = score_font.stringWidth(high_score_string);
		score_font.drawString(high_score_string, ofGetWindowWidth() / 2 - string_width / 2, y_pos);
		y_pos += BUFFER_HEIGHT;
		count++;
	}
}

//draws game end screen
void ofApp::drawGameOver() {
	string lose_message = "Game Over! Your Final Score is: ";
	float string_width = score_font.stringWidth(lose_message);
	score_font.drawString(lose_message, ofGetWindowWidth() / 2 - string_width / 2, ofGetWindowHeight() / 2 - BUFFER_HEIGHT);
}

//updates the vector of high scores. If the length of the vector is greater than 5, removes unrequired scores
void ofApp::updateHighScores(int score) {
	high_scores.push_back(score);
	std::sort(high_scores.rbegin(), high_scores.rend());

	if (high_scores.size() > 5) {
		high_scores.pop_back();
	}
}

//calculates the player's core based on the time played
void ofApp::calculateScore() {
	score = (2 * ofGetElapsedTimeMillis()) / 1000;
}