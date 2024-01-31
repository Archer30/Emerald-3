#include "era.h"

void ConnectEra()
{
	HINSTANCE hAngel = LoadLibrary((LPCWSTR)"angel.dll");

	&SaveEventParams =  (void (__stdcall *)(void))
		GetProcAddress(hAngel, "SaveEventParams");
}