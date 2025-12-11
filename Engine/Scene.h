#pragma once
#include "GameObject.h"
#include <vector>

class Scene
{
public:
	void Start() 
	{
		for (GameObject* gameObject : gameObjects)
		{
			gameObject->Start();
		}
	}
	void Update();
	void Render();
	void Destroy();

private:
	std::vector<GameObject> gameObjects;
};

