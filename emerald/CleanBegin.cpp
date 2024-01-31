
#include "emerald.h"
//#include "MyTypes.h"

char empty_text[1024] = "EMERALD_3_3 BUG";

void CleanBegin(void) {
	memset(&save, 0x00, sizeof(save));
	memset(&no_save, 0x00, sizeof(no_save));

	for (int i = 0;i < STORED_ARTS_AMOUNT; i++) {
		// no_save.artDescTable[i] = empty_text;
		// no_save.artNameTable[i] = empty_text;
		strcpy(no_save.artDescTable[i], empty_text);
		strcpy(no_save.artNameTable[i], empty_text);

		no_save.newtable[i].name = no_save.artNameTable[i];
		no_save.newtable[i].desc = no_save.artDescTable[i];

		//strcpy(no_save.arteventtable[i], empty_text);
		no_save.arteventtable[i] = empty_text;

		no_save.ArtSetUpBack[i].name = no_save.artNameTable[i];
		no_save.ArtSetUpBack[i].desc = no_save.artDescTable[i];
	}
}