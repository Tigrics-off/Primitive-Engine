#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "engine/window.hpp"
#include "graphics/shader.hpp"
#include "engine/loop.hpp"
#include "utils/config.hpp"
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
    if (glfwGetKey(win, GLFW_KEY_Q) == GLFW_PRESS)
    {
        cam.translate(0, -speed, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_E) == GLFW_PRESS)
    {
        cam.translate(0, speed, 0);
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
    conf = custom::parse_config();
    custom::load_arg(argc, argv, conf);
    
    win = window::init(conf);
    shader::load(shader_prog);

    scene scene("assets/scenes/dance.json");

    loop::run(win, shader_prog, conf, [&]()
    {
        input(*scene["cam"].as<camera>());
        
        scene.render(shader_prog);
    });
    
    return 0;
}
