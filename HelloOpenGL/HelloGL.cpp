#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	
	HelloGL::InitGL(argc,argv);
	HelloGL::InitObjects();
	HelloGL::InitLighting();
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
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
	
}
void HelloGL::InitLighting()
{
	_lightposition = new Vector4();
	_lightposition->x = 0.0;
	_lightposition->y = 0.0;
	_lightposition->z = 0.0;
	_lightposition->w = 0.0;

	_lightdata = new Lighting();
	_lightdata->ambient.x = 0.5;
	_lightdata->ambient.y = 0.5;
	_lightdata->ambient.z = 0.5;
	_lightdata->ambient.w = 1.0;
	_lightdata->diffuse.x = 2.0;
	_lightdata->diffuse.y = 2.0;
	_lightdata->diffuse.z = 2.0;
	_lightdata->diffuse.w = 1.0;
	_lightdata->specular.x = 0.2;
	_lightdata->specular.y = 0.2;
	_lightdata->specular.z = 0.2;
	_lightdata->specular.w = 1.0;
}
void HelloGL::InitObjects()
{
	camera = new Camera();
	Mesh* cubeMesh = MeshLoader::LoadTextured("cube.txt");
	Mesh* OBJmesh = MeshLoader::LoadAdvanced("capsule.obj");
	 linkedlist = new LinkedList();
	//Mesh* pyramidMesh = MeshLoader::Load("pyramid.txt");
	//Mesh* objmesh = MeshLoader::LoadAdvanced("teapot.obj");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Triplet.raw",512,512);
	
	sceneobject = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	linkedlist->head->data = sceneobject;
	for (int i = 0; i < 500; i++)
	{
		sceneobject = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
		linkedlist->MakeNode(&linkedlist->head, sceneobject);
	}

	//for (int i = 500; i < 1000; i++)
	//{
		//sceneobject[i] = new Pyramid(pyramidMesh,texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	//}
	for (int i = 500; i < 1000; i++)
	{
		//inkedList::MakeNod = new BasicObject(OBJmesh, texture,((rand() % 400) / 10.0f) - 20.0f, ((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
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
	for (int i = 0; i < 500; i++)
	{
		ListNode* node = linkedlist->GetNode(1);
		node->data->Draw();
	}
	for (int i = 500; i < 1000; i++)
	{
		// sceneobject[i]->Draw();
		// std::cerr << "got here";
		//object[i]->Draw();
	}
	glFlush();
	glutSwapBuffers();
	
}
void HelloGL::Update()
{
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightdata->ambient.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightdata->specular.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightdata->diffuse.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightposition->x));
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	//for (int i = ; i < 500; i++)
	//{
	//	sceneobject[i]->Update();
		//object[i]->Update();
	//}
	
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

