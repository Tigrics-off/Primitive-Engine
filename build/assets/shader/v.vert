#version 330
layout(location = 0) in vec3 Pos;
layout(location = 1) in vec2 UV;

out vec2 aUV;

uniform mat4 model, view, proj;
uniform bool psx;

void main()
{
    vec4 pos = model * vec4(Pos, 1.0);
    
    if (psx)
    {
        float grid = 0.01;
        pos = floor(pos / grid) * grid;
    }
    
    pos = proj * view * pos;
    gl_Position = pos;
    aUV = UV;
}