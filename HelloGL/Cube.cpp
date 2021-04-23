#include "Cube.h"
#include <fstream>
#include <iostream>

Vertex* Cube::indexedVertices = nullptr;
Color* Cube::indexedColors = nullptr;
GLushort* Cube::indices = nullptr;

int Cube::numVertices = 0;
int Cube::numColors = 0;
int Cube::numIndices = 0;

Cube::Cube(Obj* obj, Texture2D* Texture, float x, float y, float z) : SceneObject(obj, Texture)
{
	_rotation = 0.0f;
	_position.x = x;
	_position.y = y;
	_position.z = z;
	_rotateSpeed = (rand() % 15) + 1;
}

Cube::~Cube()
{
	delete _material;
	_material = nullptr;
}

void Cube::Draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture->GetID());
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, &_obj->vertices);
	glNormalPointer(GL_FLOAT, 0, &_obj->Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, &_obj->TexCoord);

	/*InitMaterial();
	glMaterialfv(GL_FRONT, GL_AMBIENT, &(_material->Ambient.x));
	glMaterialf(GL_FRONT, GL_SHININESS, _material->Shininess);*/

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation, 0.0f, 0.1f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _obj->faceCount; i++)
	{
		glTexCoord2f(_obj->TexCoord[_obj->TexIndices[i]].u, _obj->TexCoord[_obj->TexIndices[i]].v);
		glNormal3f(_obj->Normals[_obj->NorIndices[i]].x, _obj->Normals[_obj->NorIndices[i]].y, _obj->Normals[_obj->NorIndices[i]].z);
		glVertex3f(_obj->vertices[_obj->VerIndices[i]].x, _obj->vertices[_obj->VerIndices[i]].y, _obj->vertices[_obj->VerIndices[i]].z);
	}
	glEnd();
	glPopMatrix();

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void Cube::Update()
{
	_rotation += _rotateSpeed;

	if (_rotation >= 360.0f)
		_rotation = 0.0f;
}

void Cube::SetRotation(float rotation)
{
}

void Cube::InitMaterial()
{
	_material = new Material();
	_material->Ambient.x = 0.8;
	_material->Ambient.y = 0.05;
	_material->Ambient.z = 0.05;
	_material->Ambient.w = 1.0;
	_material->Diffuse.x = 0.8;
	_material->Diffuse.y = 0.05;
	_material->Diffuse.z = 0.05;
	_material->Diffuse.w = 1.0;
	_material->Specular.x = 1.0;
	_material->Specular.y = 1.0;
	_material->Specular.z = 1.0;
	_material->Specular.w = 1.0;
	_material->Shininess = 100.0f;
}

/*bool Cube::Load(char* path)
{
	std::ifstream inFile;
	inFile.open(path);
	if (!inFile.good())
	{
		std::cerr << "Can't open text file. " << path << std::endl;
		return false;
	}
	inFile >> numVertices;
	indexedVertices = new Vertex[numVertices];
	for (int i = 0; i < numVertices; i++)
	{
		inFile >> indexedVertices[i].x;
		inFile >> indexedVertices[i].y;
		inFile >> indexedVertices[i].z;
	}
	inFile >> numColors;
	indexedColors = new Color[numColors];
	for (int i = 0; i < numColors; i++)
	{
		inFile >> indexedColors[i].r;
		inFile >> indexedColors[i].b;
		inFile >> indexedColors[i].g;
	}
	inFile >> numIndices;
	indices = new GLushort[numIndices];
	for (int i = 0; i < numIndices; i++)
	{
		inFile >> indices[i];
	}

	inFile.close();

	return true;
}*/
