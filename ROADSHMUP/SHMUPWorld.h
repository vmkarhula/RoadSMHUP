#pragma once

class OpenGLRenderer2D;

/* 

    Interface for the game world alternatives

*/

class SHMUPWorld
{
public: 
    // Default test world
    SHMUPWorld() = default;    
    virtual ~SHMUPWorld() = 0;

    virtual void Update(float dt) = 0;

    // Feeds the current renderable list to the renderer 
    virtual void SendRenderables(OpenGLRenderer2D* renderer) = 0;
    virtual void PrepareRenderer(OpenGLRenderer2D* renderer) = 0;
};