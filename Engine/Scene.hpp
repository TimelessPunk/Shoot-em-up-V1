#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

namespace eng
{
    class Application; // forward

    class Scene
    {
    public:
        virtual ~Scene() = default;

        virtual void OnEnter(Application&) {}
        virtual void OnExit(Application&) {}

        virtual void HandleEvent(Application&, const sf::Event&) {}
        virtual void Update(Application&, float dt) = 0;
        virtual void Render(Application&, sf::RenderTarget& target) = 0;
    };
}
