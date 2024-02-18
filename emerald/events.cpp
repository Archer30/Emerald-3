#include "emerald.h"
//extern GAMEDATA2 no_save;

extern void BattleStartAction(int art, int customdata);
/* Disabled by Archer 13 Feb 2024 
extern void CastArtifactSummon(int artifact, int spell, int SpellPower, int SpellLevel);
*/

extern int CalculateAttackBonus(int art, int customdata);
extern int CalculateDmgHighBonus(int art, int customdata);
extern int CalculateDmgLowBonus(int art, int customdata);
extern int CalculateDefenceBonus(int art, int customdata);
extern int CalculateHealthBonus(int art, int customdata);
extern int CalculateShotsBonus(int art, int customdata);
extern int CalculateSpeedBonus(int art, int customdata);
extern int CalculateSpellsBonus(int art, int customdata);

int __stdcall BattleStartHook(LoHook* h, HookContext* c)
{
	if (!ExecErmCmd) ConnectEra();
	HERO *hero = (HERO*)c->edi;
	
/* Disabled by Archer 14 Feb 2024
	for (int i = 0; i != 19; i++)
	{
		if (hero->IArt[i][0] != -1)
		{
			CastArtifactSummon(hero->IArt[i][0],2,hero->PSkill[2],0);
		}
	}
*/
	for (int i=0; i!=19; i++)
	{
		if(hero->IArt[i][0]!=-1)
		{
			BattleStartAction(hero->IArt[i][0], hero->IArt[i][1]);

			if(no_save.erm_on_battlestart[hero->IArt[i][0]]!=0
				&& no_save.erm_on_battlestart[hero->IArt[i][0]][0] )
					ExecErmSequence(no_save.erm_on_battlestart[hero->IArt[i][0]]);
		}
	}

	return EXEC_DEFAULT;
}



int __stdcall OnCreatureParamInit (HiHook* h, HERO* hero, int creature, MONSTER_PROP* monster)
{
	CALL_3(int ,__thiscall, h->GetDefaultFunc(), hero, creature, monster);

	for (int i=0; i!=19; i++)
	{
		if(hero->IArt[i][0]!=-1)
		{
			monster->attack+=CalculateAttackBonus		(hero->IArt[i][0], hero->IArt[i][1]);
			monster->damage_high+=CalculateDmgHighBonus	(hero->IArt[i][0], hero->IArt[i][1]);
			monster->damage_low+=CalculateDmgLowBonus	(hero->IArt[i][0], hero->IArt[i][1]);
			monster->defence+=CalculateDefenceBonus		(hero->IArt[i][0], hero->IArt[i][1]);
			monster->hp+=CalculateHealthBonus			(hero->IArt[i][0], hero->IArt[i][1]);
			monster->shots+=CalculateShotsBonus			(hero->IArt[i][0], hero->IArt[i][1]);
			monster->speed+=CalculateSpeedBonus			(hero->IArt[i][0], hero->IArt[i][1]);
			monster->spells+=CalculateSpellsBonus		(hero->IArt[i][0], hero->IArt[i][1]);

			
			if(no_save.erm_on_creature_param_init[hero->IArt[i][0]]!=0
				&& no_save.erm_on_creature_param_init[hero->IArt[i][0]][0])
			{
				*(int*)0x27F9970 = (int)hero;
				ErmV[998] = hero->x;
				ErmV[999] = hero->y;
				ErmV[1000] = hero->l;

				ErmF[1000]= !CALL_1(int, __thiscall, 0x4BAA60, *(int*)0x69CCFC);

				ErmV[1]=hero->Id;
				ErmV[2]=creature;
				ErmV[3]=(int)monster;

				if(no_save.erm_on_creature_param_init[hero->IArt[i][0]]!=0
					&& no_save.erm_on_creature_param_init[hero->IArt[i][0]][0])
						ExecErmSequence(no_save.erm_on_creature_param_init[hero->IArt[i][0]]);

			}
		}
	}

	return 0;
}


void __stdcall OnEquip (PEvent e)
{

	if (!ExecErmCmd) ConnectEra();

	int artifact = *(int*)0x27F9964;

	if(no_save.erm_on_ae0[artifact]
		&& no_save.erm_on_ae0[artifact][0])
	{
		ExecErmSequence(no_save.erm_on_ae0[artifact]);
	}
}

void __stdcall OnUnequip (PEvent e)
{
	int artifact = *(int*)0x27F9964;
	if(no_save.erm_on_ae1[artifact]
		&& no_save.erm_on_ae1[artifact][0] )
	{
		ExecErmSequence(no_save.erm_on_ae1[artifact]);
	}
}

void __stdcall OnBattleStart(PEvent e)
{
	if (!ExecErmCmd) ConnectEra();
    int combat_manager = (*((int*)0x699420));
	
	//ExecErmCmd("IF:L^battle started^;");

	/*
	char luckmoraleenemy[] = "!!HEv1:R0/?v5;!!HEv1:R1/?v4;!!VRv4:+v2;!!VRv5:+v3;!!HEv1:R0/v3;!!HEv1:R1/v2;";
	for (int i = 0; i != 19; i++) {
		HERO *attacker = (HERO*)(*(int*)(combat_manager+21452));
		HERO *defender = (HERO*)(*(int*)(combat_manager+21456));

		if (defender && attacker->IArt[i][0] != -1) {
			ErmV[1] = -20; 
			
			ErmV[2] = no_save.enemy_luck_bonuses[attacker->IArt[i][0]];
			ErmV[3] = no_save.enemy_morale_bonuses[attacker->IArt[i][0]];

			//ExecErmSequence(luckmoraleenemy);
			defender->DLuck += ErmV[2]; defender->DMorale += ErmV[3];
		}

		if (defender && defender->IArt[i][0] != -1) {
			ErmV[1] = -10;

			ErmV[2] = no_save.enemy_luck_bonuses[defender->IArt[i][0]];
			ErmV[3] = no_save.enemy_morale_bonuses[defender->IArt[i][0]];

			//ExecErmSequence(luckmoraleenemy);
			attacker->DLuck += ErmV[2]; attacker->DMorale += ErmV[3];
		}
	}
	*/

	//	 ExecErmCmd("BA:H0/?v1;");
	//   ExecErmCmd("IF:L^%V1^;");

	HERO *attacker = (HERO*)GetHeroRecord(ErmV[1]);
	
	for (int i=0; i!=19; i++)
	{
		if(attacker->IArt[i][0]!=-1)
		{
			ErmV[1]=0;
			if(*no_save.erm_on_ba52[attacker->IArt[i][0]]!=0)
				ExecErmSequence(no_save.erm_on_ba52[attacker->IArt[i][0]]);
		}
	}

	ExecErmCmd("BA:H1/?v1;");
	HERO *defender = (HERO*)GetHeroRecord(ErmV[1]);
	
	if(ErmV[1]!=-2)
	{
		for (int i=0; i!=19; i++)
		{
			if(defender->IArt[i][0]!=-1)
			{
				ErmV[1]=1;
				if(*no_save.erm_on_ba52[defender->IArt[i][0]]!=0)
					ExecErmSequence(no_save.erm_on_ba52[defender->IArt[i][0]]);
			}
		}
	}
}


void __stdcall OnBattleEnd(PEvent e)
{
	if (!ExecErmCmd) ConnectEra();
	
	//   ExecErmCmd("BA:H0/?v1;");
	//   ExecErmCmd("IF:L^%V1^;");

       char* combat_manager = (char*)(*((int*)0x699420));

	HERO *attacker = (HERO*)(*(int*)(combat_manager+21452));
	HERO *defender = (HERO*)(*(int*)(combat_manager+21456));
	
	if(attacker)
	{
		for (int i = 0; i != 19; i++)
		{
			if (attacker->IArt[i][0] != -1)
			{
				ErmV[1] = 0;
				if (*no_save.erm_on_ba53[attacker->IArt[i][0]] != 0)
					ExecErmSequence(no_save.erm_on_ba53[attacker->IArt[i][0]]);
			}
		}
	}

	if(defender)
	{
		for (int i=0; i!=19; i++)
		{
			if(defender->IArt[i][0]!=-1)
			{
				ErmV[1]=1;
				if(*no_save.erm_on_ba53[defender->IArt[i][0]]!=0)
					ExecErmSequence(no_save.erm_on_ba53[defender->IArt[i][0]]);
			}
		}
	}
}

void __stdcall OnNewDay(PEvent e)
{
	if (!ExecErmCmd) ConnectEra();
	//int owner = *(int*)(e->Data);
	// int owner = 0;
	if (!ExecErmCmd) MessageBoxA(0, "ExecErmCmd is NULL !!!" , "Emerald", 0);
	//ExecErmCmd("IF:M^test^");
	
	
	int tmp = ErmV[1];
	ExecErmCmd("OW:C?v1;");
	int owner = ErmV[1];
	ErmV[1] = tmp;
	
	//ExecErmCmd("IF:M^test^");
	
	HERO* hero;

	//return;

	for(int i=0; i!=156; i++)
	{
		if((hero = (HERO*)GetHeroRecord(i))->Owner == owner)
		{
			for (int j = 0; j != 19; j++)
			{
				if (hero->IArt[j][0] != -1)
				{
					float* InteligenceTable = (float*)*(int*)(0x004D8C1D + 3);
					int max_spell_points = hero->PSkill[3] * 10 * (1.0 + InteligenceTable[hero->SSkill[24]]);
					if (hero->SpPoints < max_spell_points) {
						hero->SpPoints += no_save.regenerate_spellpoints[hero->IArt[j][0]];
						if (hero->SpPoints > max_spell_points) hero->SpPoints = max_spell_points;
					}
					for (int k = 0; k < 9; k++) {
						for (int m = 0; m < 7; m++)
							if (hero->Ct[m] == no_save.upgrade_from[hero->IArt[j][0]][k])
								hero->Ct[m] = no_save.upgrade_to[hero->IArt[j][0]][k];
					}
				}
			}
			
			for (int j = 0; j != 19; j++)
			{
				if(hero->IArt[j][0] != -1)
				{
					ErmV[1]=owner;
					ErmV[2]=hero->Number;
					ErmV[3]=*(1+(int*)(e->Data));
					if(no_save.erm_on_timer[hero->IArt[j][0]]!=0
						&& no_save.erm_on_timer[hero->IArt[j][0]][0] )
						ExecErmSequence(no_save.erm_on_timer[hero->IArt[j][0]]);
				}
			}
			
		}
	}
}
