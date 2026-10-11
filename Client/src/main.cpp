#include "GLFW/glfw3.h"
#include "core/window.hpp"
#include "engine/loop.hpp"
#include "objects/camera.hpp"
#include "graphics/shader.hpp"
#include "objects/custom.hpp"
#include "objects/light/light.hpp"
#include "objects/light/point.hpp"
#include "objects/light/spot.hpp"
#include <format>
#include <string>

void trans_cam(window& win, camera& cam, float delta)
{
    float speed = 5, sense = 65;

    if (glfw_get_key(win.win(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam.rotate(0, -sense * delta, 0);
    if (glfw_get_key(win.win(), GLFW_KEY_LEFT) == GLFW_PRESS)
        cam.rotate(0, sense * delta, 0);
    if (glfw_get_key(win.win(), GLFW_KEY_UP) == GLFW_PRESS)
        cam.rotate(sense * delta, 0, 0);
    if (glfw_get_key(win.win(), GLFW_KEY_DOWN) == GLFW_PRESS)
        cam.rotate(-sense * delta, 0, 0);

    float sin = sinf(glm::radians(cam.rot().y));
    float cos = cosf(glm::radians(cam.rot().y));

    if (glfw_get_key(win.win(), GLFW_KEY_W) == GLFW_PRESS)
        cam.translate(-sin * speed * delta, 0, -cos * speed * delta);
    if (glfw_get_key(win.win(), GLFW_KEY_S) == GLFW_PRESS)
        cam.translate(sin * speed * delta, 0, cos * speed * delta);
    if (glfw_get_key(win.win(), GLFW_KEY_A) == GLFW_PRESS)
        cam.translate(-cos * speed * delta, 0, sin * speed * delta);
    if (glfw_get_key(win.win(), GLFW_KEY_D) == GLFW_PRESS)
        cam.translate(cos * speed * delta, 0, -sin * speed * delta);
    if (glfw_get_key(win.win(), GLFW_KEY_E) == GLFW_PRESS)
        cam.translate(0, speed * delta, 0);
    if (glfw_get_key(win.win(), GLFW_KEY_Q) == GLFW_PRESS)
        cam.translate(0, -speed * delta, 0);
}

int main()
{
    window win;
    game_loop loop(win, 64, 187, 194);
    shaders shaders("assets/shaders/v.vert", "assets/shaders/f.frag");
    
    custom_mesh room("assets/models/a.obj", "assets/textures/cat.jpg"), a;
    light light(17, 41, 194);
    point_light point(250, 250, 250, 0.1, 10, 5);
    spot_light spot(250, 250, 250, 0.1, 10, 65, 5);
    
    point.translate(10, 10, 10);
    
    camera cam;

    std::string prime_title = win.title();
    float timer = 0;
    
    loop.run(
    [&]()
    {
        trans_cam(win, cam, loop.delta_time());
        timer += loop.delta_time();
        if (timer >= 1)
        {
            win.set_title(std::format("{}, (FPS: {:.1f})", prime_title, 1.f/loop.delta_time()));
            timer = 0;
        }

        spot.set_pos(cam.pos() - glm::vec3(1, 0, 0));
        spot.set_rot(cam.rot().x, -cam.rot().y - 90, -cam.rot().z);

        shaders.use();
        cam.render(shaders);
        room.render(shaders);
        a.render(shaders);
        light.render(shaders);
        point.render(shaders);
        spot.render(shaders);
    });
}