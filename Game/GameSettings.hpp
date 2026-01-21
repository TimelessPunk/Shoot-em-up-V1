#pragma once
#include <SFML/Graphics.hpp>

struct GameSettings
{
    int volume = 80;                 // 0 - 100%
    int brightness = 100;            // 50 - 150%
    sf::Vector2u resolution = { 1920, 1080 };

    static GameSettings& Get()
    {
        static GameSettings instance;
        return instance;
    }
};
