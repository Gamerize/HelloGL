#pragma once
#include "Structures.h"
#include "Texture2D.h"

class SceneObject
{
protected:
	Obj* _obj;
	Texture2D* _texture;
public:
	SceneObject(Obj* obj, Texture2D* texture);
	virtual  ~SceneObject();

	virtual void Update();
	virtual void Draw();
};

