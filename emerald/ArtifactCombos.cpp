// dllmain.cpp: определяет точку входа для приложения DLL.
#include "emerald.h"

void EnableCombos(void) {
	emerald->WriteDword(0x717079,NEW_ARTS_AMOUNT); //BuildUpCombo


	emerald->WriteDword(0x4E2D3D, (int)EmeraldArtNewTable + 4 * NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x4E2DD7, (int)EmeraldArtNewTable + 4 * NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x4E2EAC, (int)EmeraldArtNewTable + 4 * NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x4E2F41, (int)EmeraldArtNewTable + 4 * NEW_ARTS_AMOUNT);
}