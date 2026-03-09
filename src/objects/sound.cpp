#include "utils/config.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "sound.hpp"
#include "utils/debug.hpp"
#include <string>
#include <filesystem>

ma_engine sound_source::engine;

sound_source::sound_source(std::string path, float volume)
{
    static bool is_init = false;
    if (!is_init)
    {
        ma_result r = ma_engine_init(nullptr, &engine);
        if (r != MA_SUCCESS)
            debug::error("Failed init sound engine");
        is_init = true;
    }
    sound_path = path;

    ma_result r = ma_sound_init_from_file
    (
        &engine,
        sound_path.c_str(),
        0,
        nullptr,
        nullptr,
        &sound
    );
    if (r != MA_SUCCESS)
    {
        custom::config conf = custom::parse_config();
        if (std::filesystem::exists(conf.sound))
        {
            debug::warn("Failed play sound " + sound_path + ". He will replaced to debug sound");
            r = ma_sound_init_from_file
            (
                &engine,
                conf.sound.c_str(),
                0,
                nullptr,
                nullptr,
                &sound
            );
        }
        else
            debug::error("Debug sound not be found");
    }

    ma_sound_set_volume(&sound, volume);
    ma_sound_set_looping(&sound, loop);
}
sound_source::~sound_source()
{
    ma_sound_uninit(&sound);
}
void sound_source::play()
{
    ma_sound_start(&sound);
}
void sound_source::stop()
{
    ma_sound_stop(&sound);
}
void sound_source::set_volume(float value)
{
    volume = value;
    ma_sound_set_volume(&sound, volume);
}
void sound_source::set_loop(bool value)
{
    loop = value;
    ma_sound_set_looping(&sound, loop);
}
