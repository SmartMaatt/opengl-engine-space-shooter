<h1 align="center"> Space Shooter Game - OpenGL Engine</h1>

<p align="center">
  <a href="#overview">Overview</a> •
  <a href="#screenshots">Screenshots</a> •
  <a href="#key-features">Key Features</a> •
  <a href="#technical-specifications">Technical Specifications</a> •
  <a href="#license">License</a>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/License-MIT-yellow.svg" />
  <img src="https://img.shields.io/badge/Author-SmartMatt-blue" />
</p>

## Overview
This Space Shooter game, developed in the OpenGL graphics API, is an immersive experience where the player navigates a spaceship through space, collecting crystals and avoiding meteorites. The game stands out for its dynamic lighting system, which not only enhances the visual appeal but also plays a crucial role in gameplay mechanics.

### Repository Contents
This repository not only contains the game but also showcases the capabilities of the custom-built mini-engine, demonstrating functionalities such as dynamic lighting, prefab system, rendering techniques, and more, all developed to offer a game engine-like experience without a graphical user interface.

## Screenshots
![Game presentation](https://smartmatt.pl/github/opengl-space-shooter-game/opengl-space-shooter-game%202.png)
*Early game stage.*

![Collecting crystals](https://smartmatt.pl/github/opengl-space-shooter-game/opengl-space-shooter-game%203.png)
*Collecting crystals.*

![Shooting projectile](https://smartmatt.pl/github/opengl-space-shooter-game/opengl-space-shooter-game%204.png)
*Shooting light projectile.*

![Main menu](https://smartmatt.pl/github/opengl-space-shooter-game/opengl-space-shooter-game%201.png)
*Main menu presentation.*

## Key Features
### Gameplay
- **Objective**: Collect 5 crystals while avoiding asteroid collisions.
- **Health System**: Colliding with asteroids results in a loss of 20 health points.
- **Crystal Detection**: Crystals emit a glow, aiding in their detection in the dark space.
- **Weapon System**: Destroy asteroids using a proton cannon with an 8-second cooldown.

### Graphics and Lighting
- **Dynamic Lighting**: A system that creates stunning cosmic effects and aids in gameplay.
- **Special Effects**: Ship and proton torpedo emit their own distinctive light, contributing to the game's visual appeal.

### User Interface
- **Start Menu**: Simple options to start the game or exit.
- **Control System**: Keyboard controls for ship navigation and actions.
- **Camera**: Mouse-controlled for intuitive rotation and viewing angles.

### Controls
- `W`/`S`: Move the ship forward/backward.
- `A`/`D`: Move the ship left/right.
- `Spacebar`: Move the ship up.
- `Shift`: Move the ship down.
- `F`: Fire proton cannon.
- `Q`/`E`: Toggle triangular object grid display.
- `H`: Toggle ship model visibility.
- `ESC`: Exit the game.

## Technical Specifications
### Libraries
- **FreeType**: For font rendering.
- **glm**: Mathematical operations and entities.
- **glfw3**: Window, context, and event handling.
- **Glad**: OpenGL function loader.
- **Blender**: Object modeling.
- **Gimp**: Texture editing.

### Engine Features
- **Dynamic Light Mechanism**: Spotlight system with variable intensity, radius, and color.
- **Prefab System**: Similar to Unity, allowing object reuse and management.
- **Rendering and Mesh Indexing Systems**: Efficient graphical rendering.
- **Material Creation**: Various shaders and parameters for material customization.
- **Buffer Management**: Automatic handling of graphical buffers.
- **Skybox Creation**: Enhances the environmental setting.
- **Scene Management**: State machine-based system for scene transitions.
- **Static Mathematical and Debugging Libraries**: For efficient calculations and debugging.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---
&copy; 2023 Mateusz Płonka (SmartMatt). All rights reserved.
<a href="https://smartmatt.pl/">
    <img src="https://smartmatt.pl/github/smartmatt-logo.png" title="SmartMatt Logo" align="right" width="60" />
</a>

<p align="left">
  <a href="https://smartmatt.pl/">Portfolio</a> •
  <a href="https://github.com/SmartMaatt">GitHub</a> •
  <a href="https://www.linkedin.com/in/mateusz-p%C5%82onka-328a48214/">LinkedIn</a> •
  <a href="https://www.youtube.com/user/SmartHDesigner">YouTube</a> •
  <a href="https://www.tiktok.com/@smartmaatt">TikTok</a>
</p>
