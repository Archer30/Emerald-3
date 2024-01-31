//»м€: Era
//јвтор: Berserker
//ќписание: Ёкспортируемые типы, пол€ и функции Ёры.

#ifndef _ERA_DEFINED_
#define _ERA_DEFINED_

#pragma once

#define bool BOOL

//#include <windows.h>
#define NOALIGN __declspec(align(1))

/* Hooks */
// jmp, 5 bytes
#define HOOKTYPE_JUMP   0
// call, 5 bytes
#define HOOKTYPE_CALL   1
/*
Opcode: call, 5 bytes.
Automatically creates safe bridge to high-level function "F".
STDCALL LONGBOOL F (PHookHandlerArgs Context); Returns "Execute default code" flag.
If default code should be executed, it can contain any commands except jumps.
*/
#define HOOKTYPE_BRIDGE 2

#define OPCODE_JUMP   0xE9
#define OPCODE_CALL   0xE8
#define OPCODE_RET    0xC3

#define EXEC_DEF_CODE       0xFFFFFFFF
#define DONT_EXEC_DEF_CODE  0x00000000

/* Erm triggers */
#define TRIGGER_FU1       0
#define TRIGGER_FU30000   29999
#define TRIGGER_TM1       30000
#define TRIGGER_TM100     30099
#define TRIGGER_HE0       30100
#define TRIGGER_HE198     30298
#define TRIGGER_BA0       30300
#define TRIGGER_BA1       30301
#define TRIGGER_BR        30302
#define TRIGGER_BG0       30303
#define TRIGGER_BG1       30304
#define TRIGGER_MW0       30305
#define TRIGGER_MW1       30306
#define TRIGGER_MR0       30307
#define TRIGGER_MR1       30308
#define TRIGGER_MR2       30309
#define TRIGGER_CM0       30310
#define TRIGGER_CM1       30311
#define TRIGGER_CM2       30312
#define TRIGGER_CM3       30313
#define TRIGGER_CM4       30314
#define TRIGGER_AE0       30315
#define TRIGGER_AE1       30316
#define TRIGGER_MM0       30317
#define TRIGGER_MM1       30318
#define TRIGGER_CM5       30319
#define TRIGGER_MP        30320
#define TRIGGER_SN        30321
#define TRIGGER_MG0       30322
#define TRIGGER_MG1       30323
#define TRIGGER_TH0       30324
#define TRIGGER_TH1       30325
#define TRIGGER_IP0       30330
#define TRIGGER_IP1       30331
#define TRIGGER_IP2       30332
#define TRIGGER_IP3       30333
#define TRIGGER_CO0       30340
#define TRIGGER_CO1       30341
#define TRIGGER_CO2       30342
#define TRIGGER_CO3       30343
#define TRIGGER_BA50      30350
#define TRIGGER_BA51      30351
#define TRIGGER_BA52      30352
#define TRIGGER_BA53      30353
#define TRIGGER_GM0       30360
#define TRIGGER_GM1       30361
#define TRIGGER_PI        30370
#define TRIGGER_DL        30371
#define TRIGGER_HM        30400
#define TRIGGER_HM0       30401
#define TRIGGER_HM198     30599
#define TRIGGER_HL        30600
#define TRIGGER_HL0       30601
#define TRIGGER_HL198     30799
#define TRIGGER_BF        30800
#define TRIGGER_MF1       30801
#define TRIGGER_TL0       30900
#define TRIGGER_TL1       30901
#define TRIGGER_TL2       30902
#define TRIGGER_TL3       30903
#define TRIGGER_TL4       30904
#define TRIGGER_OB_POS    (int)(0x10000000)
#define TRIGGER_LE_POS    (int)(0x20000000)
#define TRIGGER_OB_LEAVE  (int)(0x08000000)

/* Era Triggers */
#define TRIGGER_BEFORE_SAVE_GAME    77000_DEPRECATED
#define TRIGGER_SAVEGAME_WRITE      77001
#define TRIGGER_SAVEGAME_READ       77002
#define TRIGGER_KEYPRESS            77003
#define TRIGGER_OPEN_HEROSCREEN     77004
#define TRIGGER_CLOSE_HEROSCREEN    77005
#define TRIGGER_STACK_OBTAINS_TURN  77006
#define TRIGGER_REGENERATE_PHASE    77007
#define TRIGGER_AFTER_SAVE_GAME     77008
#define TRIGGER_SKEY_SAVEDIALOG     77009_DEPRECATED
#define TRIGGER_HEROESMEET          77010_DEPRECATED
#define TRIGGER_BEFOREHEROINTERACT  77010
#define TRIGGER_AFTERHEROINTERACT   77011

typedef NOALIGN struct TTxtFile
{
  char  Dummy[0x18];
  int   RefCount;
  /* Dummy */
} TTxtFile, *PTxtFile;

typedef NOALIGN struct THookHandlerArgs
{
  int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
  int RetAddr;
} THookHandlerArgs, *PHookHandlerArgs;

typedef NOALIGN struct TEvent
{
  char* Name;
  void* Data;
  int   DataSize;
} TEvent, *PEvent;

typedef int TEventParams[16];
typedef TEventParams* PEventParams;
typedef void (__stdcall *TEventHandler) (PEvent Event);

typedef char  TErmZVar[512];


static int* EventParams = NULL;

/* WoG vars */
static int*      ErmV = (int*)      0x887664; // 1..10000
static TErmZVar* ErmZ = (TErmZVar*) 0x9271E8; // 1..1000
static int*      ErmY = (int*)      0xA48D7C; // 1..100
static int*      ErmX = (int*)      0x91DA34; // 1..16
static bool*     ErmF = (bool*)     0x91F2DF; // 1..1000
static float*    ErmE = (float*)    0xA48F14; // 1..100

typedef struct TGameState
{
  int RootDlgId;
  int CurrentDlgId;
} TGameState, *PGameState;


typedef void (__stdcall *TWriteAtCode) (int Count, void* Src, void* Dst);
typedef void (__stdcall *THook) (void* HandlerAddr, int HookType, int PatchSize, void* CodeAddr);
typedef void (__stdcall *TKillThisProcess) ();
typedef void (__stdcall *TFatalError) (char* Err);
typedef void (__stdcall *TRegisterHandler) (TEventHandler Handler, char* EventName);
typedef void (__stdcall *TFireEvent) (char* EventName, void* EventData, int DataSize);
typedef PTxtFile (__stdcall *TLoadTxt) (char* Name);
typedef void (__stdcall *TForceTxtUnload) (char* Name);
typedef void (__stdcall *TExecErmCmd) (char* CmdStr);
typedef void (__stdcall *TReloadErm) ();
typedef void (__stdcall *TExtractErm) ();
typedef void (__stdcall *TFireErmEvent) (int EventID);
typedef void (__stdcall *TClearIniCache) ();
typedef bool (__stdcall *TReadStrFromIni) (char* Key, char* SectionName, char* FilePath, char* Res);
typedef bool (__stdcall *TWriteStrToIni) (char* Key, char* Value, char* SectionName, char* FilePath);
typedef void (__stdcall *TNameColor) (int Color32, char* Name);
typedef void (__stdcall *TWriteSavegameSection) (int DataSize, void* Data, char* SectionName);
typedef int (__stdcall *TReadSavegameSection) (int DataSize, void* Data, char* SectionName);
typedef void (__stdcall *TGetGameState) (PGameState GameState);
typedef void (__stdcall *TSaveEventParams) ();
typedef void (__stdcall *TRestoreEventParams) ();




static TWriteAtCode          WriteAtCode           = NULL;
static THook                 Hook                  = NULL;
static TKillThisProcess      KillThisProcess       = NULL;
static TFatalError           FatalError            = NULL;
static TRegisterHandler      RegisterHandler       = NULL;
static TFireEvent            FireEvent             = NULL;
static TLoadTxt              LoadTxt               = NULL;
static TForceTxtUnload       ForceTxtUnload        = NULL;
static TExecErmCmd           ExecErmCmd            = NULL;
static TReloadErm            ReloadErm             = NULL;
static TExtractErm           ExtractErm            = NULL;
static TFireErmEvent         FireErmEvent          = NULL;
static TClearIniCache        ClearIniCache         = NULL;
static TReadStrFromIni       ReadStrFromIni        = NULL;
static TWriteStrToIni        WriteStrToIni         = NULL;
static TNameColor            NameColor             = NULL;
static TWriteSavegameSection WriteSavegameSection  = NULL;
static TReadSavegameSection  ReadSavegameSection   = NULL;
static TSaveEventParams      SaveEventParams       = NULL;
static TRestoreEventParams   RestoreEventParams    = NULL;




static void ConnectEra ()
{
  HINSTANCE hAngel                = LoadLibrary(TEXT("angel.dll"));
  EventParams           = (int*) GetProcAddress(hAngel, "EventParams");



  SaveEventParams       = (TSaveEventParams) GetProcAddress(hAngel, "SaveEventParams");
  RestoreEventParams    = (TRestoreEventParams)GetProcAddress(hAngel, "RestoreEventParams");
  /***/
  // HINSTANCE hEra                  = (HINSTANCE) ErmV[1];
  HINSTANCE hEra                     = LoadLibrary(TEXT("era.dll"));
  if (!hEra) MessageBoxA(0, "hEra is NULL !!!", "Emerald", 0);

  WriteAtCode           = (TWriteAtCode) GetProcAddress(hEra, "WriteAtCode");
  Hook                  = (THook) GetProcAddress(hEra, "Hook");
  KillThisProcess       = (TKillThisProcess) GetProcAddress(hEra, "KillThisProcess");
  FatalError            = (TFatalError) GetProcAddress(hEra, "FatalError");
  RegisterHandler       = (TRegisterHandler) GetProcAddress(hEra, "RegisterHandler");
  FireEvent             = (TFireEvent) GetProcAddress(hEra, "FireEvent");
  LoadTxt               = (TLoadTxt) GetProcAddress(hEra, "LoadTxt");
  ForceTxtUnload        = (TForceTxtUnload) GetProcAddress(hEra, "ForceTxtUnload");
  ExecErmCmd            = (TExecErmCmd) GetProcAddress(hEra, "ExecErmCmd");
  if (!ExecErmCmd) MessageBoxA(0, "ExecErmCmd is NULL !!!", "Emerald", 0);


  ReloadErm             = (TReloadErm) GetProcAddress(hEra, "ReloadErm");
  ExtractErm            = (TExtractErm) GetProcAddress(hEra, "ExtractErm");
  FireErmEvent          = (TFireErmEvent) GetProcAddress(hEra, "FireErmEvent");
  ClearIniCache         = (TClearIniCache) GetProcAddress(hEra, "ClearIniCache");
  ReadStrFromIni        = (TReadStrFromIni) GetProcAddress(hEra, "ReadStrFromIni");
  WriteStrToIni         = (TWriteStrToIni) GetProcAddress(hEra, "WriteStrToIni");
  NameColor             = (TNameColor) GetProcAddress(hEra, "NameColor");
  WriteSavegameSection  = (TWriteSavegameSection) GetProcAddress(hEra, "WriteSavegameSection");
  ReadSavegameSection   = (TReadSavegameSection) GetProcAddress(hEra, "ReadSavegameSection");
}

#endif
