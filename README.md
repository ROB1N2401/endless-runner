# Endless Runner - Game Project in 2D

## Controls

* P - Pause;
* SPACE - Jump;
* ESC - Close application;

## Description 

The goal of this assignment was to write an [endless runner](https://en.wikipedia.org/wiki/Platform_game#Endless_running_games) game in 2D, using C++ and SDL, with an emphasis on *game feel*. An endless runner is a specialization of the platformer genre where the player is always moving forwards until some endgame condition is met. 
The game features only a single mechanic of jumping. However, since it was based upon an empty SDL library, all features were implemented on my own: from camera to animations. 

## Features

* Game loop and character are implemented with the usage of Finite State-Machine (FSM), written on C++
* Collision detection and resolve
* Keyframe animation 
* 6-layer parallax background
* Audio manager
* Adjustable game settings (through cfg files) 
* Easing functions for UI animations and camera shake FX
