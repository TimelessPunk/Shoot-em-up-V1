#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace eng
{
    struct AppConfig
    {
        sf::Vector2u windowSize{ 1280, 720 };
        std::string title{ "Shoot'em up" };
        unsigned int fpsLimit{ 120 };
        bool vsync{ false };
    };
}
