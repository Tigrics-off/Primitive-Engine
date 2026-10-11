#version 460 core

layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_texcoord;

layout(location = 0) smooth out vec2 v_texcoord;
out vec3 frag_pos;

uniform mat4 u_model, u_view, u_proj;


void main()
{
    vec4 result_pos = u_proj * u_view * u_model * vec4(a_pos, 1.0);
    float grid = 0.01;

    result_pos.xyz = floor(result_pos.xyz / grid) * grid;

    frag_pos = vec3(u_model * vec4(a_pos, 1.0));
    v_texcoord = a_texcoord;
    gl_Position = result_pos;
}