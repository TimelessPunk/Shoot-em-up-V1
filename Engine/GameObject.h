#pragma once
#include <string>

class Transform 
{
	float x = 0.f;
	float y = 0.f;

	float rotation = 0.f;

	float scale_x = 1.f;
	float scale_y = 1.f;
};

class GameObject
{
public:
	std::strong_ordering name;
	Transform transform;

	void Start();
	void Update();
	void Render();
	void Destroy();

private:

	std::vector<Component>
};

