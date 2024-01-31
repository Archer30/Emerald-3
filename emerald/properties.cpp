#include "emerald.h"
extern GAMEDATA2 no_save;

int GetLuckBonus(int id, int customdata)
{

	return no_save.luck_bonuses[id];
}

int GetMoraleBonus(int id, int customdata)
{
	return no_save.morale_bonuses[id];
}

int GetLuckBonusFromBP(int id, int customdata)
{
	return no_save.luck_bonuses_bp[id];
}

int GetMoraleBonusFromBP(int id, int customdata)
{
	return no_save.morale_bonuses_bp[id];
}

int IsArtifactAllowWaterWalk(int id, int customdata)
{
	return false;
}

int IsArtifactAllowFly(int id, int customdata)
{
	return false;
}

// the result is the chance of repelling the spell. 0 - nothing, 1 - immunity.
double AbsorbDamage(int id, int customdata, int spell)
{
	//if (spell==SPELL_ARMAGEDDON)
	//	return 1;

	return no_save.spell_immunity[id][spell];
}

void BattleStartAction(int id, int customdata)
{
	//if(no_save.autocast[id]!=0) CastArtifactSpell(id, no_save.autocast[id],50);
	for(int j=0;j<9;j++) if (no_save.autocast[id][j] != 0)
		CastArtifactSpell(id, no_save.autocast[id][j], 50);


	return;
}


int CalculateAttackBonus(int art, int customdata)
{
	return no_save.crattack_bonuses[art];
}

int CalculateDmgHighBonus(int art, int customdata)
{
	return no_save.dmgmax_bonuses[art];
}

int CalculateDmgLowBonus(int art, int customdata)
{
	return no_save.dmgmin_bonuses[art];
}

int CalculateDefenceBonus(int art, int customdata)
{
	return no_save.crdefence_bonuses[art];
}

int CalculateHealthBonus(int art, int customdata)
{
	return no_save.hp_bonuses[art];
}

int CalculateShotsBonus(int art, int customdata)
{
	return no_save.shots_bonuses[art];
}

int CalculateSpeedBonus(int art, int customdata)
{
	return no_save.speed_bonuses[art];
}

int CalculateSpellsBonus(int art, int customdata)
{
	return no_save.casts_bonuses[art];
}
