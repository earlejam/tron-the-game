# tron-the-game
A tron game three classmates and I created for a Tiva C Series Launchpad-powered handheld gaming device. Written in C using the class's provided API.

Project Instructions: 

Our project is modeled as a two player game of the Tron light cycles arcade game. Each player controls a light cycle of a different color that leaves behind a trail of colored light, and the goal of the game is to avoid running into either of these paths of colored light or the outer walls of the arena for longer than your opponent. This can be achieved through sharp turns and trapping of the opposing light cycle. To start the game, the up push-button is pressed at the main title screen. 

After distinguishing which colors the joystick player and push-buttons player will control, a countdown with the LEDs is initiated and the game begins, with each player initially moving towards each other in a direct collision path. The winner will be the player who outlasts his or her opponent (who loses by crashing into a path of light or an outer wall). Players avoid other paths using their respective controls, and player positions are updated in real time on the LCD. 

Upon conclusion of the game, the winner is displayed on the LCD (or a tie if neither player moved and both crashed instantaneously) and the players can elect to play again by pressing the up push-button when initiated.



My Role in the Project:

Initially, I created the title screen and the first half of our official flowchart, and also helped Nick in developing the process of assigning players wirelessly. Moving forward, I put my efforts into the methods that updated the directions / last pressed buttons for each player (for our initial wireless version of the game) as well as combining the versions of the code between what I had and what Justin had. We eventually ran into problems with the wireless module, and after Nick and I debugged and worked through the code for a while, we realized the best decision for our team was to scrap the wireless connectivity and move to a version of the game on a single device. Upon this realization, I rid the code of all signs of wireless and rewrote the methods that updated directions and some global variables, and also put a few of our longer pieces of code in main into methods. Then I manned the keyboard as we all huddled around a single computer to discuss in what order our methods should be called, making changes and debugging as a team. Throughout the process, I was a group member that remained vocal and initiated a lot of conversations about design decisions we had to make, making an effort to get everyone on the same page to confirm that we were moving forward with our best option. I also wrote, coordinated and delivered the commentary for our presentation video.



What I learned from the project: 

One of the most important concepts I learned from lab that I thoroughly applied to this project was troubleshooting code that was not functioning as I had initially expected. The practice I had in lab searching through the provided API for methods, learning things about C that differed from Java, and getting more practice using and differentiating between reference and primitive types helped me write more effective and functional code for this final project. More specifically, I learned more about the functioning of AlertButtons and solidified my understanding of how to effectively draw to the LCD and read both the push-buttons and the joystick's movements to effectively update positions. Finally, I learned how to more effectively work in a team environment where people are writing different sections of code at the same time, and learned how to most effectively blend versions of code into a single, functional version.
