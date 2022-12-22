#version 460

in vec2 uvCoord;

uniform sampler2D texture1;

out vec4 FragColor;

void main()
{
    vec4 texResult = texture(texture1, uvCoord);    
    
    if(texResult.a < 0.05)
    {
        discard;
    }
    
    else
    {
        FragColor = texResult;
    }
}