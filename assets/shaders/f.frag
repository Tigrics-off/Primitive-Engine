#version 460 core

layout(location = 0) smooth in vec2 v_texcoord;
in vec3 frag_pos;

out vec4 frag_color;

uniform sampler2D u_texture;

uniform vec3 am_color;

uniform vec3 pt_color;
uniform vec3 pt_pos;
uniform float pt_min_dis;
uniform float pt_max_dis;
uniform float pt_power;

uniform vec3 sp_color;
uniform vec3 sp_pos;
uniform vec3 sp_rot;
uniform vec3 sp_dir;
uniform float sp_min_dis;
uniform float sp_max_dis;
uniform float sp_angle;
uniform float sp_power;

vec3 calc_pt()
{
    const float steps = 6;
    vec3 light_dir = normalize(pt_pos - frag_pos);

    float radius = abs(pt_max_dis - pt_min_dis);

    float dist = length(pt_pos - frag_pos);
    float att = clamp(1.0 - (dist - pt_min_dis) / radius, 0.0, 1.0);
    
    att = floor(att * steps) / steps;

    return pt_color * att * pt_power;
}
vec3 calc_sp()
{
    const float steps = 6;
    vec3 light_dir = normalize(sp_pos - frag_pos);

    float radius = abs(sp_max_dis - sp_min_dis);
    float cut = cos(radians(sp_angle * 0.5));
    float outer_cut = cos(radians(sp_angle * 0.5 + 10.0));
    
    float theta = dot(light_dir, normalize(-sp_dir));
    float epsilon = cut - outer_cut;
    float intensity = clamp((theta - outer_cut) / epsilon, 0.0, 1.0);
    
    float dist = length(sp_pos - frag_pos);
    float att = clamp(1.0 - (dist - sp_min_dis) / radius, 0.0, 1.0);

    att = floor(att * steps) / steps;
    return sp_color * att * sp_power * intensity;
}

void main()
{
    const float steps = 4, grid = 0.015;
    vec4 result_color = texture(u_texture, floor(v_texcoord.xy / grid) * grid);

    result_color.rgb = (floor(result_color.rgb * steps) / steps);

    vec3 lighting = am_color + calc_pt() + calc_sp();
    result_color.rgb *= lighting;

    frag_color = result_color;
}