#include<Windows.h>
#include<conio.h>
#include"../includes/kbInput.h"

bool kbi::isKeyHeld(int key) 
{
	short keyState = GetKeyState(key);
	return keyState & 0x8000;
}

bool kbi::isKeyToggled(int key) 
{
	short keystate = GetKeyState(key);
	return keystate & 0x0001;
}

int kbi::cursorX()
{
	POINT currPos;
	int result = GetCursorPos(&currPos);

	return (result * currPos.x);
}

int kbi::cursorY()
{
	POINT currPos;
	int result = GetCursorPos(&currPos);

	return (result * currPos.y);
}