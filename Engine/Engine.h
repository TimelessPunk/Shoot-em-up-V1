#pragma once
#include "Scene.h"

class Engine 
{
public:
	static Engine* GetInstance() 
	{
		if (instance == nullptr) 
		{
			instance = new Engine();
		}
		return instance;
	}

	void Start() 
	{
		scene = new Scene();

		scene->Start();
	}

	void Run()
	{
		while (true)
		{
			scene->Update();
			scene->Render();
		}
		scene->Destroy();
	}

private:
	static Engine* instance;

	Engine()
	{

	}
};
