#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Application.hpp"

namespace eng
{
    void SceneManager::Set(std::unique_ptr<Scene> next, Application& app)
    {
        if (m_current)
            m_current->OnExit(app);

        m_current = std::move(next);

        if (m_current)
            m_current->OnEnter(app);
    }
}
