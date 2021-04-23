#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "Structures.h"
#include "SceneObject.h"
#include "Texture2D.h"

class Cube : public SceneObject
{
private:
	static Vertex* indexedVertices;
	static Color* indexedColors;
	static GLushort* indices;

	static int numVertices, numColors, numIndices;

	GLfloat _rotation;
	GLfloat _rotateSpeed;
	Vector3 _position;
	Vector3 _rotate;

	Material* _material;

public:
	Cube(Obj* obj, Texture2D* Texture, float x, float y, float z);
	~Cube();

	void Draw();
	void Update();
	void SetRotation(float rotation);
	void InitMaterial();

	//static bool Load(char* path);
};
