#pragma once
#define REFRESHRATE 16
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "Pyramid.h"
#include "MeshLoader.h"

class HelloGL
{
public:

	//constructor definition
	HelloGL(int argc, char* argv[]);

	//destructor
	~HelloGL(void);

	void Display();

	void Update();

	void Keyboard(unsigned char key, int x, int y);

	void InitObject();

	void InitLight();

	void InitGL(int argc, char* argv[]);

private:
	float rotation;

	Camera* camera;
	SceneObject* objects[500];
	Vector4* _lightPosition;
	Lighting* _lightData;
};

