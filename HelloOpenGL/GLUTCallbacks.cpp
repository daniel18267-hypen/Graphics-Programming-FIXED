// Includes
#include "GlUTCallbacks.h"
#include "HelloGL.h"

// namespace implemenbtation
namespace GLUTCallbacks
{
	namespace
	{
		// initialise to a null pointer before doing anything
		HelloGL* helloGL = nullptr;
	}
	/// <summary>
	/// initialises hellogl class
	/// </summary>
	/// <param name="gl"></param>
	void Init(HelloGL *gl)
	{
		helloGL = gl;
	}
	/// <summary>
	/// calls on display if hellogl class is initialised.
	/// </summary>
	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}
	/// <summary>
	/// calls update 60 frames a second.
	/// </summary>
	/// <param name="refreshrate"></param>
	void Timer(int refreshrate)
	{
		int updatetime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updatetime = glutGet(GLUT_ELAPSED_TIME) - updatetime;
		glutTimerFunc(refreshrate - updatetime, GLUTCallbacks::Timer, refreshrate);
	}
	/// <summary>
	/// sets up callback for keyboard, so can detect what keys are pressed
	/// </summary>
	/// <param name="key"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key,x,y);
	}
	/// <summary>
	/// sets up callback for mouse, getting the x and y position of cursor on screen.
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void Mouse(int x, int y)
	{
		helloGL->Mouse(x, y);
	}
}