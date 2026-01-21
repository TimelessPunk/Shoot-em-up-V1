#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "AppConfig.hpp"
#include "Input.hpp"
#include "SceneManager.hpp"
#include "Resources.hpp"

namespace eng
{
    class Application
    {
    public:
        explicit Application(const AppConfig& cfg);

        void Run();
        void Quit();

        sf::RenderWindow& Window() { return m_window; }
        Input& GetInput() { return m_input; }
        SceneManager& Scenes() { return m_scenes; }
        ResourceManager& Resources() { return m_resources; }

    private:
        void ProcessEvents();

    private:
        AppConfig m_cfg;

        sf::RenderWindow m_window;
        sf::Clock m_clock;
        bool m_running{ true };

        Input m_input;
        SceneManager m_scenes;
        ResourceManager m_resources;
    };
}
