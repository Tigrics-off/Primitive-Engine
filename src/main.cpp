#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "engine/window.hpp"
#include "graphics/shader.hpp"
#include "engine/loop.hpp"
#include "utils/config.hpp"
#include "utils/debug.hpp"
#include "utils/file.hpp"
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
    glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0, 1, 0)));

    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
    {
        cam.translate(forward.x * speed, 0, forward.z * speed);
    }
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
    {
        cam.translate(-forward.x * speed, 0, -forward.z * speed);
    }
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
    {
        cam.translate(-right.x * -speed, 0, -right.z * speed);
    }
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
    {
        cam.translate(right.x * speed, 0, right.z * speed);
    }

    if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS)
    {
        cam.rotate(rot_speed, 0, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        cam.rotate(-rot_speed, 0, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        cam.rotate(0, -rot_speed, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        cam.rotate(0, rot_speed, 0);
    }
}
int main(int argc, char *argv[])
{
    custom::parse_config(conf);
    custom::load_arg(argc, argv, conf);
    
    win = window::init(conf);
    shader::load(shader_prog);
    
    camera cam(conf.width, conf.height);
    cube c("assets/textures/kirpich.jpg");
    cube sky("assets/textures/sky.jpg");
    light ambient(60.0/255.0, 40.0/255.0, 125.0/255.0, 0.5);
    point_light p;
    
    cam.translate(0, 0, -0.2);
    sky.scale(100, 100, 100);
    p.translate(0, 3, 0);
    loop::run(win, shader_prog, conf, [&](){
        input(cam);
        
        cam.hand_matrix(shader_prog);
        
        c.rotate(0.05, 0.05, 0.05);
        c.draw(shader_prog);

        sky.draw(shader_prog);
        ambient.enable(shader_prog);
        p.enable(shader_prog);
    });
    
    return 0;
}
