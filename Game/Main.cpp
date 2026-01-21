#include "Engine/AppConfig.hpp"
#include "Engine/Application.hpp"
#include "MenuScene.hpp"
#include <memory>
#include <exception>
#include <Windows.h>

int main()
{
    try
    {
        eng::AppConfig cfg;
        cfg.title = "Shoot'em up";
        cfg.windowSize = { 1280, 720 };
        cfg.fpsLimit = 120;

        eng::Application app(cfg);
        app.Scenes().Set(std::make_unique<MenuScene>(), app);
        app.Run();
        return 0;
    }
    catch (const std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Runtime error", MB_OK | MB_ICONERROR);
        return 1;
    }
}
