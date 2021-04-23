#pragma once
#include <Windows.h> //Required for OpenGL on Windows
#include <gl/GL.h> //OpenGL
#include <gl/GLU.h> //OpenGL Ultilities
#include "GL\freeglut.h" //freeglut library
#include <vector>

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Camera
{
	Vector3 eye;
	Vector3 center;
	Vector3 up;
};

struct Color
{
	GLfloat r, g, b;
};

struct Vertex
{
	GLfloat x, y, z;
};

struct TexCoord
{
	GLfloat u;
	GLfloat v;
};

struct Mesh
{
	Vertex* Vertices;
	//Color* Colors;
	Vector3* Normals;
	GLushort* Indices;
	int VertexCount, NormalCount, IndexCount, TexCoordCount;
	TexCoord* TexCoords;
};

struct Obj
{
	std::vector<Vertex> vertices;
	std::vector<Vector3> Normals;
	std::vector<TexCoord> TexCoord;
	std::vector<GLushort> VerIndices, NorIndices, TexIndices;
	int faceCount, verCount, norCount, texCount;
};

struct Vector4
{
	float x, y, z, w;
};

struct Lighting
{
	Vector4 Ambient, Diffuse, Specular;
};

struct Material
{
	Vector4 Ambient, Diffuse, Specular;
	GLfloat Shininess;
};

