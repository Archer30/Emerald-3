// dllmain.cpp: Defines the entry point for the DLL application.
#include "emerald.h"

extern void __stdcall  Emerald(PEvent e);
//extern void __stdcall  UndoEmerald(PEvent e);

extern void __stdcall ReallocProhibitionTables(PEvent e);
extern void __stdcall LoadConfigs(PEvent e);
// extern void __stdcall blank(int first);
extern void CleanBegin(void);

// GAMEDATA save;
// GAMEDATA2 no_save;
Patcher * globalPatcher;
PatcherInstance *emerald;

unsigned long SaveLocker;

extern void DebugWindow(void);
extern void __stdcall DebugWindow(PEvent e);
//extern void __stdcall UndoProhibitionTables(PEvent e);


extern void __stdcall EmeraldRedo(PEvent e);
extern void __stdcall EmeraldUndo(PEvent e);
// extern void __stdcall EmeraldMove(PEvent e);
extern void __stdcall EmeraldStrings(PEvent e);
extern void __stdcall EmeraldStrings2(PEvent e);

unsigned int InChat, InDialog, IsTidy, SpecialDialog, click_locked;

/*
void __stdcall CheckDialog(PEvent e) {
	return;

	static TGameState state;
	*TGetGameState(&state);

	if ((state.CurrentDlgId != state.RootDlgId) ||
		(state.CurrentDlgId != 4205280))
	{
		/// *(ErmY + 1) = temp;
		InDialog = false;
		// Tidy(e);

	}
	else {
		InDialog = true;
		if (state.RootDlgId == 4205280)
			SpecialDialog = true;
		else SpecialDialog = false;
	}
}
*/

/*
void __stdcall Chat(PEvent e) {
	if (SaveLocker) return;

	int tmp = *(ErmY + 1);
	ExecErmCmd("SN:X?y1;");
	if ( *(ErmY + 1) == 0)ExecErmCmd("SN:W^InChat^/1;");
	if ( *(ErmY + 1) == 2)ExecErmCmd("SN:W^InChat^/0;");
	ExecErmCmd("SN:W^InChat^/?y1;");
		
	InChat= *(ErmY + 1);
	 *(ErmY + 1)=tmp;
}
*/

/*
void __stdcall Refresh(PEvent e) {
	//CheckDialog(e);
	//if (InDialog) return;
	
	//emerald->WriteDword(0x7324BD, NEW_ARTS_AMOUNT); //UN:A
	//blank(NON_BLANK_ARTS_AMOUNT);
	
	int UN_A = *(int*) 0x7324BD;
	if (UN_A != NEW_ARTS_AMOUNT )
		IsTidy=false;
	//else IsTidy = true; // _
}
*/


void __stdcall Tidy(PEvent e) {
	//CheckDialog(e);
	//if (InDialog) return;
	
	//if (click_locked) return;
	//Refresh(e);
	//if (IsTidy) return;
	//blank(NON_BLANK_ARTS_AMOUNT);

	/*
	EmeraldArtNewTable = save.newtable;
	EmeraldArtNewBTable = save.newbtable;
	Emerald(e);
	*/

	//ReallocProhibitionTables(e);
	//blank(NON_BLANK_ARTS_AMOUNT);
	//IsTidy = true;

	EmeraldRedo(e);
}





void __stdcall Clean(PEvent e) {
	//CheckDialog(e);
	//if (InDialog) return;
	
	//Refresh(e);
	//if (!IsTidy) return;
	
	
	//// Is it still needed? (should be not)
	//UndoProhibitionTables(e);
	EmeraldUndo(e);
	
	
	//IsTidy = false;
}




/*
void __stdcall Click(PEvent e) {
	if (SaveLocker) return;

	if (click_locked) {
		//click_locked = false;
		ExecErmCmd("CM:R0;");
		//return;
	}

	//CheckDialog(e);
	//if(InDialog) return;

	int temp = *(ErmY + 1);

	ExecErmCmd("CM:I?y1;");
	//if (*(ErmY + 1) == 3) DebugWindow();

	if (*(ErmY + 1) != 10 ) {
		*(ErmY + 1) = temp;
		if ( (InDialog || click_locked) 
		// && (!save_state)
		) {
			click_locked = false;
			return;
		}

		Tidy(e);
		return;
	}else{

	*(ErmY + 1) = temp;
	Clean(e);
	return;
	}
}
*/

/*
void __stdcall Key(PEvent e) {
	if (SaveLocker) return;

	if (InChat) return;

	CheckDialog(e);
	if (InDialog) return;

	int temp = *(ErmY + 1);
	ExecErmCmd("SN:X?y1;");

	if ( *(ErmY + 1) != 76 && *(ErmY + 1) != 108 &&
		 *(ErmY + 1) != 83 && *(ErmY + 1) != 115 &&
		 *(ErmY + 1) != 69 && *(ErmY + 1) != 101 &&
		true)
	{

		*(ErmY + 1) = temp;
		Tidy(e);  return;
	}
	else {
		*(ErmY + 1) = temp;
		Clean(e); return;
	}

}
*/

void __stdcall InitData3 (PEvent e)
{

	static bool first_time = true;
	//MessageBoxA(0, "Emerald::InitData3", "Emerald::InitData3", 0);

	//EmeraldMove(e);

	//pause();
	//EmeraldMove(e);

	EmeraldArtNewTable = no_save.newtable;//save.newtable;//no_save.newtable;
	EmeraldArtNewBTable = no_save.newbtable;//save.newbtable;//no_save.newbtable;
	Emerald(e);

	if(!first_time) ReallocProhibitionTables(e);
	LoadConfigs(e);
	EmeraldStrings(e); // modified at 2017-12-12

	/*
   // fix getartbase and getartname wog functions
	emerald->WriteDword(0x0071498E, (int)EmeraldArtBase);
	emerald->WriteDword(0x00714FA8, (int)EmeraldArtBase);
	*/

	//Refresh_Artifact(e);
	//pause();


	//MessageBoxA(0, "Emerald::InitData3 done", "Emerald::InitData3 done", 0);

	/*
	memcpy(save.newtable, no_save.newtable, sizeof(ART_RECORD)*NEW_ARTS_AMOUNT);
	memcpy(save.newbtable, no_save.newbtable, sizeof(ART_BONUS)*NEW_ARTS_AMOUNT);


	EmeraldArtNewTable = save.newtable;
	EmeraldArtNewBTable = save.newbtable;
	Emerald(e);
	*/
	first_time = false;
}

/*
void __stdcall InitData2(PEvent e)
{
	int y2 = *(ErmY + 2);
	ExecErmCmd("SN:W^Emerald Enabled^/?y2;");
	if (*(ErmY + 2) == 1) return;
	ExecErmCmd("SN:W^Emerald Enabled^/1;");
	ReallocProhibitionTables(e);
	//Emerald(e);
	LoadConfigs(e);
	//EmeraldMove(e);
	EmeraldStrings(e);
		
	*(ErmY + 2) = y2;

}
*/

/*
void __stdcall InitData1(PEvent e)
{
	ReallocProhibitionTables(e);
	LoadConfigs(e);
}
*/


void __stdcall StoreData (PEvent e)
{

	//MessageBoxA(0, "Emerald::StoreData BUMP 01", "Emerald::StoreData BUMP", 0);

	/*
	////Trying to fix
	for (int i = 0; i < NEW_ARTS_AMOUNT; ++i) {
		//memcpy(&save.newtable[i], &no_save.newtable[i], sizeof(ART_RECORD));
		//memcpy(&save.newbtable[i], &no_save.newbtable[i], sizeof(ART_BONUS));

		if (save.newtable[i].name && save.artname[i] != save.newtable[i].name)
			strncpy(save.artname[i], save.newtable[i].name, char_table_size-1);
		if (save.artname[i][0] == 0 || !(save.newtable[i].name)) {
			strncpy(save.artname[i], "{Unnamed Artifact}", char_table_size - 1);
			save.newtable[i].name = save.artname[i];
		}
			
		if (save.newtable[i].desc && save.artdesc[i] != save.newtable[i].desc)
			strncpy(save.artdesc[i], save.newtable[i].desc, char_table_size-1);
		if (save.artdesc[i][0] == 0 || !(save.newtable[i].desc)) {
			strncpy(save.artdesc[i], "{Undescribed Artifact}", char_table_size - 1);
			save.newtable[i].desc = save.artdesc[i];
		}
	}
	*/
	
	 WriteSavegameSection(sizeof(save), (void*)&save, PINSTANCE_MAIN);
	//WriteSavegameSection(NEW_ARTS_AMOUNT * 2, (void*)&save, PINSTANCE_MAIN);
	 click_locked = true;
	 //SaveLocker = true;

	 //MessageBoxA(0, "Emerald::StoreData BUMP 02", "Emerald::StoreData BUMP", 0);

}


void __stdcall RestoreData (PEvent e)
{

	
	//EmeraldArtNewTable = no_save.newtable;
	//EmeraldArtNewBTable = no_save.newbtable;
	//Emerald(e);
	

	//EmeraldUndo(e);

	//MessageBoxA(0, "Emerald::RestoreData BUMP 01", "Emerald::RestoreData BUMP", 0);

	//ExecErmCmd("SN:W^InChat^/0;");
	ReadSavegameSection(sizeof(save), (void*)&save, PINSTANCE_MAIN);
	//Refresh_Artifact(e);
	//ReadSavegameSection(NEW_ARTS_AMOUNT*2, (void*)&save, PINSTANCE_MAIN);
	
	/*
	////Trying to fix
	for (int i = 0; i < NEW_ARTS_AMOUNT; ++i) {
		//memcpy(&no_save.newbtable[i], &save.newbtable[i], sizeof(ART_BONUS));
		//memcpy(&no_save.newtable[i], &save.newtable[i],sizeof(ART_RECORD));
		//no_save.newtable[i].name = save.artname[i];
		//no_save.newtable[i].desc = save.artdesc[i];
		save.newtable[i].name = save.artname[i];
		save.newtable[i].desc = save.artdesc[i];
	}
	

	EmeraldArtNewTable = save.newtable;
	EmeraldArtNewBTable = save.newbtable;
	Emerald(e);
	*/
	EmeraldStrings2(e);

	//IsTidy = 2; // two steps
	click_locked = true;

	//MessageBoxA(0, "Emerald::RestoreData BUMP 02", "Emerald::RestoreData BUMP", 0);

}


void __stdcall Unlock(PEvent e) {

	// MessageBoxA(0, "Emerald::Unlock", "Emerald::Unlock", 0);

	// ReallocProhibitionTables(e);
	SaveLocker = false;
	
	//Refresh(e);
	//IsTidy = false;

	//Tidy(e); //disabled on 2019-05-20
	
	// ExecErmCmd("SN:W^InChat^/0;");

	ExecErmCmd("FU99001:P;");
}

void __stdcall Lock(PEvent e) {

	// MessageBoxA(0, "Emerald::Lock", "Emerald::Lock", 0);

	ExecErmCmd("FU99002:P;");

	SaveLocker = true;
	//Clean(e); //disabled on 2019-05-20
}


void __stdcall NewGame(PEvent e)
{
	/*
	EmeraldArtNewTable = no_save.newtable;
	EmeraldArtNewBTable = no_save.newbtable;
	Emerald(e);
	LoadConfigs(e);
	*/


	//memcpy(save.newtable, no_save.newtable, sizeof(ART_RECORD)*NEW_ARTS_AMOUNT);
	//memcpy(save.newbtable, no_save.newbtable, sizeof(ART_BONUS)*NEW_ARTS_AMOUNT);


	//EmeraldArtNewTable = save.newtable;
	//EmeraldArtNewBTable = save.newbtable;
	//Emerald(e);


	//memcpy(save.newtable, no_save.newtable, NEW_ARTS_AMOUNT * sizeof(ART_RECORD));
	//memcpy(save.newbtable, no_save.newbtable, NEW_ARTS_AMOUNT * sizeof(ART_BONUS));

	//InitData3(e);

	/*
	for (int i = 0; i < NEW_ARTS_AMOUNT; i++) {
		memcpy(&save.newbtable[i], &no_save.newbtable[i], sizeof(ART_BONUS));
		memcpy(&save.newtable[i], &no_save.newtable[i], sizeof(ART_RECORD));
	}

	Tidy(e);
	*/

	//EmeraldStrings2(e);
	Unlock(e);
}

void __stdcall AfterSaveGame(PEvent e) {

	//EmeraldArtNewTable = save.newtable;
	//EmeraldArtNewBTable = save.newbtable;
	//Emerald(e);
}

/*
void __stdcall NO_SAVE_NEWTABLES(PEvent e) {
	static bool first_time = true;
	if (first_time) {
		memcpy(no_save.newtable, save.newtable, NEW_ARTS_AMOUNT * sizeof(ART_RECORD));
		memcpy(no_save.newbtable, save.newbtable, NEW_ARTS_AMOUNT * sizeof(ART_BONUS));
		//MessageBoxA(0, "NO_SAVE_NEWTABLES", "emerald", MB_OK);
		first_time = false;
	}
}
*/

void __stdcall Z_OnAfterCreateWindow(PEvent e) {

	//MessageBoxA(0, "Emerald::Emerald OnAfterCreateWindow 0", "Emerald::Emerald OnAfterCreateWindow", 0);
	///// was:
	//InitData3(e);

	ReallocProhibitionTables(e);

	////2020-04-03
	//EmeraldArtNewTable = no_save.newtable;//save.newtable;//no_save.newtable;
	//EmeraldArtNewBTable = no_save.newbtable;//save.newbtable;//no_save.newbtable;
	
	//Emerald(e);

	//MessageBoxA(0, "Emerald::Emerald OnAfterCreateWindow 1", "Emerald::Emerald OnAfterCreateWindow", 0);

	LoadConfigs(e);
	//MessageBoxA(0, "Emerald::Emerald OnAfterCreateWindow 2", "Emerald::Emerald OnAfterCreateWindow", 0);
	
	////moved to Z_OnAfterWog
	//ReallocProhibitionTables(e);

	//MessageBoxA(0, "Emerald::Emerald OnAfterCreateWindow 3", "Emerald::Emerald OnAfterCreateWindow", 0);
	//LoadConfigs(e);
	//EmeraldStrings2(e); // modified at 2017-12-12

	//MessageBoxA(0, "Emerald::Emerald OnAfterCreateWindow 4", "Emerald::Emerald OnAfterCreateWindow", 0);

	//EmeraldUndo(e);
}

void __stdcall Z_OnAfterWog(PEvent e) {
	//MessageBoxA(0, "This is alpha version of Emerald. do not use.", "Emerald::Emerald OnAfterWog", 0);


	//MessageBoxA(0, "Emerald::Emerald OnAfterWog 0", "Emerald::Emerald OnAfterWog", 0);
	///// was:
	//InitData3(e);

	//EmeraldArtNewTable = no_save.newtable;//save.newtable;//no_save.newtable;
	//EmeraldArtNewBTable = no_save.newbtable;//save.newbtable;//no_save.newbtable;

	Emerald(e);
	ReallocProhibitionTables(e);


	//Lock(e);

	EmeraldStrings2(e);


}


void __stdcall Z_OnAfterErmInstructions(PEvent e) {
	//MessageBoxA(0, "Emerald::Emerald Z_OnAfterErmInstructions", "Emerald::Emerald Z_OnAfterErmInstructions", 0);

	///// was:
	//NewGame(e);

	//Unlock(e);

}


void __stdcall OnNewDay(PEvent e);
void __stdcall OnBattleStart(PEvent e);
void __stdcall OnBattleEnd(PEvent e);
void __stdcall OnEquip(PEvent e);
void __stdcall OnUnequip(PEvent e);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		
		static bool FirstTime = true;
		if(FirstTime)
		{
			//DebugWindow();
			//save.footer = 0;
			IsTidy = true; InChat = false; 
			InDialog = true; SpecialDialog = false;
			click_locked = true; SaveLocker = true;

			CleanBegin();

			//strcpy(save.footer, "here is emerald save.");
			//strcpy(save.header, "here is emerald save.");
			char emerald_save_marker[64] = "here is emerald save.";
			memcpy((void *)save.footer, emerald_save_marker, 64);
			memcpy((void *)save.header, emerald_save_marker, 64);
			//strcpy(save.header, "here is emerald save.");

			//strcpy(no_save.footer, "here is emerald not saved.");
			//strcpy(no_save.header, "here is emerald not saved.");
			char emerald_no_save_marker[64] = "here is emerald not saved.";
			memcpy((void *)no_save.footer, emerald_no_save_marker, 64);
			memcpy((void *)no_save.header, emerald_no_save_marker, 64);

			unsigned char _magic[22] = { 
				0x6A,0x01,0x6A,0x09,
				0x8D,0x4D,0xE4,0xB8,
				0xA0,0x67,0x4E,0x00,
				0xFF,0xD0,0xB8,0x9D,
				0x97,0x4D,0x00,0xFF,
				0xE0,0x90 
			}; //машкод кейса, ответственного за добавление заклинания артефакту.
			memcpy((void*) no_save._magic, _magic, 22);

			no_save.enchanted_artifacts_count = 9;
			int enchanted_artifacts[] =
			{ 0x01,0x80,0x7B,0x7C,
				0x56,0x57,0x58,0x59,
				0x87 };	//список артефактов, дающих заклинания. 
						//Для добавления - дописываем свой арт в конец списка 
						//и задаем ему заклинание через artspelltable
			memcpy(no_save.enchanted_artifacts, enchanted_artifacts, 4*9);

			memset(no_save.autosummon,-1, 4*9* STORED_ARTS_AMOUNT);


			EmeraldArtNewTable = no_save.newtable;//save.newtable;//no_save.newtable;
			EmeraldArtNewBTable = no_save.newbtable;//save.newbtable;//no_save.newbtable;

			
			FirstTime = false;
		}
		
		 
		globalPatcher = GetPatcher();
		emerald =  globalPatcher->CreateInstance(PINSTANCE_MAIN);
		ConnectEra();

		//Storing data
		//RegisterHandler(InitData2, "OnErmTimer 1");
		//RegisterHandler(InitData1, "OnBeforeErmInstructions");
		
		RegisterHandler(StoreData, "OnSavegameWrite");
		RegisterHandler(RestoreData, "OnSavegameRead");
		//RegisterHandler(InitData1, "OnAfterCreateWindow");

		//RegisterHandler(AfterSaveGame, "OnAfterSaveGame");

		//EmeraldArtNewTable = no_save.newtable;
		//EmeraldArtNewBTable = no_save.newbtable;


		////InitData3 fires too late

		////2020-04-02
		//RegisterHandler(InitData3, "OnAfterCreateWindow"); //original
		RegisterHandler(Z_OnAfterCreateWindow, "OnAfterCreateWindow"); //original
		
		//RegisterHandler(InitData3, "OnBeforeWog"); 
		

		////2020-04-02
		//RegisterHandler(InitData3, "OnAfterWoG"); //changed at 2017-12-10
		RegisterHandler(Z_OnAfterWog, "OnAfterWoG");
												  
		//RegisterHandler(OnAfterWoG, "OnAfterWoG"); //original
		//RegisterHandler(InitData3, "OnAfterWoG"); //changed at 2017-12-10

		//RegisterHandler(Click, "OnAdventureMapLeftMouseClick");
		//RegisterHandler(Key, "OnKeyPressed");
		//RegisterHandler(Chat, "OnChat");
		
		////Locking: why it can't be  disabled ?
		//// 2020-04-02
		RegisterHandler(Lock, "OnBeforeSaveGame");
		RegisterHandler(Unlock, "OnAfterSaveGame");
		RegisterHandler(Unlock, "OnAfterLoadGame");
		RegisterHandler(Unlock, "OnAfterErmInstructions");

		//RegisterHandler(Unlock, "OnAfterErmInstructions"); // disabled 2019-05-21
		
		////2020-04-02
		//RegisterHandler(NewGame, "OnAfterErmInstructions"); 
		RegisterHandler(Z_OnAfterErmInstructions, "OnAfterErmInstructions");

		RegisterHandler(OnNewDay, "OnEveryDay");

		RegisterHandler(OnBattleStart, "OnBeforeBattleUniversal");
		RegisterHandler(OnBattleEnd, "OnAfterBattleUniversal");

		RegisterHandler(OnEquip, "OnEquipArt");
		RegisterHandler(OnUnequip, "OnUnequipArt");

		//RegisterHandler(NO_SAVE_NEWTABLES, "OnAfterCreateWindow");

	}
	return TRUE;
}

