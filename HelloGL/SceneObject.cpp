#include "SceneObject.h"

SceneObject::SceneObject(Mesh* mesh, Texture2D* Texture)
{
	_mesh = mesh;
	_texture = Texture;
}

SceneObject::~SceneObject()
{
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}
