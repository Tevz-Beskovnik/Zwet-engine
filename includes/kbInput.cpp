#include<Windows.h>
#include"kbInput.h"

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