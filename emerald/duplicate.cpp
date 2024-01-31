#include "emerald.h"


extern int IsArtifactAllowWaterWalk(int id, int customdata);
extern int IsArtifactAllowFly(int id, int customdata);




int __stdcall NewHasArtifact(HiHook* h, HERO* hero, int art)
{
	int ret = CALL_2(int, __thiscall, h->GetDefaultFunc(), hero, art);

	if (h->GetReturnAddress() < 0x700000 && h->GetReturnAddress() > 0x400000) //We only fool SoD;
	{
		for (int i=0; i!=19; i++)
		{
			if (art==ARTIFACT_SPELLBOOK && hero->IArt[i][0]!=-1 &&  //if the heroes reach for a book, then 
				GetArtifactRecord(hero->IArt[i][0])->rank & 0x40)	//we check for the presence of spellbooks in all slots and replace the answer 
			{
				//sprintf(buf,"NewHasArtifact::Spellbook found at slot %i", i);
				//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),(const void*)buf,64,0,0);
				return true;
			}


			if (art==ARTIFACT_ANGELWINGS && hero->IArt[i][0]!=-1 && 
				IsArtifactAllowFly(hero->IArt[i][0],hero->IArt[i][1]))
			{
				return true;
			}


			if (art==ARTIFACT_WATERBOOTS && hero->IArt[i][0]!=-1 && 
				IsArtifactAllowWaterWalk(hero->IArt[i][0],hero->IArt[i][1]))
			{
				return true;
			}
		}
	}

	return ret;
}

int __stdcall NewHasArtifactInBP(HiHook* h, HERO* hero, int art)
{
	int ret = CALL_2(int, __thiscall, h->GetDefaultFunc(), hero, art);

	if (h->GetReturnAddress() < 0x700000 && h->GetReturnAddress() > 0x400000)//We're only fooling SoD;
	{
		for (int i=0; i!=19; i++)
		{
			if (art==ARTIFACT_SPELLBOOK && hero->IArt[i][0]!=-1 && (GetArtifactRecord(hero->IArt[i][0])->rank & 0x40))
			{
				//sprintf(buf,"NewHasArtifactInBP::Spellbook found at slot %i, artid:%i rank: %x", i, hero->IArt[i][0], GetArtifactRecord(hero->IArt[i][0]));
				//WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE),(const void*)buf,64,0,0);
				return true;
			}

		}

		for (int i=0; i!=64; i++)
		{
			if (art==ARTIFACT_SPELLBOOK && hero->OArt[i][0]!=-1  && (GetArtifactRecord(hero->OArt[i][0])->rank & 0x40))
			{
				//sprintf(buf,"NewHasArtifactInBP::Spellbook found at bp slot %i", i);
				//WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE),(const void*)buf,64,0,0);
				return true;
			}
		}

		//In fact, the usefulness of this hook is limited by the spellbook. 
		//Well, it seems like the cars also showed up somewhere.
	}
	return ret;
}