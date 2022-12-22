#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord; 

out vec2 uvCoord;

uniform mat4 world;
uniform mat4 proj;
uniform mat4 view;  

void main()
{
    
    
    // gl_Position = proj * view * world * vec4(aPos, 1.0);
    gl_Position =  proj * view * world * vec4(aPos, 1.0);
    uvCoord = aTexCoord;

}