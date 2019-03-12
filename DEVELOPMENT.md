04/20: 
  * Started work on final project. 
  * Had trouble with updating my project with OpenFrameworks: main.cpp, ofApp.cpp and ofApp.h were not being generated. Resolved by creating a new blank project and copying necessary files to the provided repo. Worked successfully
  * Initially, the player's interactions were modelled using a sprite, but that went against the principles of OOP, and so I defined the player class
  * Added background music using the ofSoundPlayer class to add authenticity to the game
  * Initially, moving the sprite in certain ways could cause it to go out of the window's bounds. Fixed by adding necessary conditions in the *keyPressed(int key)* method
  * Getting __"unorthodox syntax"__ build errors when trying to register keypress events. To be fixed


 05/02
  * Fixed build errors by restructuring code
  * Finalised object decomposition into player, bullet and monster classes
  * Started using ofPoint to track objects instead of usiing the sprites coordinates. This made it much easier to write position based event funtions
  * Added sprites of bullets and monsters
  * Implemented projectile shooting using by keeping vectors of bullets and monsters maintained in real-time 
  * Implemented bullet-monster and player-monster collisions using the ofDist() method
  * Added sound effects using ofSoundPlayer
  * Added custom font for more arcadey aesthetic
  * Added picture based health bar for the player
  * Initially had trouble in implementing position/event based drawing. Done easily once ofPoint variables were integrated into the classes
  * Disabled windows resizing
  * Tried to implement more random looking monster sprite movement using the sine and cosine functions. Removed for non-optimal results
  * Added time based events such as score calculation and monster spawning using the ofGetElapsedTimeMillis() and ofGetElapsedTimef() util methods
  * Had trouble in getting the drawGamePaused() and drawGameOver() methods to work right. Corrected by reordering draw methods.
  * Implemented functionality to keep record of top 5 high scores and diplaying them in the pause menu using a vector
  * Disabled window resizing to prevent unsightly scaling
  * Added comments to make the solution more readable