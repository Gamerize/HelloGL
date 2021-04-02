#pragma once
#include "SceneObject.h"

class Pyramid : public SceneObject
{
private:
	Vector3 _position;

public:
	Pyramid(Mesh* mesh, float x, float y, float z);
	~Pyramid();

	void Draw();
	void Update();
};

