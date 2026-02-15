#version 330 core
in vec2 aUV;
in vec3 frag_pos;
out vec4 FragColor;

uniform bool psx;

uniform vec3 ambient_light;

uniform vec3 point_light_pos;
uniform float point_light_strength;
uniform vec3 point_light_color;

uniform sampler2D out_texture;

vec3 calc_point_light()
{
    float distance = length(point_light_pos - frag_pos);
    float attenuation = 1.0 / (1.0 + point_light_strength * distance * distance);
    attenuation *= 10.0;
    
    if (psx)
    {
        float levels = 4.0;
        attenuation = floor(attenuation * levels) / levels;
    }
    attenuation = max(attenuation, 0.0);
    return point_light_color * attenuation;
}

void main()
{
    vec4 tex_color = texture(out_texture, aUV);
    
    tex_color.rgb *= ambient_light + calc_point_light();
    FragColor = tex_color;
}