#pragma once
#include"..\__include\heroes.h"

typedef ART_RECORD _ArtSetUp_;

#define OLD_ARTS_AMOUNT	171
#define NON_BLANK_ARTS_AMOUNT	161
#define NEW_ARTS_AMOUNT 300 // Changed by Archer 14 Feb 2024 from 1000
#define STORED_ARTS_AMOUNT 1024
#define char_table_size 512
#define int_tuple_size 256

#define SPELLS_AMOUNT	128 //зачем жалеть память?



struct replace_byte {
	unsigned int address;
	unsigned char new_byte;
};

struct replace_dword {
	unsigned int address;
	unsigned int new_dword;
};

struct GAMEDATA
{
	char header[64];
	char    used_artifacts[STORED_ARTS_AMOUNT];// 0x4E224
	char allowed_artifacts[STORED_ARTS_AMOUNT];// 0x4E2B4
	//char marker_1[STORED_ARTS_AMOUNT]; //2020-04-09


	//char unknown_art1     [STORED_ARTS_AMOUNT];// 0x4E344

	//char artname[STORED_ARTS_AMOUNT][char_table_size];
	//char artdesc[STORED_ARTS_AMOUNT][char_table_size];
	//int ERM_Z_name[(STORED_ARTS_AMOUNT + 2) * 2];


	/* extern */ //  ART_RECORD newtable[STORED_ARTS_AMOUNT];
	/* extern */ //  ART_BONUS newbtable[STORED_ARTS_AMOUNT];

	char footer[64]; // = "here is emerald.";

};

struct GAMEDATA2
{
	char header[64];
	// #include "Properties.h"

	/* extern */  ART_RECORD newtable[STORED_ARTS_AMOUNT];
	/* extern */  ART_BONUS newbtable[STORED_ARTS_AMOUNT];


	//extern char* arteventtable[STORED_ARTS_AMOUNT+1]; 
	/* extern */  char* arteventtable[STORED_ARTS_AMOUNT /* + 1 */]/*[char_table_size]*/;
	/* extern */ // char  arteventtable_txt[STORED_ARTS_AMOUNT + 1][char_table_size];

	/* extern */  char  artspelltable[STORED_ARTS_AMOUNT];
	//New tables

	// char* artNameTable[STORED_ARTS_AMOUNT];
	// char* artDescTable[STORED_ARTS_AMOUNT];

	//char artname[STORED_ARTS_AMOUNT][char_table_size];
	//char artdesc[STORED_ARTS_AMOUNT][char_table_size];

	char artNameTable[STORED_ARTS_AMOUNT][char_table_size];
	char artDescTable[STORED_ARTS_AMOUNT][char_table_size];

	_ArtSetUp_ ArtSetUpBack[STORED_ARTS_AMOUNT];

	struct _ArtNames_ {
		int NameVar;  
		int DescVar;
	} ArtNames[STORED_ARTS_AMOUNT];

	/* extern */  int luck_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int morale_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int luck_bonuses_bp[STORED_ARTS_AMOUNT];
	/* extern */  int morale_bonuses_bp[STORED_ARTS_AMOUNT];

	/* extern */  int enemy_luck_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int enemy_morale_bonuses[STORED_ARTS_AMOUNT];


	/* extern */  int allow_fly[STORED_ARTS_AMOUNT];
	/* extern */  int allow_water[STORED_ARTS_AMOUNT];

	/* extern */  int spell_immunity[STORED_ARTS_AMOUNT][SPELLS_AMOUNT];

	/* extern */  int autocast[STORED_ARTS_AMOUNT][9];

	/* extern */  int autosummon[STORED_ARTS_AMOUNT][9];
	/* extern */  int autosummon_power[STORED_ARTS_AMOUNT][9];

	/* extern */  int regenerate_spellpoints[STORED_ARTS_AMOUNT];

	/* extern */  int upgrade_from[STORED_ARTS_AMOUNT][9];
	/* extern */  int upgrade_to[STORED_ARTS_AMOUNT][9];

	/* extern */  int crattack_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int crdefence_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int dmgmin_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int dmgmax_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int speed_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int hp_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int shots_bonuses[STORED_ARTS_AMOUNT];
	/* extern */  int casts_bonuses[STORED_ARTS_AMOUNT];

	//bonuses


	//events
	/* extern */  char erm_on_ae0[STORED_ARTS_AMOUNT][char_table_size];
	/* extern */  char erm_on_ae1[STORED_ARTS_AMOUNT][char_table_size];

	/* extern */  char erm_on_ba52[STORED_ARTS_AMOUNT][char_table_size];
	/* extern */  char erm_on_ba53[STORED_ARTS_AMOUNT][char_table_size];
	/* extern */  char erm_on_timer[STORED_ARTS_AMOUNT][char_table_size];

	/* extern */  char erm_on_creature_param_init[STORED_ARTS_AMOUNT][char_table_size];
	/* extern */  char erm_on_battlestart[STORED_ARTS_AMOUNT][char_table_size];

	/*
	int enchanted_artifacts[STORED_ARTS_AMOUNT];
	int enchanted_artifacts_count;
	*/


	int artspellswitch[256];      //новый свитч для этой таблицы
	unsigned char _magic[22]/* = { 0x6A,0x01,0x6A,0x09,
		0x8D,0x4D,0xE4,0xB8,
		0xA0,0x67,0x4E,0x00,
		0xFF,0xD0,0xB8,0x9D,
		0x97,0x4D,0x00,0xFF,
		0xE0,0x90 }*/; //машкод кейса, ответственного за добавление заклинания артефакту.
	char new_cases[22 * 128];  //буфер для новых кейсов, дающих единичные заклинания


	int enchanted_artifacts_count = 9;
	
	int enchanted_artifacts[STORED_ARTS_AMOUNT*4]; 
	/*
	{ 0x01,0x80,0x7B,0x7C,
		0x56,0x57,0x58,0x59,
		0x87 };	//список артефактов, дающих заклинания. 
				//Для добавления - дописываем свой арт в конец списка 
				//и задаем ему заклинание через artspelltable
	*/

	char footer[64];
};

