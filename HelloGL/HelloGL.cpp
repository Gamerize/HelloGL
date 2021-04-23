#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include "time.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	srand(time(NULL));
	InitGL(argc, argv);
	InitLighting();
	InitObject();
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);

	glDepthFunc(GL_LESS);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set the viewport to be the entire window
	glViewport(0, 0, 800, 800);
	//Set the correct perspective
	gluPerspective(45, 1, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	rotation = 0.0f;

	glEnable(GL_TEXTURE_2D);// without this you will just gat white boxes
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
}

void HelloGL::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = -1.0;
	_lightPosition->y = 5.0;
	_lightPosition->z = -2.0;
	_lightPosition->w = 10.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 2.0;
	_lightData->Specular.x = 0.6;
	_lightData->Specular.y = 0.6;
	_lightData->Specular.z = 0.6;
	_lightData->Specular.w = 1.0;
}

void HelloGL::InitObject()
{
	/*Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* PyramidMesh = MeshLoader::Load((char*)"pyramid.txt");*/
	Obj* CrystalObj = ObjectLoader::Load((char*)"Objects/Crystal.obj");
	Obj* PlatformObj = ObjectLoader::Load((char*)"Objects/Platform.obj");
	Obj* TipObj = ObjectLoader::Load((char*)"Objects/Tip.obj");
	Obj* MainPillarObj = ObjectLoader::Load((char*)"Objects/MainPillar.obj");
	Obj* RingObj = ObjectLoader::Load((char*)"Objects/Ring.obj");
	Obj* PillarObj = ObjectLoader::Load((char*)"Objects/pillar.obj");

	Texture2D* crystalTexture = new Texture2D();
	crystalTexture->Load((char*)"Textures/greco_scritto_marble_basecolor.raw", 4096, 4096);
	Texture2D* PlatformTexture = new Texture2D();
	PlatformTexture->Load((char*)"Textures/brick_floor_003_diffuse_4k.raw", 4096, 4096);
	Texture2D* MainPillarTexture = new Texture2D();
	MainPillarTexture->Load((char*)"Textures/rough_plaster_broken_diff_4k.raw", 4096, 4096);
	Texture2D* RingTexture = new Texture2D();
	RingTexture->Load((char*)"Textures/factory_wall_diff_4k.raw", 4096, 4096);
	Texture2D* PillarTexture = new Texture2D();
	PillarTexture->Load((char*)"Textures/cobblestone_floor_04_diff_4k.raw", 4096, 4096);

	camera = new Camera();
	camera->eye.x = 0.0f;
	camera->eye.y = 0.0f;
	camera->eye.z = 1.0f;
	camera->center.x = 0.0f;
	camera->center.y = 0.0f;
	camera->center.z = 0.0f;
	camera->up.x = 0.0f;
	camera->up.y = 1.0f;
	camera->up.z = 0.0f;

	/*for (int i = 0; i < 5; i++)
	{

	}*/
	Crystal[0] = new Cube(CrystalObj, crystalTexture, 0, 1, -10);
	Crystal[1] = new Cube(CrystalObj, crystalTexture, 6, -2, -15);
	Crystal[2] = new Cube(CrystalObj, crystalTexture, 6, -2, -5);
	Crystal[3] = new Cube(CrystalObj, crystalTexture, -5, -2, -15);
	Crystal[4] = new Cube(CrystalObj, crystalTexture, -5, -2, -5);
	Platform = new Cube(PlatformObj, PlatformTexture, 0, -6, -10);
	Tip = new Cube(TipObj, MainPillarTexture, 0, -7, -10);
	MainPillar = new Cube(MainPillarObj, MainPillarTexture, 0, -7, -10);
	Pillar[0] = new Cube(PillarObj, PillarTexture, 0, -6, -10);
	Pillar[1] = new Cube(PillarObj, PillarTexture, 11, -6, -10);
	Pillar[2] = new Cube(PillarObj, PillarTexture, 11, -6, -20);
	Pillar[3] = new Cube(PillarObj, PillarTexture, 0, -6, -20);
	Ring = new Cube(RingObj, RingTexture, 0, -7, -10);

	/*for (int i = 0; i < 1; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) /
			10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}*/
	/*for (int i = 500; i < 1000; i++)
	{
		objects[i] = new Pyramid(PyramidMesh, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) /
			10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}*/
}

HelloGL::~HelloGL(void)
{
	delete camera;
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //this clears the scene

	for (int i = 0; i < 5; i++)
	{
		Crystal[i]->Draw();
	}
	Platform->Draw();
	Tip->Draw();
	MainPillar->Draw();
	for (int i = 0; i < 4; i++)
	{
		Pillar[i]->Draw();
	}
	Ring->Draw();

	/*for (int i = 0; i < 100; i++)
	{
		objects[i]->Draw();
	}*/

	glFlush(); //flushes the scene drawn to the graphics card

	glutSwapBuffers();
}

void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);

	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));

	Ring->Update();

	for (int i = 0; i < 5; i++)
	{
		Crystal[i]->Update();
	}

	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
		if (key == 'w')
		{
			camera->eye.z -= 0.1f;
			camera->center.z -= 0.1f;
		}
		if (key == 's')
		{
			camera->eye.z += 0.1f;
			camera->center.z += 0.1f;
		}
		if (key == 'd')
		{
			camera->eye.x += 0.1f;
			camera->center.x += 0.1f;
		}
		if (key == 'a')
		{
			camera->eye.x -= 0.1f;
			camera->center.x -= 0.1f;
		}
		if (key == 'W')
		{
			camera->eye.y += 0.1f;
		}
		if (key == 'S')
		{
			camera->eye.y -= 0.1f;
		}
		if (key == 'A')
		{
			camera->eye.x += 0.1f;
		}
		if (key == 'D')
		{
			camera->eye.x -= 0.1f;
		}

}


/*void HelloGL::DrawCube()
{
	glBegin(GL_TRIANGLES);
	// face v0-v1-v2
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	// face v2-v3-v0
	glColor3f(1, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(1, -1, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face v0-v3-v4
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	// face v4-v5-v0
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face v0-v5-v6
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v1-v0
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(1, 1, 1);
	glVertex3f(1, 1, 1);
	// face  v1-v6-v7
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	// face v7-v2-v1
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(1, 1, 0);
	glVertex3f(-1, 1, 1);
	// face v7-v4-v3
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	// face v3-v2-v7
	glColor3f(1, 0, 1);
	glVertex3f(1, -1, 1);
	glColor3f(1, 0, 0);
	glVertex3f(-1, -1, 1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);

	// face v4-v7-v6
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);
	glColor3f(0, 0, 0);
	glVertex3f(-1, -1, -1);
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	// face v6-v5-v4
	glColor3f(0, 1, 0);
	glVertex3f(-1, 1, -1);
	glColor3f(0, 1, 1);
	glVertex3f(1, 1, -1);
	glColor3f(0, 0, 1);
	glVertex3f(1, -1, -1);

	glEnd();
}

void HelloGL::DrawCubeArray()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glColor3fv(&colors[i].r);
		glVertex3fv(&vertices[i].x);
	}

	glEnd();

	glPopMatrix();
}

void HelloGL::DrawIndexedCube()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 36; i++)
	{
		glVertex3f(indexedVertices[indices[i]].x, indexedVertices[indices[i]].y, indexedVertices[indices[i]].z);
	}
	glEnd();

	glPopMatrix();
}

void HelloGL::DrawCubeArrayAlt()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glPushMatrix();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void HelloGL::DrawIndexedCubeAlt()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, indexedVertices);
	glColorPointer(3, GL_FLOAT, 0, indexedColors);

	glPushMatrix();
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
	glPopMatrix();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}*/


/*void HelloGL::DrawTriangle()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -0.5f);
	glRotatef(rotation, 1.0f, 0.0f, 0.0f);

	glBegin(GL_POLYGON); //starts to draw a polygon
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f); //red color
	glVertex2f(-0.1, 0.4); //define the first point of the polygon,top left
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f); //yellow color
	glVertex2f(-0.1, 0.4); //next point, top right
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f); //blue color
	glVertex2f(0.1, -0.3); //bottom right
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f); //green color
	glVertex2f(-0.3, -0.3); //last point of the polygon, bottom left
	glEnd(); // defines the end of the draw

	glPopMatrix();
}

void HelloGL::DrawParallelogram()
{
	glPushMatrix();
	glTranslatef(0.5f, 0.5f, 0.5f);
	glRotatef(rotation, 0.0f, 0.0f, -1.0f);

	glBegin(GL_POLYGON); //starts to draw a polygon
	glColor4f(1.0f, 0.0f, 0.0f, 0.0f); //red color
	glVertex2f(-0.1, 0.3); //define the first point of the polygon,top left
	glColor4f(1.0f, 1.0f, 0.0f, 0.0f); //yellow color
	glVertex2f(0.2, 0.37); //next point, top right
	glColor4f(0.0f, 0.0f, 1.0f, 0.0f); //blue color
	glVertex2f(0.1, -0.3); //bottom right
	glColor4f(0.0f, 1.0f, 0.0f, 0.0f); //green color
	glVertex2f(-0.2, -0.37); //last point of the polygon, bottom left
	glEnd(); // defines the end of the draw

	glPopMatrix();
}

void HelloGL::DrawPolygon()
{
	glBegin(GL_POLYGON);
	{
		glVertex2f(-0.5, 0.5); //define the first point of the polygon, top left
		glVertex2f(0.0, 0.7);
		glVertex2f(0.5, 0.5); //next point, top right
		glVertex2f(0.5, -0.5); //bottom right
		glVertex2f(0.0, -0.7);
		glVertex2f(-0.5, -0.5); //last point of the polygon, bottom left
		glEnd(); //defines the end of the draw
	}
}*/
