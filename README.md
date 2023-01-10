# RoadSMHUP
A 2D Car SHMUP as OpenGL / Game programming practice. 

## The Initial Scope 

This is a simple SHMUP Game base to quickly experiment with various parts of game programming without having to make a dive to a more complex topics in 3D. 

## Current targets:

  - Builds nicely in Visual Studio 2022 from the git
  - Runs a simple SHMUP that allows experimentation with various APIs and features without too much hassle. 
 

## Building and running

ROADSHMUP is currently tested mostly in debug mode in Visual Studio 2022, so that's your best bet for running the game.

There are some issues with the working directory not being included properly in the project. If you receive error in missing files, try setting it to the solution directory. 
 
## Current external libraries used

### Glad 

For loading up the modern OpenGL versions in Windows and Linux

### GLFW 

For getting the platform layer running. This may get phased out once we have some more functionality in the game and we want to experiment with the platform layer. 

### DearIMGUI 

For creating a nice debug UI for experimenting with various runtime changes and displaying debug information.

### GLM 

Widely used OpenGL conforming math library.

### STB

Widely used header-only C-library for various utility tasks. Currently mostly loads up images for me. 
