#pragma once
#include <memory>

namespace eng
{
    class Scene;
    class Application;

    class SceneManager
    {
    public:
        void Set(std::unique_ptr<Scene> next, Application& app);
        Scene* Current() { return m_current.get(); }

    private:
        std::unique_ptr<Scene> m_current;
    };
}
