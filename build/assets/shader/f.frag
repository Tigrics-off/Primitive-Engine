#version 330 core
in vec2 aUV;
in vec3 frag_pos;
out vec4 frag_color;
uniform sampler2D out_texture;

uniform bool psx;

uniform vec3 ambient_light;

uniform vec3 point_light_pos;
uniform float point_light_strength;
uniform vec3 point_light_color;

uniform vec3 spot_light_pos;
uniform float spot_light_strength;
uniform vec3 spot_light_color;
uniform vec3 spot_light_dir;
uniform float cut_off;
uniform float out_cut_off;

vec3 calc_point_light()
{
    float distance = length(point_light_pos - frag_pos);
    float attenuation = 1.0 / (1.0 + point_light_strength * distance * distance);
    attenuation *= 10.0;
    
    attenuation = max(attenuation, 0.0);
    return point_light_color * attenuation;
}

vec3 calc_spot_light()
{
    vec3 light_to_frag = normalize(spot_light_pos - frag_pos);
    vec3 dir = normalize(spot_light_dir);

    float cos_angle = dot(dir, light_to_frag);

    if (cos_angle < out_cut_off) return vec3(0);
    
    float power = 1;

    if (cos_angle < cut_off)
    {
        power = (cos_angle - out_cut_off) / (cut_off - out_cut_off);
    }
    
    float distance = length(spot_light_pos - frag_pos);
    float attenuation = 1.0 / (1.0 + spot_light_strength * distance * distance);
    attenuation *= 10;

    return spot_light_color * power * attenuation;
}

void main()
{
    vec4 tex_color = texture(out_texture, aUV);
    
    tex_color.rgb *= ambient_light + calc_point_light() + calc_spot_light();
    frag_color = tex_color;
}