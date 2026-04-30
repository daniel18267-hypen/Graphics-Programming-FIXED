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
	void Init(HelloGL *gl)
	{
		helloGL = gl;
	}
	void Display()
	{
		if (helloGL != nullptr)
		{
			helloGL->Display();
		}
	}
	void Timer(int refreshrate)
	{
		int updatetime = glutGet(GLUT_ELAPSED_TIME);
		helloGL->Update();
		updatetime = glutGet(GLUT_ELAPSED_TIME) - updatetime;
		glutTimerFunc(refreshrate - updatetime, GLUTCallbacks::Timer, refreshrate);
	}
	void Keyboard(unsigned char key, int x, int y)
	{
		helloGL->Keyboard(key,x,y);
	}
	void Mouse(int x, int y)
	{
		helloGL->Mouse(x, y);
	}
}