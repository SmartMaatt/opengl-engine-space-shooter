## Description
The idea behind the project is to create a simple Space Shooter game in the OpenGL graphics API. The main goal of the user is to collect all the crystals suspended from space, thus being careful of the surrounding meteorites. The player has the option to avoid the rocks or destroy them with a long-reload proton cannon. 

An important graphical element of the application is the concept of playing with light. The game is equipped with a dymanic lighting system with reflections. This allowed the implementation of a system for finding crystals through the light they emit in dark space. In addition, the ship and the proton torpedo are a source of their own light of different colours, which in combination creates a spectacular cosmic effect.

## Screenshots

![App Screenshot](https://i.ibb.co/1MtD8TV/Screenshot-1.png)

![App Screenshot](https://i.ibb.co/ThCd3pX/Screenshot-2.png)


## Main features of the game
The main objective of the completed game is to collect 5 collectible objects, which are crystals, while avoiding obstacle objects - asteroids. Getting into a situation where the player collides with an obstacle is punished with the loss of 20 health points. Crystals in space can be found thanks to the glow of light they emit. It is possible to eliminate obstacles using the laser beam that is the projectile of the user's ship, but this interaction has a certain cooldown - 8 seconds.
## User manual
The only options available in the start menu are to start the game and exit the application. These are selected using the mouse.

By activating the gameplay mode, the user switches to a control system that depends mostly on keyboard inputs. Preset keys include:
* W - moving the ship forward,
* S - move the ship backwards,
* A - move the ship left,
* D - move the ship to the right,
* Spacebar - move the ship up,
* Shift - move the ship down,
* F - use missile,
* Q - enable triangular object grid display mode,
* E - deactivate triangular object grid display mode,
* H - activate or deactivate the ship model,
* ESC - exit the application.
Camera rotation depends on user's mouse movements.
## Libraries
* **FreeType** - read the font file and generate text dynamically
* **glm** - accessing operations and mathematical entities
* **glfw3** - activating windows, contexts and surfaces, reading input, handling events
* **Glad** - system function address code generator.
* **Blender program** - editing/improving models used
* **Gimp program** - editing/improving used textures
## Additional technical information

The application contains a script that imports and loads models of objects in space such as meteorites and crystals. The objects were inserted into the application from .obj files previously prepared in Blender. In addition, it was equipped with the ability to apply a basic texture (colour/layer), specular and normal map to any object.

The game features a dynamic spotlight system with variable values of intensity, radius and colour. The sources of these lights are located in the instances of the objects crystals, projectiles and the ship.