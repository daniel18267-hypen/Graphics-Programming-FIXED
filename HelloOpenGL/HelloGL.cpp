#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	
	HelloGL::InitGL(argc,argv);
	HelloGL::InitObjects();
	glutMainLoop();
		
}
void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(RefreshRate, GLUTCallbacks::Timer, RefreshRate);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	
}
void HelloGL::InitObjects()
{
	camera = new Camera();
	Mesh* cubeMesh = MeshLoader::LoadTextured("cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load("pyramid.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Triplet.raw",512,512);
	//objectloader::Load((char*)"teapot.obj");
	for (int i = 0; i < 500; i++)
	{
		sceneobject[i] = new Cube(cubeMesh, texture,((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 500; i < 1000; i++)
	{
		sceneobject[i] = new Pyramid(pyramidMesh,texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 0; i < 1000; i++)
	{
		object[i] = new objectloader(((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}
HelloGL::~HelloGL(void)
{
	delete camera;
}
void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 1000; i++)
	{
		 sceneobject[i]->Draw();
		//object[i]->Draw();
	}
	glFlush();
	glutSwapBuffers();
	
}
void HelloGL::Update()
{
	glLoadIdentity();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	for (int i = 0; i < 1000; i++)
	{
		sceneobject[i]->Update();
		//object[i]->Update();
	}
	
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		camera->eye.z += 0.1f;
		camera->center.z += 0.1f;
	}
	if (key == 's')
	{
		camera->eye.z -= 0.1f;
		camera->center.z -= 0.1f;
	}
	if (key == 'a')
	{
		camera->eye.x += 0.1f;
		camera->center.x += 0.1f;
	}
	if (key == 'd')
	{
		camera->eye.x -= 0.1f;
		camera->center.x -= 0.1f;
	}
}

