#pragma once
#include "Entity.hpp"
#include <vector>
#include <memory>
#include <algorithm>

namespace eng
{
    class World
    {
    public:
        template<typename T, typename... Args>
        T& Spawn(Args&&... args)
        {
            auto e = std::make_unique<T>(std::forward<Args>(args)...);
            T& ref = *e;
            m_entities.push_back(std::move(e));
            return ref;
        }

        void Update(float dt)
        {
            for (auto& e : m_entities)
                if (e->IsAlive())
                    e->Update(dt);

            m_entities.erase(
                std::remove_if(m_entities.begin(), m_entities.end(),
                    [](auto& e) { return !e->IsAlive(); }),
                m_entities.end());
        }

        void Render(sf::RenderTarget& target)
        {
            for (auto& e : m_entities)
                if (e->IsAlive())
                    e->Render(target);
        }

        std::vector<Entity*> Alive()
        {
            std::vector<Entity*> out;
            for (auto& e : m_entities)
                if (e->IsAlive())
                    out.push_back(e.get());
            return out;
        }

    private:
        std::vector<std::unique_ptr<Entity>> m_entities;
    };
}
