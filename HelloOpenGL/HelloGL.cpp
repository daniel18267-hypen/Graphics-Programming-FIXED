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
	glutPassiveMotionFunc(GLUTCallbacks::Mouse);
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
	yaw = -90.0f;
	index = 0;
	offset = 5.0f;
	camera = new Camera();
	firstobject = true;
	objectselectmode = false;
	Mesh* cubeMesh = MeshLoader::LoadTextured("cube.txt");
	Mesh* OBJmesh = MeshLoader::LoadAdvanced("monkey.obj");
	linkedlist = new LinkedList();
	 
	//Mesh* pyramidMesh = MeshLoader::Load("pyramid.txt");
	//Mesh* objmesh = MeshLoader::LoadAdvanced("teapot.obj");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Triplet.raw",512,512);
	
	
	for (int i = 0; i < 3; i++)
	{
		if (firstobject == true)
		{
			sceneobject = new BasicObject(OBJmesh, texture, xpos,ypos,zpos);
			linkedlist->head->data = sceneobject;
			listlength++;
			xpos += 5;
			firstobject = false;
		}
		else
		{
			sceneobject = new BasicObject(OBJmesh, texture, xpos, ypos, zpos);
			listlength++;
			linkedlist->MakeNode(&linkedlist->head, sceneobject);
			xpos += 5;
		}
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
	currentobject = linkedlist->GetNode(0)->data;
}
HelloGL::~HelloGL(void)
{
	delete camera;
}
void HelloGL::Display()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 3; i++)
	{
		ListNode* node = linkedlist->GetNode(i);
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
	if (objectselectmode == false)
	{
		gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	}
	if (objectselectmode == true)
	{
		objectpos = currentobject->GetPos();
		gluLookAt(objectpos.x - offset, objectpos.y - offset, objectpos.z - offset, objectpos.x,objectpos.y,objectpos.z, camera->up.x, camera->up.y, camera->up.z);
	}
	//for (int i = ; i < 500; i++)
	//{
	//	sceneobject[i]->Update();
		//object[i]->Update();
	//}
	for (int i = 0; i < listlength; i++)
	{
		linkedlist->GetNode(i)->data->Update();
	}
	glutPostRedisplay();
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	
	if (key == 'w')
	{
		if (objectselectmode == false)
		{
			camera->eye.x += 0.5f * front.x;
			camera->eye.y += 0.5f * front.y;
			camera->eye.z += 0.5f * front.z;
			camera->center.x = camera->eye.x + front.x;
			camera->center.y = camera->eye.y + front.y;
			camera->center.z = camera->eye.z + front.z;
		}
		if (objectselectmode == true)
		{
			currentobject->Rotate(1.0f, 0.0f, 0.0f, 1);
		}
		//camera->center.z += 0.1f;
	}
	if (key == 's')
	{
		if (objectselectmode == false)
		{
			camera->eye.x -= 0.5f * front.x;
			camera->eye.y -= 0.5f * front.y;
			camera->eye.z -= 0.5f * front.z;
			camera->center.x = camera->eye.x + front.x;
			camera->center.y = camera->eye.y + front.y;
			camera->center.z = camera->eye.z + front.z;
		}
		if (objectselectmode == true)
		{
			currentobject->Rotate(1.0f, 0.0f, 0.0f, -1);
		}
	}
	if (key == 'a' && objectselectmode == true)
	{
		currentobject->Rotate(0.0f, 1.0f, 0.0f, -1);
	}
	if (key == 'd' && objectselectmode == true)
	{
		currentobject->Rotate(0.0f, 1.0f, 0.0f, 1);
	}
	if (key == 'j' && objectselectmode == true)
	{
		currentobject->IsSelected();
		currentobject = linkedlist->GetNode(index)->data;
		currentobject->IsSelected();
		index++;
		if (index >= listlength)
		{
			index = 0;
		}
		
	}
	if (key == 'h' && objectselectmode == true)
	{
		index--;
		
		
		if (index < 0)
		{
			index = listlength-1;
		}
		currentobject->IsSelected();
		currentobject = linkedlist->GetNode(index)->data;
		currentobject->IsSelected();
	}
	
	if (key == 'e')
	{
		currentobject->IsSelected();
		objectselectmode = !objectselectmode;
		std::cout << objectselectmode;
	}

	
	
}
void HelloGL::Mouse(int x, int y)
{
	int xdiff = x - lastx;
	int ydiff = y - lasty;
	float sensitivity = 1;
	lastx = x;
	lasty = y;
	yaw += xdiff * sensitivity;
	pitch += ydiff * (sensitivity * 2);
	if (pitch > 90.0f)
	{
		pitch = 90.0f;
	}
	float yawrad = (yaw * (3.14f / 180));
	float pitchrad = (pitch * (3.14f / 180));
	front.x = cos(yawrad) * cos(pitchrad);
	front.y = sin(pitchrad);
	front.z = cos(pitchrad) * sin(yawrad);
	/*float length = sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
	front.x /= length;
	front.y /= length;
	front.z /= length; */
	camera->center.x = camera->eye.x + front.x;
	camera->center.y = camera->eye.y + front.y;
	camera->center.z = camera->eye.z + front.z;


	
}

