#version 330 core
in vec2 aUV;
out vec4 FragColor;

uniform sampler2D out_texture;

void main()
{
    FragColor = texture(out_texture, aUV);
}