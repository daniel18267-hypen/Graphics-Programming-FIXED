#pragma once
class HelloGL;

namespace GLUTCallbacks
{
	void Init(HelloGL* gl);
	void Display();
	void Timer(int preferredrefresh);
	void Keyboard(unsigned char key, int x, int y);
	void Mouse(int x, int y);
}