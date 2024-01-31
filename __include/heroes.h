#pragma once
#ifndef HEROES_H
#define HEROES_H
//#include "heroes.cpp"

#pragma pack (push, 1)
#define DWORD int
#define WORD short
#define BYTE char

#define _DWORD DWORD

#define Word WORD
#define Byte BYTE
#define Dword DWORD



//���������
typedef struct
{
   char *name;
   int cost;
   int slot;
   int rank;
   char *desc;
   int partof;
   int combonum;
   char disable;
   char spellflag;
   char _unk;
   char _unkk;
} ART_RECORD;

typedef struct
{
   char att;
   char def;
   char spp;
   char knw;
}ART_BONUS;

/*
typedef struct
{
	char dummy[0x492];
}HERO;
*/
// ����������� ������ ������ �� ���������
struct _Mes_{
  char *s;
  long  l;  
};

// ����������� ������ ���������� ������ �� ���������
struct _AMes_{
  _Mes_ m;
  long  a;
};


typedef struct
{
	int town;
	int level;
	char* soundname; // 4 �����, � ������� ���������� ����� �������
	char* defname;
	int flags;
	char* name;
	char* pluralname; 
	char* features; // (�������� ������������)
	int cost_wood;
	int cost_mercury;
	int cost_ore;
	int cost_sulfur;
	int cost_crystal;
	int cost_gems;
	int cost_gold;
	int fight_value;
	int ai_value;
	int growth;
	int horde_growth;
	int hp;
	int speed;
	int attack;
	int defence;
	int damage_low;
	int damage_high;
	int shots;
	int spells;
	int adv_low;  // ?
	int adv_high; // ?
}MONSTER_PROP;


typedef struct
{
    WORD w_anim1;
    WORD w_anim2;
    WORD w_anim3;
    WORD w_anim4;
    WORD w_anim5;
    WORD w_anim6;
    float f_anim7;
    float f_anim8;
    float f_anim9;
    float f_anim10;
    float f_anim11;
    float f_anim12;
    float f_anim13;
    float f_anim14;
    float f_anim15;
    float f_anim16;
    float f_anim17;
    float f_anim18;
    int i_anim19;
    int i_anim20;
    int i_anim21;
    int i_anim22;
    int i_anim23;
    int i_anim24;
    
}CRANIM;


typedef struct{
  Word   x;        //   +00  dw    = x position
  Word   y;        //   +02  dw    = y position
  Word   l;        //   +04  dw    = ? ������� ������� ����� y (y<<2>>C)
  Byte   Visible;  //   +06  db    = 1 - ���� �� ����� (������ ������ ��� �� �������)
//  Byte  _u1[17];
// +07 db - x
// +08 db - (?) ����� (� x)
// +09 db - y
// +0A db - l(?) ����� (� y)
    Dword  PlMapItem; // MixedPos
// +0B db - (?) l
    Byte  _u1;
// +0C dd - ��� ������� �� ������� ����� �����
    long   PlOType; // dd +1E � �����
// +10 db - ��� ��������� �� ������ ����������� 00001000
// ��� ��� ����������, ��� ����� ����/���� ����� ����� (������ ������)
    Dword  Pl0Cflag;
// +14 dd - SetUp � �����
    Dword  PlSetUp; // dd +0 � �����
  Word   SpPoints; //   +18  dw    = ����� ����������
  int    Number;   //   +1A  dd    = ����� ������� (���������� �����)
  Dword  Id;       //   +1E  dd    = Id
  char   Owner;    //   +22  db    = ������ (����)
  char   Name[13]; //*   +23  db*D  = ���,0
  long   Spec;     //   +30  dd    = str[8] str=(*[67CD08])[����� ������� *5C]
  Byte   Pic;      //*   +34  db    = ����� ��������
// dw +35 ???
// dw +41 ???
// db +43 0
  Byte  _u2[15];
    // +3E db -??? 4E3BB5 - used in luck calculation
  Byte   x0;       //   +44  db    = ������� x ��� �������� (FF-�� ���������)
  Byte   y0;       //   +45  db    = ������� y ��� �������� (FF-�� ���������)
  Byte   Run;      //   +46  db    = ������ �������� (FF-�� ���������)
  Byte  _u3;       //   +47  db    = ??? 
  Byte   Flags;    //   +48  8*bb  (463253)
    // 01 - ��� ����������� ������
    // 02 - ��������� ������� ��� �����
  int    Movement0;//    +49  dd    = ������ ����������� ���������
  int    Movement; //*   +4D  dd    = ���������� �����������
  Dword  Exp;      //*   +51  dd    = ����
  Word   ExpLevel; //*   +55  dw    = �������
//  Dword  VStones;  // +57 32 ����� (1-�������,2-���)
//  Dword  VMTower;  // +5B ����� ��������
//  Dword  VGarden;  // +5F ��� ����������
//  Dword  VMCamp;   // +63 ������ ���������
//  Dword  VSAxis;   // +67 �������� ������
//  Dword  VKTree;   // +6B ������ ������
//  Dword  VUniver;  // +6F �����������
//  Dword  VArena;   // +73 �����
//  Dword  VSMagic;  // +77 ����� �����
//  Dword  VSWar;    // +7B ����� �����
  Dword  Visited[10];
  Byte  _u4[18];   // +7F
  int    Ct[7];    //   +91  dd*7  = ��� ������� (-1 - ���)
  int    Cn[7];    //   +AD  dd*7  = ����������
  Byte   SSkill[28];
	//   +C9  db*1C = ������� 2-� ������ (���� ���� - ������� ����� ������ ����� 1,2,3) 0-���
    // C9=Pathfinding CA=Archery CB=Logistics CC=Scouting CD=Diplomacy CE=Navigation CF=Leadership 
    // D0=Wisdom D1=Mysticism D2=Luck D3=Ballistics D4=Eagle Eye D5=Necromancy D6=Estates D7=Fire Magic 
    // D8=Air Magic D9=Water Magic DA=Earth Magic DB=Scholar DC=Tactics DD=Artillery DE=Learning DF=Offence 
    // E0=Armorer E1=Intelligence E2=Sorcery E3=Resistance E4=First Aid 
  Byte   SShow[28]; //   +E5  db*1C = ������� ����������� 2-� ������ � ���� ����� (1,2,3,4,5,6)
  Dword  SSNum;    //   +101 dd    = ���������� 2-� ������
//  Word  RefData1;  //   +105  4814D3+...
//  Word  RefData2;  //   +107  4DA466
  Dword  TempMod;    // +105 ��������� ������������
// ���. ����. ��� ����� 0xFFF9FFFF
//  00000002 = ������� 3.59 ERM
//  00000008 = ��������� ����� swan pond 3.59 ERM
//  00000020 = (???) ������ ����� fountain of fortune 3.59 ERM
//  00000080 = �����
//  00002000 = ����� ���
//  00040000 = � ����� �� ����
//  00200000 = -3morale � ������ ����
//  00400000 = Give Maximum Luck
//  00800000 = Give Maximum Moral
//  38000000 = ���������� ��� ������� �����
  Byte  _u6[9];   // +109
  Dword _u7;      // +112 
  char   DMorale;  // +116 ������������ ������ (�������������)
  Byte  _u60[3];
  char   DMorale1; // +11A ����� ������ (�����)
  char   DLuck;    // +11B ����� ����� �� ���� �����
  Byte  _u6a[17];
  int   IArt[19][2];  //+12D dd*2*13h = ��������� dd-�����,dd-(FF) (����� 3,FF)
  Byte  FreeAddSlots;   //+1C5 ���������� ������ ���. ������ �����
  char  LockedSlot[14]; //+1C6
  int   OArt[64][2];  //+1D4 dd*2*40 = ��� � ������� dd-�����, dd-(FF)
  Byte    OANum;   //   +3D4 db   = ����� ���������� � �������
  Dword  Sex;      //   +3D5 dd    = ���
  Byte   fl_B;     //   +3D9 db    = ���� ���������
//  char  *Bibl;     //   +3DA dd    -> ���������
//  Byte  _u7[12];    //  +3DE
    Dword  _5b;     // +3DA
    _AMes_ Bibl;    // +3DE
  Byte   Spell[70]; //   +3EA db*46 = ���������� (����/���)
  Byte   LSpell[70];//   +430 db*46 = ������� ���������� (>=1)
  char   PSkill[4]; //   +476 db*4  = ��������� ������
  Byte  _u8[24];
}HERO;

typedef struct {
  Byte   Number;        //* +0 0,1,2,...
  char   Owner;         //*O +1 0,...
  char   BuiltThisTurn; // +2 - ��� ������� � ���� ���� (0-���, 1-��, 2-�� ��� �����)
  Byte  _u2;            //* +3 0
  Byte   Type;          //*T +4 0,1...,8
  Byte   x;             //* +5
  Byte   y;             //* +6
  Byte   l;             //* +7
  Byte   Pos2PlaceBoatX;//* +8 �������� ����� ��� ������� � Shipyard
  Byte   Pos2PlaceBoatY;//* +9
  Byte  _uAa[2];        // +0A
  int    IHero;         //* +0Ch = ����� ����� ������ ������ (-1 - ������ ���)
  int    VHero;         //* +10h = ����� ����� ������� ������ (-1 - ������ ���)
  char   MagLevel;      //*G +14h = ������� ���������� ������� � ������ (���. AI ��� ���������)
  Byte  _u15;
  Word   Monsters[2][7];//*M- +16h ��-��� ������� � ������������
  char  _u32;           //*- +32 = ?
  char  _u33;           //* +33 = 1
  char  _u34;           //* +34 = 0
  Byte  _u35a[3];
  int   _u38;           //* +38 = -1
  int   EightMonsterType;           //* +3C = -1
  short EightMonsterAmount;           //*- +40
  Word  _u42;           //  +42
  int    Spels[5][6];   //*G- +44 ���� ����������
  char   MagicHild[5];  //*G- +BCh = ����� ���������� � ������ �������
  Byte  _uC1[3];
  char  _uC4;           //* +C4 = 0
  Byte  _uC5[3];
  _AMes_ Name;          //*N +C8 -> ��� ������
  int   _u8[3];         //* +D4 = 0
  Dword  GuardsT[7];    //*M +E0 = ������ �����
  Dword  GuardsN[7];    //*M +FC = ���-�� ������
  Dword  GuardsT0[7];   //*M- +118 = ������ �����
  Dword  GuardsN0[7];   //*M- +134 = ���-�� ������
  Byte   Built[8];      //*B +150h = ��� ����������� ������ (0400)
  Byte   Bonus[8];      //*B +158h = ����� �� �������, ������� � �.�., ��������� ����������
  Dword  BMask[2];      //*B- +160h = ����� ��������� ��� �������� ��������
}CASTLE;


#pragma pack (pop)

//���������
#define CREATURE_CHAMPION		11


#define CREATURE_GOG			44
#define CREATURE_MAGOG			45

#define CREATURE_EFREET			52
#define CREATURE_EFREET_SULTAN	53

#define CREATURE_LICH			64
#define CREATURE_POWERLICH		65

#define CREATURE_AIR_ELEM		112
#define CREATURE_EARTH_ELEM		113
#define CREATURE_FIRE_ELEM		114
#define CREATURE_WATER_ELEM		115

#define CREATURE_GOLD_GOLEM		116
#define CREATURE_DIAM_GOLEM		117

#define CREATURE_ICE_ELEM		123
#define CREATURE_MAGMA_ELEM		125
#define CREATURE_STORM_ELEM		127
#define CREATURE_ENERGY_ELEM	129

#define CREATURE_FIREBIRD		130
#define CREATURE_PHOENIX		131

#define CREATURE_DRACOLICH		196

#define CREATURE_PALADIN		197
#define CREATURE_DRAGSLAYER		198
#define CREATURE_SORCR			199
#define CREATURE_ALCHEMIST		200
#define CREATURE_NECROMANCER	201
#define CREATURE_BONESNIPER		202
#define CREATURE_BONEGOLEM		203
#define CREATURE_DARKELF		204
#define CREATURE_THUNDMECH		205
#define CREATURE_FURY			206
#define CREATURE_MERCENARY		207
#define CREATURE_SHAMAN			208
#define CREATURE_WISP			209


#define SPELL_SANDS				10
#define SPELL_MINEFIELD			11
#define SPELL_FORCEFIELD		12
#define SPELL_FIREWALL			13
#define SPELL_EARTHQUAKE		14
#define SPELL_MAGICARROW		15
#define SPELL_ICEBOLT			16
#define SPELL_LIGHTBOLT			17
#define SPELL_IMPLOSION			18
#define SPELL_CHAINLIGHT		19
#define SPELL_ICECIRCLE			20
#define SPELL_FIREBALL			21
#define SPELL_INFERNO			22
#define SPELL_METEORSHOWER		23
#define SPELL_DEATHWAVE			24
#define SPELL_DESTROYUNDEAD		25
#define SPELL_ARMAGEDDON		26
#define SPELL_SHIELD			27
#define SPELL_AIRSHIELD			28
#define SPELL_FIRESHIELD		29
#define SPELL_PROTAIR			30
#define SPELL_PROTFIRE			31
#define SPELL_PROTWATER			32
#define SPELL_PROTEARTH			33
#define SPELL_ANTIMAGIC			34
#define SPELL_DISPEL			35
#define SPELL_MAGICMIRROR		36
#define SPELL_CURE				37
#define SPELL_RESSURRECT		38
#define SPELL_ANIMATEDEAD		39
#define SPELL_SACRIFICE			40
#define SPELL_BLESS				41
#define SPELL_CURSE				42
#define SPELL_BLOODLUST			43
#define SPELL_PRECISION			44
#define SPELL_WEAKNESS			45
#define SPELL_STONESKIN			46
#define SPELL_DISRUPT			47
#define SPELL_PRAYER			48
#define SPELL_MIRTH				49
#define SPELL_SORROW			50
#define SPELL_FORTUNE			51
#define SPELL_MISFORTUNE		52
#define SPELL_HASTE				53
#define SPELL_SLOW				54
#define SPELL_SLAYER			55
#define SPELL_FRENZY			56
#define SPELL_TITANTHUNDER		57
#define SPELL_CS				58
#define SPELL_BERSERK			59
#define SPELL_HYPNOTIZE			60
#define SPELL_FORGET			61
#define SPELL_BLIND				62
#define SPELL_TELEPORT			63
#define SPELL_REMOBSTACLE		64
#define SPELL_CLONE				65
#define SPELL_SUMMONFIRE		66
#define SPELL_SUMMONEARTH		67
#define SPELL_SUMMONWATER		68
#define SPELL_SUMMONAIR			69

#define SPELL_STONE				70
#define SPELL_POISON			71
#define SPELL_ROOTS				72
#define SPELL_DECAY				73
#define SPELL_PARALIZE			74
#define SPELL_AGE				75
#define SPELL_DEATHCLOUD		76	
#define SPELL_THUNERBOLT		77
#define SPELL_DISPELBEN			78
#define SPELL_DEATHSTARE		79
#define SPELL_ACIDBREATH		80


		//ToE constants.
#define ARTIFACT_SPELLBOOK		0
#define ARTIFACT_ANGELWINGS		72
#define ARTIFACT_WATERBOOTS		90

#define ARTIFACT_ANG_ALLIANCE	129 
#define ARTIFACT_ARMOR_DAMNED	132 

#define ARTIFACT_CRIMSON_SHLD	157 



#define ARTIFACT_INQ_HAMMER		171 
#define ARTIFACT_INQ_SHIELD		172 
#define ARTIFACT_INQ_HELMET		173 
#define ARTIFACT_INQ_ARMOR 		174 

#define ARTIFACT_BARD_HARP		175

#define ARTIFACT_AMMO_BOX		176

#define ARTIFACT_SLAYER_SWING	177

#define ARTIFACT_ELEM_FUSION	178
#define ARTIFACT_ELEM_CONJUR	-1



#define ARTIFACT_FIZBIN_MISFORT	179
#define ARTIFACT_CURSD_HRSESHOE	180
#define ARTIFACT_HOLY_LANTERN	181
#define ARTIFACT_FAIRY_ABSENT	182 // :)

#define ARTIFACT_SEAMAN_LOGBOOK	183
#define ARTIFACT_RUNE_AMULET	184

#define ARTIFACT_CUBE_OF_NEGAT	185

#define ARTIFACT_ROGUE_CLOAK	186
#define ARTIFACT_ROGUE_RING		187

#define ARTIFACT_WANDOFFIRE		188

#define ARTIFACT_DAGGER1		190
#define ARTIFACT_DAGGER2		191
#define ARTIFACT_DAGGER3		192
#define ARTIFACT_HOLYDAGGER		193

#define ARTIFACT_MEMORYCRYSTALA	196
#define ARTIFACT_MEMORYCRYSTALB	197
#define ARTIFACT_MEMORYCRYSTALC	198
#define ARTIFACT_MEMORYCRYSTALD	199

#define ARTIFACT_WETSUIT		200
#define ARTIFACT_BLASTER		201


//==========WriteHook=============
#define OPCODE_JUMP 0xE9
#define OPCODE_CALL 0xE8
#define OPCODE_NOP 0x90

#define HOOKTYPE_JUMP 0
#define HOOKTYPE_CALL 1

#define HOOK_SIZE 5


//����������
/*
#define CONST_advManager	(void*)(*(int*)0x6992B8)

#define CONST_storedGame	(void*)(*(int*)0x699538)

#define CONST_level	(int)(storedGame + 0x1F6B0)
#define CONST_x		(int)(storedGame + 0x1F6B8)
#define CONST_y		(int)(storedGame + 0x1F6C0)*/
/*
#define grail_cnt
*/

//�������
extern int (__thiscall *HasArtifact)(void *hero, int art);
		//�������� �� ������� ���������

extern int (__thiscall *HasArtifactInBackpack)(void *hero, int art);

extern int (__thiscall *HasCreature)(void *hero, int creature);
		//�������� �� ������� ��������

extern int(__thiscall *ShowGrailMap)(void *advManager);
		//�������� ��������� �����

extern int(__thiscall *ShowThiefGuild)(void *_this, int amount);

extern int(__thiscall *RandArtGenerator)(int _this, int _class);

extern char(__thiscall *sub_5A43E0)(void* combatManager, int a2, int a3, int a4, int a5, int a6);
	
extern int (__thiscall *CastBattleSpell)(void* combatManager, int spell, signed int target, unsigned int source, int a5, int mastery, int spellpower);
		//���� ������ � ���

extern int (__thiscall *SummonCreature)(void *combat_manager, int spell, int creature, int spellpower, int unk);
      //����� �������� �������

extern int (__fastcall *ShowMSG)(const char *text, int type, int f1, int f2, int f3, int f4, int f5, int f6, int f7, int f8, int f9, int f10);

extern void (__cdecl *CallERM)(int num);

extern void (_cdecl  *hprintf)(int, char*, ...);

//�����������
extern void* HeroStructPointer(char hero);

extern int* BattleStackParam(int stack, int param_offset);

extern ART_RECORD* GetArtifactRecord(int number);

extern MONSTER_PROP* GetMonsterRecord(int number);

extern char* GetHeroRecord(int number);

extern void WriteHook( void *pOriginal, void *pNew, char type );

#endif