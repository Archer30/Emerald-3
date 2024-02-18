// application of the main code: expanding tables

#include "emerald.h"
#include "SpellSet.h"
//extern GAMEDATA2 no_save;
extern void DebugWindow(void);
extern void __stdcall blank(int first);

extern void EnableCombos(void);
// extern int *enchanted_artifacts;

/*

ART_RECORD newtable[NEW_ARTS_AMOUNT];
ART_BONUS newbtable[NEW_ARTS_AMOUNT];
//char* arteventtable[NEW_ARTS_AMOUNT+1]; 
char arteventtable[NEW_ARTS_AMOUNT + 1] [char_table_size];

char  artspelltable[NEW_ARTS_AMOUNT]; //new table of spells given by artifacts
int artspellswitch[256];      //new switch for this table
unsigned char _magic[22] = {0x6A,0x01,0x6A,0x09,
							0x8D,0x4D,0xE4,0xB8,
							0xA0,0x67,0x4E,0x00,
							0xFF,0xD0,0xB8,0x9D,
							0x97,0x4D,0x00,0xFF,
							0xE0,0x90}; //The machine code of the case responsible for adding the spell to the artifact.
 char new_cases[22*128];  //buffer for new cases that give single spells

 
 int enchanted_artifacts_count = 9;
 int enchanted_artifacts[NEW_ARTS_AMOUNT] = 
 {0x01,0x80,0x7B,0x7C,
  0x56,0x57,0x58,0x59,
  0x87};	//list of artifacts that give spells.
			//To add - add your art to the end of the list
			//and give him a spell via artspelltable
*/
 char *dummy_hint = "Artifact sponsored by emerald.dll. Version from: "\
					__DATE__ \
					" "\
					__TIME__;

 int p_Z_name_0x00A4A588_table[] = {
	 //by majaczek
	0x00732672 + 3, // MOV EAX,DWORD PTR DS:[EDX*8+0A4A588]
	0x0073269f + 3, // MOV DWORD PTR DS:[EAX*8+0A4A588],ECX
	0x0075122c + 3, // LEA EAX,[EDX*8+0A4A588]
	0x00751c94 + 3, // LEA EAX,[EDX * 8 + 0A4A588]
	0x00751dde + 3, // MOV EDX,DWORD PTR DS:[ECX*8+0A4A588]
	0x00752dfa + 3  // MOV DWORD PTR DS : [EAX * 8 + 0A4A588],0
 };
 
 int p_Z_name_0x00A4A58C_table[] = {
	 //by majaczek
	0x0073270a + 3, // MOV EDX,DWORD PTR DS:[ECX*8+0A4A58C]
	0x00732737 + 3, // MOV DWORD PTR DS : [EDX * 8 + 0A4A58C],EAX
	0x007512c0 + 3, // LEA EDX,[ECX*8+0A4A58C]
	0x00751d28 + 3, // LEA EDX,[ECX*8+0A4A58C]
	0x00751e49 + 3, // MOV EAX,DWORD PTR DS:[EDX*8+0A4A58C]
	0x00752e08 + 3  // MOV DWORD PTR DS:[ECX*8+0A4A58C],0
 };

extern int __stdcall NewHasArtifactInBP(HiHook* h, HERO* hero, int art);
extern int __stdcall NewHasArtifact(HiHook* h, HERO* hero, int art);

extern int __stdcall LuckTextHook(LoHook* h, HookContext* c);
extern int __stdcall LuckValueHook(LoHook* h, HookContext* c);
extern int __stdcall MoraleTextHook(LoHook* h, HookContext* c);
extern int __stdcall MoraleValueHook(LoHook* h, HookContext* c);

extern double __stdcall ResistanceHook(HiHook* h, int spell, int creature, HERO* dhero, HERO* ahero);
extern int __stdcall OnCreatureParamInit(HiHook* h, HERO* hero, int creature, MONSTER_PROP* monster);

extern int __stdcall BattleStartHook(LoHook* h, HookContext* c);


extern void __stdcall OnEquip(PEvent e);
extern void __stdcall OnUnequip(PEvent e);
extern void __stdcall OnBattleStart(PEvent e);
extern void __stdcall OnBattleEnd(PEvent e);
extern void __stdcall OnNewDay(PEvent e);


int __stdcall ArtTypesHook(LoHook* h, HookContext* c)
{
	if (c->eax == 'W') 
		{*(int*)(0x0C + c->ebx) = 0x20; return NO_EXEC_DEFAULT;} //war machines
	if (c->eax == 'B') 
		{*(int*)(0x0C + c->ebx) = 0x40; return NO_EXEC_DEFAULT;} //books

	return EXEC_DEFAULT;
}

void CastArtifactSummon(int artifact, int spell, int SpellPower, int SpellLevel) {
	char* combatManager = (char*)(*((int*)0x699420));
	char* tmp;
	
	for (int i = 0; i < 9; i++) if (no_save.autosummon[artifact][i] >= 0) {
		int pow = no_save.autosummon_power[artifact][i];
		if (pow < 0)  (pow *= SpellPower) /= -1000;
		else if (pow == 0) pow = SpellPower;
		if (pow == 0) pow = 1;
		SummonCreature(combatManager, spell, no_save.autosummon[artifact][i], pow, SpellLevel);
	}
}

void CastArtifactSpell(int artifact, int spell, int duration)
{
		char* combatManager = (char*)(*((int*)0x699420));
        char *tmp;

        tmp = GetArtifactRecord(spell)->name;
        GetArtifactRecord(spell)->name = GetArtifactRecord(artifact)->name;
        if ( (unsigned char)sub_5A43E0( combatManager, spell, 3, *(int *)(combatManager + 78528), 1, 2) )
          CastBattleSpell(combatManager, spell, -1, 2, -1, 3, duration);
        GetArtifactRecord(spell)->name = tmp;
}


void ExecErmSequence(char* _command)
{
	if (!ExecErmCmd) ConnectEra();
	if ((!_command) || (!*_command) ) return;

	char command[512];
	memset(command,0,512);
	strcpy(command, _command);

	  char *p;

	  p = strtok(command, "!");
	  ExecErmCmd(p);
	  do {
		p = strtok(NULL, "!");
		if(p) ExecErmCmd(p);
	  } while(p);
}


//// 2020-04-03
// DWORD oldtable =0; DWORD oldbtable = 0; DWORD old_arteventtable = 0;


void __stdcall EmeraldStrings2(PEvent e) {
	return; //2020-04-10

	for (int i = 0; i < NEW_ARTS_AMOUNT; i++) {
		if (!no_save.newtable[i].name) {
			if (!no_save.artNameTable[i])
			{
				// no_save.artNameTable[i] = new char[char_table_size];
				// *(no_save.artNameTable[i]) = 0;
			}
			no_save.newtable[i].name = no_save.artNameTable[i];
		}
		if (!no_save.newtable[i].desc) {
			if (!no_save.artDescTable[i])
			{
				// no_save.artDescTable[i] = new char[char_table_size];
				// *(no_save.artDescTable[i]) = 0;
			}
			no_save.newtable[i].desc = no_save.artDescTable[i];
		}
	}
};
void __stdcall EmeraldStrings(PEvent e) {
	static int first_time = true;
	/*
	if (first_time || true) {
		//ART_RECORD* ptr = (ART_RECORD*)0x00660B68; //oldtable;
		for (int i = 0; i != NEW_ARTS_AMOUNT ; i++) {
			
			// 2017-12-12
			if (!save.newtable[i].desc) {
				no_save.newtable[i].desc = save.artdesc[i];
				save.newtable[i].desc = save.artdesc[i];
				// strncpy(no_save.newtable[i].desc, dummy_hint, char_table_size - 1);
			}
			



			// 2017-12-12
			if (!save.newtable[i].name) {

				no_save.newtable[i].name = save.artname[i];
				save.newtable[i].name = save.artname[i];
				//strncpy(no_save.newtable[i].name, dummy_hint, char_table_size - 1);
			}


		}

	}
	else {
		for (int i = 0; i != NEW_ARTS_AMOUNT ; i++) {

			// 2017-12-12
			
			save.newtable[i].desc = save.artdesc[i];
			save.newtable[i].name = save.artname[i];
			

			//no_save.arteventtable[i] = no_save.arteventtable_txt[i];
		}
		//no_save.arteventtable[NEW_ARTS_AMOUNT] = no_save.arteventtable_txt[NEW_ARTS_AMOUNT];
	}

	*/
	first_time = false;
}


//// 2020-04-03
/*
void __stdcall EmeraldMove(PEvent e) {

	//void* oldtable = (void*) 0x00660B68;//0x007B6DA0; //0x693a58; //0xF3C0EF0;//0x693a58 ;
	void* newtable = (void*) no_save.newtable;// no_save.newtable;
	memcpy(newtable, (const void*) oldtable, sizeof(ART_RECORD)*OLD_ARTS_AMOUNT);


	//void* oldbtable = (void*) 0x007B8358;//0x63e758;
	void* newbtable = (void*) no_save.newbtable; // no_save.newbtable;
	memcpy(newbtable, (const void*) oldbtable, sizeof(ART_BONUS)*OLD_ARTS_AMOUNT);

	//EmeraldStrings(e);


}
*/


void __stdcall EmeraldUndo_old(PEvent e)	
{
	
	//int oldtable = 0x007B6DA0; //0x693a58; //0xF3C0EF0;//0x693a58 ;
	
	//should be off
	/*
	emerald->WriteDword(0x44CB32, oldtable);
	emerald->WriteDword(0x44CD1E, oldtable);
	emerald->WriteDword(0x44CD6C, oldtable);

	//
	emerald->WriteDword(0x44CCDF, oldtable + 0x1C);
	emerald->WriteDword(0x44CCFA, oldtable + 0x1D);
	emerald->WriteDword(0x716F8D, oldtable + 0x18);

	emerald->WriteDword(0x716F9E, oldtable + 0x18);
	emerald->WriteDword(0x716FAE, oldtable + 0x14);
	emerald->WriteDword(0x716FBF, oldtable + 0x14);

	emerald->WriteDword(0x717117, oldtable + 0x14);
	emerald->WriteDword(0x717146, oldtable + 0x18);
	emerald->WriteDword(0x754A42, oldtable); 

	emerald->WriteDword(0x717117, oldtable + 0x14);
	*/

	//6emerald->WriteDword(0x714ECA, OLD_ARTS_AMOUNT);
	//emerald->WriteDword(0x714F46, OLD_ARTS_AMOUNT);
	
	//emerald->WriteDword(0x716F7F, OLD_ARTS_AMOUNT);

	//emerald->WriteDword(0x717020, OLD_ARTS_AMOUNT);

	//emerald->WriteDword(0x7324BD, OLD_ARTS_AMOUNT); // UN:A Support
	//emerald->WriteDword(0x732849, OLD_ARTS_AMOUNT); // UN:A Support

	emerald->WriteDword(0x75120D, OLD_ARTS_AMOUNT); // WoG_Saver

	//emerald->WriteDword(0x4DC358, 0xA0); //MoP said

	/*

	//int oldbtable = 0x007B8358;//0x63e758;
	
	emerald->WriteDword(0x4E2D26, oldbtable);
	emerald->WriteDword(0x4E2DF1, oldbtable);
	emerald->WriteDword(0x4E2E95, oldbtable);
	emerald->WriteDword(0x4E2F7C, oldbtable); //??
	


	//is it needed?
	
	emerald->WriteDword(0x4E2D3D, oldbtable + 4 * 160);
	emerald->WriteDword(0x4E2DD7, oldbtable + 4 * 160);
	emerald->WriteDword(0x4E2EAC, oldbtable + 4 * 160);
	emerald->WriteDword(0x4E2F41, oldbtable + 4 * 160);
	
	//this would be better ??

	//int old_arteventtable = 0x007C8570;// 0x696A78;
	
	emerald->WriteDword(0x49F2E7, old_arteventtable +4 ); // were  + 4
	emerald->WriteDword(0x49F51E, old_arteventtable +4 ); // were  + 4
	emerald->WriteDword(0x49F5DA, old_arteventtable +4 ); // were  + 4
	
	emerald->WriteDword(0x49DD9A, old_arteventtable);
	
	*/
	
	// is it needed?
	//emerald->WriteDword(0x44CCA8, OLD_ARTS_AMOUNT * 4 + 8); //artraits.txt
	//emerald->WriteDword(0x44CACA, OLD_ARTS_AMOUNT * 4 + 8); //artraits.txt
	//emerald->WriteDword(0x49DD90, OLD_ARTS_AMOUNT * 4 + 0); //artevent.txt
	
}

void __stdcall EmeraldUndo(PEvent e){
	emerald->WriteDword(0x75120D, OLD_ARTS_AMOUNT); // WoG_Saver
	const int max_art = OLD_ARTS_AMOUNT;

	emerald->WriteDword(0x4C9248, max_art);
	emerald->WriteDword(0x4C91C2, max_art); //2020-04-08


	emerald->WriteDword(0x4C21B3, max_art * 0x20);
	emerald->WriteDword(0x4C2306, max_art * 0x20);


	emerald->WriteDword(0x4C21E0, max_art);
	emerald->WriteDword(0x4C2279, max_art);

	emerald->WriteDword(0x44D1AA, max_art);

}
void __stdcall EmeraldRedo(PEvent e) {
	emerald->WriteDword(0x75120D, NEW_ARTS_AMOUNT); // WoG_Saver
	const int max_art = NEW_ARTS_AMOUNT;

	emerald->WriteDword(0x4C9248, max_art);
	emerald->WriteDword(0x4C91C2, max_art); //2020-04-08


	emerald->WriteDword(0x4C21B3, max_art * 0x20);
	emerald->WriteDword(0x4C2306, max_art * 0x20);


	emerald->WriteDword(0x4C21E0, max_art);
	emerald->WriteDword(0x4C2279, max_art);

	emerald->WriteDword(0x44D1AA, max_art);
}

void __stdcall Emerald(PEvent e)	//main function
{

		//MessageBoxA(0, "Emerald::Emerald BUMP 01", "Emerald::Emerald BUMP", 0);
		static BOOL first_time = true;

		//DebugWindow();
		if (first_time) {
			//blank(0); // disabled 2017-12-10
		}


		/////2020-04-03
		/*
		//first_time = false;
		if (//!oldtable && 
			*(int*)0x660B68 != 0 &&
			*(int*)0x660B68 != (int)no_save.newtable) 
		{
				oldtable=			*(int*) 0x660B68;
				oldbtable=			*(int*) 0x4E2D26;
				old_arteventtable = *(int*) 0x49DD9A;
				EmeraldMove(e);
		}
		if (!(int)EmeraldArtNewTable) { DebugWindow();	return; }
		if (!oldtable) { DebugWindow();	return; } 
		*/

		// *(int*)0x660B68 = (int) EmeraldArtNewTable;
		// *(int*)0x4E2D26 = (int) EmeraldArtNewBTable;
		
		//pause();

		//MessageBoxA(0, "Emerald::Emerald BUMP 02", "Emerald::Emerald BUMP", 0);

		/*
		if (first_time)
			memcpy(no_save.newtable,(void*)*(int*)0x660B68,sizeof(ART_RECORD)*OLD_ARTS_AMOUNT);
		*/

		emerald->WriteDword(0x660B68,(int)EmeraldArtNewTable); //transfer of main table


		memcpy(EmeraldArtNewBTable, (void*)*(int*)0x4E2D26, sizeof(ART_BONUS) * OLD_ARTS_AMOUNT);
		emerald->WriteDword(0x4E2D26,(int)EmeraldArtNewBTable);

		emerald->WriteDword(0x7324BD,NEW_ARTS_AMOUNT); //UN:A
		
		//emerald->WriteDword(0x4DC358,0xA0); //MoP said
		emerald->WriteDword(0x4DC358, NEW_ARTS_AMOUNT); //majaczek tries

		//text writers
		emerald->WriteDword(0x44CB32,(int)EmeraldArtNewTable);
		emerald->WriteDword(0x44CD1E,(int)EmeraldArtNewTable);
		emerald->WriteDword(0x44CD6C,(int)EmeraldArtNewTable);


		//
		emerald->WriteDword(0x44CCDF,(int)EmeraldArtNewTable+0x1C);
		emerald->WriteDword(0x44CCFA,(int)EmeraldArtNewTable+0x1D);
		emerald->WriteDword(0x716F8D,(int)EmeraldArtNewTable+0x18);

		emerald->WriteDword(0x716F9E,(int)EmeraldArtNewTable+0x18);
		emerald->WriteDword(0x716FAE,(int)EmeraldArtNewTable+0x14);
		emerald->WriteDword(0x716FBF,(int)EmeraldArtNewTable+0x14);

		emerald->WriteDword(0x717117,(int)EmeraldArtNewTable+0x14);
		emerald->WriteDword(0x717146,(int)EmeraldArtNewTable+0x18);
		emerald->WriteDword(0x754A42,(int)EmeraldArtNewTable);

		emerald->WriteDword(0x717117,(int)EmeraldArtNewTable+0x14);
		
		//erm
		emerald->WriteDword(0x714ECA,NEW_ARTS_AMOUNT);
		emerald->WriteDword(0x714F46,NEW_ARTS_AMOUNT);
		emerald->WriteDword(0x716F7F,NEW_ARTS_AMOUNT);
		emerald->WriteDword(0x717020,NEW_ARTS_AMOUNT);
		emerald->WriteDword(0x7324BD,NEW_ARTS_AMOUNT);
		emerald->WriteDword(0x732849,NEW_ARTS_AMOUNT);

		emerald->WriteDword(0x75120D,NEW_ARTS_AMOUNT); //WoG_Saver
		emerald->WriteDword(0x751c5d,NEW_ARTS_AMOUNT); //WoG_Loader

		//bonuses
		//if(first_time) memcpy(no_save.newbtable,(void*)0x7B8358,4*OLD_ARTS_AMOUNT);
		
		emerald->WriteDword(0x4E2D26, (int)EmeraldArtNewBTable);
		emerald->WriteDword(0x4E2DF1, (int)EmeraldArtNewBTable);
		emerald->WriteDword(0x4E2E95, (int)EmeraldArtNewBTable);
	    emerald->WriteDword(0x4E2F7C, (int)EmeraldArtNewBTable);

	    emerald->WriteDword(0x4E2D3D, (int)EmeraldArtNewBTable + 4 * 160);
	    emerald->WriteDword(0x4E2DD7, (int)EmeraldArtNewBTable + 4 * 160);
	    emerald->WriteDword(0x4E2EAC, (int)EmeraldArtNewBTable + 4 * 160);
	    emerald->WriteDword(0x4E2F41, (int)EmeraldArtNewBTable + 4 * 160);

		//if (first_time)
			//no_save.newbtable[ARTIFACT_CRIMSON_SHLD].def = +2; //восстанавливаем "щит возмездия", будь он неладен
	
		//emerald->WriteDataPatch(0x4e2eb3,"4D F4 E8 E6 17");
		//emerald->WriteDataPatch(0x4E2D43,"8B 4D F4 E8 55");
		

			/*
		
			for (int i = -1; i != OLD_ARTS_AMOUNT; i++) {
				no_save.arteventtable[i + 1] = no_save.arteventtable_txt[i + 1];

				if (first_time) {
					
				}
			}

			*/
			//EmeraldStrings(e);

			//MessageBoxA(0, "Emerald::Emerald BUMP 03", "Emerald::Emerald BUMP", 0);
		
		
		//texts on the map

		//MessageBoxA(0, "Emerald::Emerald BUMP 04", "Emerald::Emerald BUMP", 0);

		
	    emerald->WriteDword(0x49F2E7, (int)no_save.arteventtable +4); //were +4
	    emerald->WriteDword(0x49F51E, (int)no_save.arteventtable +4); //were +4
	    emerald->WriteDword(0x49F5DA, (int)no_save.arteventtable +4); //were +4

	    emerald->WriteDword(0x49DD9A, (int)no_save.arteventtable);

	    emerald->WriteDword(0x44CCA8, NEW_ARTS_AMOUNT *4 +8); //artraits.txt
	    emerald->WriteDword(0x44CACA, NEW_ARTS_AMOUNT *4 +8); //artraits.txt
	    emerald->WriteDword(0x49DD90, NEW_ARTS_AMOUNT *4 +0); //artevent.txt


		//table of spells given by artifacts

		//MessageBoxA(0, "Emerald::Emerald BUMP 05", "Emerald::Emerald BUMP", 0);

		if ( first_time ) {
			memset(no_save.artspelltable, 8, NEW_ARTS_AMOUNT);
			memcpy(no_save.artspelltable + 86, (void*)0x4D9800, 136 - 86);
		}

		emerald->WriteByte(0x4D95DC,0x06);
		emerald->WriteDword(0x4D95DD,0x90909090);
		emerald->WriteDword(0x4D95EB,(int)no_save.artspelltable);


		//MessageBoxA(0, "Emerald::Emerald BUMP 06", "Emerald::Emerald BUMP", 0);

		if (first_time) {
			memset(no_save.new_cases, 0x90, 22 * 128);
			for (unsigned char i = 0; i != 128; i++)
			{
				memcpy(no_save.new_cases + i * 22, no_save._magic, 22);
				no_save.new_cases[i * 22 + 3] = i;
				no_save.artspellswitch[i + 0x80] = i * 22 + (int)(no_save.new_cases);
			}
			memcpy((void*)no_save.artspellswitch, (void*)0x4D97DC, 4 * 9);
			no_save.artspellswitch[9]  = (int)(void*)SpellSet_LV1;
			no_save.artspellswitch[10] = (int)(void*)SpellSet_LV2;
			no_save.artspellswitch[11] = (int)(void*)SpellSet_LV3;
			no_save.artspellswitch[12] = (int)(void*)SpellSet_LV4;
			no_save.artspellswitch[13] = (int)(void*)SpellSet_ALL;
			no_save.artspellswitch[14] = (int)(void*)SpellSet_EYE;
			no_save.artspellswitch[15] = (int)(void*)SpellSet_ADV;
			no_save.artspellswitch[16] = (int)(void*)SpellSet_TP;
			no_save.artspellswitch[17] = (int)(void*)SpellSet_4EL;
		}

		emerald->WriteDword(0x4D95F2,(int)no_save.artspellswitch);

		emerald->WriteDword(0x44CCE7,(int)no_save.enchanted_artifacts);
		//emerald->WriteDword(0x44CCF4,(int)enchanted_artifacts+sizeof(enchanted_artifacts));
		emerald->WriteDword(0x44CCF4, (int)no_save.enchanted_artifacts + no_save.enchanted_artifacts_count * sizeof(int) );

		//MessageBoxA(0, "Emerald::Emerald BUMP 07", "Emerald::Emerald BUMP", 0);


		if (first_time ) {
			//new types of artifacts
			/* Disabled by Archer 15 Feb 2024
			emerald->WriteLoHook(0x44CC86, (void*)ArtTypesHook);

			//splice for limited copying of artifact functions
			emerald->WriteHiHook(0x4D9460, SPLICE_, EXTENDED_, THISCALL_, (void*)NewHasArtifact);
			emerald->WriteHiHook(0x4D9420, SPLICE_, EXTENDED_, THISCALL_, (void*)NewHasArtifactInBP);
			*/

			//luck
			emerald->WriteLoHook(0x4DCDA6, (void*)LuckTextHook);
			emerald->WriteLoHook(0x4E3A46, (void*)LuckValueHook);

			/* Disabled by Archer 14 Feb 2024
			//morality
			emerald->WriteLoHook(0x4DC606, (void*)MoraleTextHook);
			emerald->WriteLoHook(0x4E3C9E, (void*)MoraleValueHook);

			//resists
			emerald->WriteHiHook(0x44A1A0, SPLICE_, EXTENDED_, FASTCALL_, (void*)ResistanceHook);
			*/

			//start of the battle (right before Angelic Alliance casts)
			emerald->WriteLoHook(0x464FBA, (void*)BattleStartHook);

			emerald->WriteHiHook(0x4E6390, SPLICE_, EXTENDED_, THISCALL_, (void*)OnCreatureParamInit);

		}
	//crutches for the god of crutches!

		//MessageBoxA(0, "Emerald::Emerald BUMP 08", "Emerald::Emerald BUMP", 0);

		if ( first_time ) {
			
			/* Disabled by Archer 13 Feb 2024
			ExecErmCmd = (void(__stdcall *)(char*))GetProcAddress(LoadLibraryA("era.dll"), "ExecErmCmd");
			RegisterHandler = (TRegisterHandler)GetProcAddress(LoadLibraryA("era.dll"), "RegisterHandler");

			RegisterHandler(OnEquip, "OnEquipArt");
			RegisterHandler(OnUnequip, "OnUnequipArt");
			//RegisterHandler(OnBattleStart, "OnSetupBattlefield");//
			RegisterHandler(OnBattleEnd, "OnAfterBattleUniversal");
			RegisterHandler(OnNewDay, "OnGlobalTimer"); 
			*/

			//emerald->WriteHiHook(0x5A7BF0, SPLICE_, EXTENDED_, FASTCALL_, (void*)MagicDamageHook);

			//loading from configs
		}

		//MessageBoxA(0, "Emerald::Emerald BUMP 09", "Emerald::Emerald BUMP", 0);

	
	//crutches for the god of crutches!

		
		int *p_Z_name_0x00A4A588_new = &no_save.ArtNames[0].DescVar;// save.ERM_Z_name;
		for (int i = 0;i < sizeof(p_Z_name_0x00A4A588_table) / 4; ++i)
			emerald->WriteDword(p_Z_name_0x00A4A588_table[i],
				(int)p_Z_name_0x00A4A588_new);
		

		int *p_Z_name_0x00A4A58C_new = &no_save.ArtNames[0].NameVar;//save.ERM_Z_name + 1;
		for (int i = 0;i<sizeof(p_Z_name_0x00A4A58C_table) / 4; ++i)
			emerald->WriteDword(p_Z_name_0x00A4A58C_table[i],
				(int)p_Z_name_0x00A4A58C_new);
		

		emerald->WriteDword(0x007326fa + 2, (int)&no_save.ArtSetUpBack[0].name); // UN:A
		emerald->WriteDword(0x00732793 + 2, (int)&no_save.ArtSetUpBack[0].desc); // UN:A


		emerald->WriteDword(0x00751e3e + 2, (int)&no_save.ArtSetUpBack[0].name); // Loader
		emerald->WriteDword(0x00751eab + 2, (int)&no_save.ArtSetUpBack[0].desc); // Loader

		emerald->WriteDword(0x00752d97 + 2, (int)no_save.ArtSetUpBack);
		emerald->WriteDword(0x00752dd1 + 2, (int)no_save.ArtSetUpBack);

		emerald->WriteDword(0x00752d80 + 3, NEW_ARTS_AMOUNT * 32); //memcpy
		emerald->WriteDword(0x00752dbd + 3, NEW_ARTS_AMOUNT * 32); //memcpy

		//MessageBoxA(0, "Emerald::Emerald BUMP 10", "Emerald::Emerald BUMP", 0);

		//EmeraldStrings2(e);

		first_time = false;
		//pause();
		//EnableCombos();

		/*
		// fix getartbase and getartname wog functions
		emerald->WriteDword(0x0071498E, (int) EmeraldArtBase);
		emerald->WriteDword(0x00714FA8, (int) EmeraldArtBase);
		*/

		//MessageBoxA(0, "Emerald::Emerald Finish", "Emerald::Emerald Finish", 0);
}


