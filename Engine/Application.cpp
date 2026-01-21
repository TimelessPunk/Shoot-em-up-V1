#include "Application.hpp"
#include "Scene.hpp"
#include <SFML/Window/Event.hpp>

namespace eng
{
    Application::Application(const AppConfig& cfg)
        : m_cfg(cfg),
        m_window(sf::VideoMode({ cfg.windowSize.x, cfg.windowSize.y }), cfg.title)
    {
        m_window.setFramerateLimit(cfg.fpsLimit);
        m_window.setVerticalSyncEnabled(cfg.vsync);
    }

    void Application::Quit()
    {
        m_running = false;
        m_window.close();
    }

    void Application::Run()
    {
        while (m_running && m_window.isOpen())
        {
            m_input.BeginFrame();
            ProcessEvents();

            const float dt = m_clock.restart().asSeconds();

            if (auto* s = m_scenes.Current())
                s->Update(*this, dt);

            m_window.clear();

            if (auto* s = m_scenes.Current())
                s->Render(*this, m_window);

            m_window.display();
        }
    }

    void Application::ProcessEvents()
    {
        while (auto ev = m_window.pollEvent())
        {
            if (ev->is<sf::Event::Closed>())
            {
                Quit();
                return;
            }

            if (auto* kp = ev->getIf<sf::Event::KeyPressed>())
                m_input.OnKeyPressed(kp->code);

            if (auto* kr = ev->getIf<sf::Event::KeyReleased>())
                m_input.OnKeyReleased(kr->code);

            if (auto* s = m_scenes.Current())
                s->HandleEvent(*this, *ev);
        }
    }
}
