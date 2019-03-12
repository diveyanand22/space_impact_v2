# Project Proposal
For my final project, I will create a 2D shooter game modelled after Space Impact (think Nokia brick phones), which I'll continue working on during the summer. 
![Space Impact Screenshot](https://i1.imgiz.com/rshots/8833/efsanevi-nokia-3310-oyunu-space-impact_8833969-72540_640x360.jpg) 

The game involves the player controlling a spaceship inside a fixed window. Enemy ships and monsters spawn at the right side of the window and the player has to shoot them down before they come into contact with the player's ship. If the enemies do come in contact with the player's ship, the player loses a life. After the player has lost 3 lives, the game ends immediately with a splash screen. The player's score depends on how far they have moved (could also be time dependent) and is tracked in real time. Ther is also a functionality to store the top 10 highscores with 3 character player identities linked to them.

For now, I will try to focus on implementing: 
* the game window
* player movement
* projectile shooting
* tracking player health and scores
* enemies which enter the window from the right side at a random height  

I will be using the [SFML](https://www.sfml-dev.org/) game development library for my project. I'll also use OpenFrameworks to implement some of the visual elements of my game.

I think working on the Snake game has goven me a good background to work on flat 2-D games and the experience will certainly prove useful when I get into developing my game.
