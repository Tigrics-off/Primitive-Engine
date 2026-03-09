#pragma once
#include <miniaudio.h>
#include "core/object.hpp"
#include <string>


class sound_source : public object
{
private:
    static ma_engine engine;
    ma_sound sound;
    std::string sound_path;
    float volume;
    bool loop = false;
    
    bool distance = false;
    float mix_dis, max_dis;
public:
    sound_source(std::string path, float volume = 1.0);
    ~sound_source();
    void play();
    void stop();

    bool get_is_distance();
    float get_min_distance();
    float get_max_distance();
    bool get_loop();
    float get_volume();
    
    void set_is_distance(bool value);
    void set_min_distance(float value);
    void set_max_distance(float value);
    void set_volume(float value);
    void set_loop(bool value);

};