#include "emerald.h"
#include<Windows.h>
//extern GAMEDATA save;

void DebugWindow(void) {
	char txt[1024];
	int base = *(int*)0x699538; // (int)EmeraldArtNewTable;// *(int*)0x699538;
	//void* atSave; atSave = &save;
	int atSave = (int) save.used_artifacts;

	MessageBoxA(0, "Emerald","Loaded Plugin" , 0);
	
	sprintf(txt, "%X", atSave);
	MessageBoxA(0, txt, "atSave", 0);

	sprintf(txt, "%X", (int)EmeraldArtNewTable);
	MessageBoxA(0, txt, "EmeraldArtNewTable", 0);

	sprintf(txt, "%X", base);
	MessageBoxA(0, txt, "base", 0);

	return;
}

void __stdcall DebugWindow(PEvent e) {
	DebugWindow();
}
