#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render/win/window.hpp"
#include "render/shaders/shader.hpp"
#include "render/loop/loop.hpp"
#include "config/config.hpp"
#include "debug/debug.hpp"
#include "file/file.hpp"
#include "objects/shapes.hpp"

GLFWwindow *win;
custom::config conf;

unsigned int shader_prog;

void input(camera &cam)
{
    float speed = 0.01f;
    float rot_speed = 0.002f;
    
    glm::vec3 forward = cam.get_direction();
    forward.y = 0;
    forward = glm::normalize(forward);

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
        cam.translate(0, 0, forward.z * -speed);
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        cam.translate(0, 0, forward.z * speed);
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        cam.translate(forward.x * -speed, 0, 0);
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        cam.translate(forward.x * speed, 0, 0);
    
    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
        cam.rotate(rot_speed, 0, 0);
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
        cam.rotate(-rot_speed, 0, 0);
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
        cam.rotate(0, -rot_speed, 0);
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam.rotate(0, rot_speed, 0);
}
int main(int argc, char *argv[])
{
    custom::parse_config(conf);
    custom::load_arg(argc, argv, conf);
    
    win = window::init(conf);
    shader::load(shader_prog);
    
    camera cam(conf.width, conf.height);
    cube c("assets/textures/kirpich.jpg");
    
    cam.translate(0, 0, -0.2);
    loop::run(win, shader_prog, conf, [&](){
        input(cam);
        
        cam.hand_matrix(shader_prog);
        
        c.rotate(0.01, 0.01, 0.01);
        c.draw(shader_prog);
    });
    
    return 0;
}
