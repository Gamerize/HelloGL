#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* Texture)
{
	_mesh = mesh;
	_texture = Texture;
}

SceneObject::~SceneObject()
{
	delete _mesh;
	_mesh = nullptr;
	delete _texture;
	_texture = nullptr;
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}
