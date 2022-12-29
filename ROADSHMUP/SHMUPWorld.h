#pragma once

class OpenGLRenderer;

/* 

    Interface for the game world alternatives

*/

class SHMUPWorld
{
public: 
    // Default test world
    SHMUPWorld() = 0;    
    virtual ~SHMUPWorld() = 0;

    virtual void Update(float dt) = 0;

    // Feeds the current renderable list to the renderer 
    virtual void SendRenderables(OpenGLRenderer* renderer) = 0;
    virtual void LoadRenderable(OpenGLRenderer* renderer) = 0;
};