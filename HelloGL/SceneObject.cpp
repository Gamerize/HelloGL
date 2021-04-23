#include "SceneObject.h"

SceneObject::SceneObject(Obj* obj, Texture2D* Texture)
{
	_obj = obj;
	_texture = Texture;
}

SceneObject::~SceneObject()
{
	delete _obj;
	_obj = nullptr;
	delete _texture;
	_texture = nullptr;
}

void SceneObject::Update()
{
}

void SceneObject::Draw()
{
}
