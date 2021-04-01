# Assignment 1 - Computer Graphics
### Nirmal Manoj C
### Roll No.: 2019111011

## How to run?
All the required libraries (freetype, glad, glm, glfw) are already present in the `libraries` folder. Any other dependency of these libraries should be satisifed for the game to run.
After extracting the compressed document, the following commands can be used to compile and run the game.
1.`mkdir build && cd build`
2. `cmake ..`
3. `make`
4. `./Hello-World`

## Instructions
The player starts at the top left corner and an enemy(imposter) exists at a random location in the maze. You can move around the maze using keys `W`, `A`, `S`, `D` for directions North, West, South, and East respectively.

A shape similar to yellow coin is a button to spawn coins and bombs. Hourglass like shape are tasks. In order to do a task, you have to reach the position of the task and press the key `T`. Doing tasks gives an award of 10 points each, while collecting a coin gives 5 points. Vaporizing the imposter will also fetch 5 points for the player. Hitting a bomb will result at a loss of 5 points. If the health points ever go below zero, game is over. When timer hits zero also, the game is over. The exit location at the bottom right corner will be accessible only if a player complete two tasks. 

### Cheats
For easily exploring the game, I have made following cheat codes.
`K` - Kills the imposter.
`O` - Game over with `You lost` message.
`P`  - Game over with `You won` message.
