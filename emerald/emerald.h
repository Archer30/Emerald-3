#pragma once
//ƒанные, общие дл€ всего модул€.

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
//#include "Tchar.h"
#include <io.h>
#include "..\__include\era.h"

#include "..\__include\heroes.h"
#include "..\__include\patcher_x86_commented.hpp"


inline bool FileExists(const char* chPath) {
	return(_access(chPath, 0) == 0);
}

//#define OLD_ARTS_AMOUNT	171
//#define NON_BLANK_ARTS_AMOUNT	161
// #define NEW_ARTS_AMOUNT 1000
//#define char_table_size 512
//#define int_tuple_size 256

//#define SPELLS_AMOUNT	128		//зачем жалеть пам€ть?

#define PINSTANCE_MAIN "emerald3_3"

//Savegame
#include"MyTypes.h"
/*
inline void init_GAMEDATA_footer(void) {
	strcpy(save.footer, "here is emerald.");
}
*/

extern GAMEDATA save;
extern GAMEDATA2 no_save;
//static ART_RECORD* EmeraldArtBase = no_save.newtable;

extern ART_RECORD* EmeraldArtNewTable; // no_save.newtable;
extern ART_BONUS* EmeraldArtNewBTable; // no_save.newbtable;

extern Patcher * globalPatcher;
extern PatcherInstance * emerald;



extern "C" __declspec(dllexport) void CastArtifactSpell(int artifact, int spell, int duration);
extern "C" __declspec(dllexport)void ExecErmSequence(char* command);

inline void pause(void) {
	MessageBoxA(0, "Program Interuption" , "PAUSE" , 0);
}