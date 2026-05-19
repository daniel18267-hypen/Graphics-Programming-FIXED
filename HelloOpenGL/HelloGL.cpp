#include "HelloGL.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	
	HelloGL::InitGL(argc,argv);
	HelloGL::InitObjects();
	HelloGL::InitLighting();
	glutMainLoop();
		
}
/// <summary>
/// initialises window, enables everything that needs enabling, starts glutcallbacks.
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
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
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	// enables anti aliasing on sceneobjects
	glEnable(GL_LINE_SMOOTH);
	glCullFace(GL_BACK);
}
/// <summary>
/// initialises a light at 0,0,0 in the scene.
/// </summary>
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
/// <summary>
/// initalises all objects in the scene, and variables related to those objects.
/// </summary>
void HelloGL::InitObjects()
{
	yaw = -90.0f;
	index = 0;
	offset = 5.0f;
	camera = new Camera();
	// this is a varible for linked list, essentially first object is dealt with differently.
	firstobject = true;
	// used for determining if object tracking camera should be used or not.
	objectselectmode = false;
	// loads in meshes
	Mesh* horsemesh = MeshLoader::LoadAdvanced("horse.obj");
	Mesh* dogmesh = MeshLoader::LoadAdvanced("dog.obj");
	// initiating linked list class and texture2d classes
	linkedlist = new LinkedList();
	 dogtexture = new Texture2D();
	 horsetexture = new Texture2D();
	// loading in textures
	horsetexture->Load((char*)"horsetexture.tga");
	dogtexture->Load((char*)"dogtexture.tga");
	// instantiates objects in world and stores them in linked list. first object is dealt with differently.
	for (int i = 0; i < 10; i++)
	{
		if (firstobject == true)
		{
			sceneobject = new BasicObject(horsemesh, horsetexture, xpos,ypos,zpos);
			// linked lists head is already made, so if first object sets the heads data to be the sceneobject 
			linkedlist->head->data = sceneobject;
			// list length is used so when updating sceneobjects index doesn't go out of bounds.
			listlength++;
			// increases x position by 5 after instantiating object, so they are seperate
			xpos += 10;
			firstobject = false;
		}
		else
		{
			if (i < 5)
			{
				// same as before but not first object so doesn't make them head of linked list, just makes new head instead.
				sceneobject = new BasicObject(dogmesh, dogtexture, xpos, ypos, zpos);
			}
			else
			{
				sceneobject = new BasicObject(horsemesh, horsetexture, xpos, ypos, zpos);
			}
			listlength++;
			linkedlist->MakeNode(&linkedlist->head, sceneobject);
			xpos += 10;

		}
	}
	// sets up camera positions
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	// sets currentobject to first object , this is what object you can manipulate and look at if in object tracking mode.
	currentobject = linkedlist->GetNode(0)->data;
}
// destructor
HelloGL::~HelloGL(void)
{
	delete camera;
}
void HelloGL::Display()
{
	// sets background colour
	glClearColor(0.0,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// traverses linked list and performs draw function on the objects.
	for (int i = 0; i < listlength; i++)
	{
		ListNode* node = linkedlist->GetNode(i);
		node->data->Draw();
	}
	// draws the HUD
	DrawUI();
	
}
/// <summary>
/// called 60 times a second, updates objects, lighting, camera.
/// </summary>
void HelloGL::Update()
{
	// calls load identity so matrix is reset.
	glLoadIdentity();
	// updates lighting
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightdata->ambient.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightdata->specular.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightdata->diffuse.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightposition->x));
	// if not in object select mode, normal camera, if you are it looks at the object you have selected
	if (objectselectmode == false)
	{
		gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	}
	if (objectselectmode == true)
	{
		objectpos = currentobject->GetPos();
		gluLookAt(objectpos.x - offset, objectpos.y - offset, objectpos.z - offset, objectpos.x,objectpos.y,objectpos.z, camera->up.x, camera->up.y, camera->up.z);
	}
	// loops through linked list, updating things.
	for (int i = 0; i < listlength; i++)
	{
		if (i <= 3)
		{
			linkedlist->GetNode(i)->data->Update();
		}
		// individually animates certain objects
		if (i == 5)
		{
			linkedlist->GetNode(i)->data->Rotate(0.0f, -2.5f, -10.0f, 1.0f);
		}
		if (i == 6)
		{
			linkedlist->GetNode(i)->data->Rotate(0.f, 2.5f, 10.0f, 1.0f);
		}
		
	}
	// redraws scene
	glutPostRedisplay();
}

/// <summary>
/// Detects keyboard inputs and does things accordingly
/// </summary>
/// <param name="key"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	
	if (key == 'w')
	{
		// if not in object select mode, move camera forward.
		if (objectselectmode == false)
		{
			camera->eye.x += 0.5f * front.x;
			camera->eye.y += 0.5f * front.y;
			camera->eye.z += 0.5f * front.z;
			camera->center.x = camera->eye.x + front.x;
			camera->center.y = camera->eye.y + front.y;
			camera->center.z = camera->eye.z + front.z;
		}
		// if in object select mode, rotates the object forwards on the x axis.
		if (objectselectmode == true)
		{
			currentobject->Rotate(1.0f, 0.0f, 0.0f, 1);
		}
	}
	if (key == 's')
	{
		// if not in object select mode, move camera backwards
		if (objectselectmode == false)
		{
			camera->eye.x -= 0.5f * front.x;
			camera->eye.y -= 0.5f * front.y;
			camera->eye.z -= 0.5f * front.z;
			camera->center.x = camera->eye.x + front.x;
			camera->center.y = camera->eye.y + front.y;
			camera->center.z = camera->eye.z + front.z;
		}
		// if in object select mode, rotates the object backwards on the x axis.
		if (objectselectmode == true)
		{
			currentobject->Rotate(1.0f, 0.0f, 0.0f, -1);
		}
	}
	// if in object select mode and a is pressed, rotate the object backwards on the y axis.
	if (key == 'a' && objectselectmode == true)
	{
		currentobject->Rotate(0.0f, 1.0f, 0.0f, -1);
	}
	// if in object select mode and d is pressed, rotate the object forward on the y axis.
	if (key == 'd' && objectselectmode == true)
	{
		currentobject->Rotate(0.0f, 1.0f, 0.0f, 1);
	}
	// cycles through objects on screen by using linked list, and sets it as currentobject and stops any non - player controlled animation on them, to allow user to manipulate.
	if (key == 'j' && objectselectmode == true)
	{
		index++;
		if (index >= listlength)
		{
			index = 0;
		}
		
		currentobject->IsSelected();
		currentobject = linkedlist->GetNode(index)->data;
		currentobject->IsSelected();
		
	}
	// does same as above - but in opposite direction.
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
	// turns object select mode on / off.
	if (key == 'e')
	{
		currentobject->IsSelected();
		objectselectmode = !objectselectmode;
		std::cout << objectselectmode;
	}
	// changes texture to different texture.
	if (key == 'r' && objectselectmode == true)
	{
		currentobject->ChangeTexture(dogtexture);
	}
	if (key == 't' && objectselectmode == true)
	{
		currentobject->ChangeTexture(horsetexture);
	}
}
/// <summary>
/// used for mouse camera movement, takes in the x and y values.
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void HelloGL::Mouse(int x, int y)
{
	// gets difference between previous x and y values and current x and y values.
	 xdiff = x - lastx;
	 ydiff = y - lasty;
	 // sets sensitivity
	 sensitivity = 1;
	 // sets lastx + lasty now they're not used for this loop anymore
	lastx = x;
	lasty = y;
	// sets yaw and pitch to be the difference multipled by sensitivity (multiplied by 2 for pitch as it felt better)
	yaw += xdiff * sensitivity;
	pitch += ydiff * (sensitivity * 2);
	// clams pitch
	if (pitch > 90.0f)
	{
		pitch = 90.0f;
	}
	if (pitch < -90.0f)
	{
		pitch = -90.0f;
	}
	// converts yaw and pitch to radians
	 yawrad = (yaw * (3.14f / 180));
	 pitchrad = (pitch * (3.14f / 180));
	 // front is a vector 3, converts the pitch and yaw into where mouse should be looking at.
	front.x = cos(yawrad) * cos(pitchrad);
	front.y = sin(pitchrad);
	front.z = cos(pitchrad) * sin(yawrad);
	// moves camera to be looking in direction mouse has moved.
	camera->center.x = camera->eye.x + front.x;
	camera->center.y = camera->eye.y + front.y;
	camera->center.z = camera->eye.z + front.z;
	
}

void HelloGL::DrawUI()
{
	// sets the text position
	// sets string, as this string changes depending on object change
	currentobjectselected = "Current object selected:" + std::to_string(index);
	// draws string, converts string to an array of characters first.
	HelloGL::DrawString(currentobjectselected.c_str(),   100.0f, 100.0f);
	// changes string based on current camera mode
	if (objectselectmode == true)
	{
		cameramode = "Camera Mode: object selection mode";
	}
	else if (objectselectmode == false)
	{
		cameramode = "Camera Mode: free camera";
	}
	// draws that stromg
	HelloGL::DrawString(cameramode.c_str(),   150.0f, 150.0f);
	// sets string by getting position of camera.
	 camerapos = "x " + std::to_string(camera->eye.x) + " y " + std::to_string(camera->eye.y) + " z " + std::to_string(camera->eye.z);
	 // draws that string, and string with control instructions.
	HelloGL::DrawString(camerapos.c_str(),   200.0f, 200.0f);
	HelloGL::DrawString("E to change camera mode, W, S and Mouse to Move, H and J to change object selected when in object selection mode",   250.0f, 250.0f);
	HelloGL::DrawString("R and T to change texture of objects", 300.0f, 300.0f);
	glFlush();
	glutSwapBuffers();
}
/// <summary>
/// called from DrawUI() draws string on screen.
/// </summary>
/// <param name="text"></param>
/// <param name="position"></param>
/// <param name="color"></param>
/// <param name="rasterposx"></param>
/// <param name="rasterposy"></param>
void HelloGL::DrawString(const char* text,   float rasterposx, float rasterposy)
{
	// disables depth testing so text doesn't render behind objects.
	glDisable(GL_DEPTH_TEST);
	// resets  both matrices 
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	// goes into orthographic mode, rendering on the "hud" essentially
	gluOrtho2D(0, 1920, 1080, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2f(rasterposx, rasterposy);
	// draws string
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)(text));
	// pops matrices off stack and enables depth testing again.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	

	
}

