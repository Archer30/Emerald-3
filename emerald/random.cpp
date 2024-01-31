
#include "emerald.h"
//extern GAMEDATA2 no_save;

extern void DebugWindow(void);

/*
void __stdcall UndoProhibitionTables(PEvent e) 
{
	int used_artifacts_references[] =
	{ 0x4BCC98, 0x4BCCC8, 0x4BE1BB, 0x4C0776,
		0x4C07E9, 0x4C91B5, 0x4C91ED, 0x4C9237,
		0x4C9252, 0x4CE084 };

	for (int i = 0; i != sizeof(used_artifacts_references) / 4; i++)
	{
		emerald->WriteDword(used_artifacts_references[i], 0x4E224);
	}


	int allowed_artifacts_references[] =
	{ 0x4BCC8C, 0x4BCCBC, 0x4BE1A8, 0x4C0767,
		0x4C21A2, 0x4C21EB, 0x4C2299, 0x4C24B1,
		0x4C24F7, 0x4C4BB7, 0x4C91E4, 0x4CE093,
		0x5701C4, 0x574AB2, 0x574FD4, 0x714EF5,
		0x714F6F, 0x74E7BF };

	int allowed_artifacts_end_references[] =
	{ 0x4C076D, 0x4C229F, 0x4C23DC };




	emerald->WriteDword(0x4C21B3, OLD_ARTS_AMOUNT * 0x20);
	emerald->WriteDword(0x4C2306, OLD_ARTS_AMOUNT * 0x20);


	emerald->WriteDword(0x4C21E0, OLD_ARTS_AMOUNT);
	emerald->WriteDword(0x4C2279, OLD_ARTS_AMOUNT);

	emerald->WriteDword(0x44D1AA, OLD_ARTS_AMOUNT);




	for (int i = 0; i != sizeof(allowed_artifacts_references) / 4; i++)
	{
		emerald->WriteDword(allowed_artifacts_references[i], 0x4E2B4);
	}

	for (int i = 0; i != sizeof(allowed_artifacts_end_references) / 4; i++)
	{
		emerald->WriteDword(allowed_artifacts_end_references[i], 0x4E344);
	}

	const int old_art = OLD_ARTS_AMOUNT;
	 
	emerald->WriteDword(0x4C9248, old_art);
	emerald->WriteDword(0x4C91C2, old_art);

} */

void __stdcall ReallocProhibitionTables(PEvent e)
{
	static bool first_time_init = true;
	
	static int base = 0;
	
	if (first_time_init && false) {
		//int base = (int)EmeraldArtNewTable;// *(int*)0x699538;
		/*int*/ base = *(int*)0x699538;
		//DebugWindow();
		if (base == 0) { DebugWindow();	return; }
	} first_time_init = false;

	//static bool alreadyRun = false;
	//if (alreadyRun) return;
	//alreadyRun = true;
	//memcpy((void*)(save.used_artifacts),	 (void*)(base+0x4E224), 144);
	//memcpy((void*)(save.allowed_artifacts), (void*)(base+0x4E2B4), 144);

	// lea eax, ds:[esi+0x4E224]
	int used_artifacts_references_lea_eax[] =
	{	0x4BCC98, // lea eax, ds:[esi+0x4E224]
		0x4BCCC8, // lea eax, ds:[esi+0x4E224]
		0x4BE1BB  // lea eax, ds:[ebx+0x4E224]
		
		/* 0x4C0776,
		0x4C07E9, 0x4C91B5, 0x4C91ED, 0x4C9237,
		0x4C9252, 0x4CE084 */ };

	// lea edi, ds:[esi+0x4E224]
	int used_artifacts_references_lea_edi[] =
	{
		0x4C0776,  // lea edi, ds:[ecx+0x4E224]
		0x4CE084   // lea edi, ds:[esi+0x4E224]
	};

	int used_artifacts_references_other[] = //2020-04-04
	{   0x4C07E9, // mov byte ptr ds:[eax+ecx*1+0x4E224], 0x1 // eax+ecx*1+0x4E224 = 0x119F6F4D //ecx = const
		0x4C91B5, // cmp byte ptr ds:[eax+ebx*1+0x4E224], 0x0 // ebx = const
		0x4C91ED, // mov byte ptr ds:[edx+ebx*1+0x4E224], cl  // ebx = const
		0x4C9237, // cmp byte ptr ds:[eax+ebx*1+0x4E224], 0x0 // 
	    0x4C9252  // mov byte ptr ds:[eax+ebx*1+0x4E224], 0x1 // ebx = const
	};


	for (int i = 0; i != sizeof(used_artifacts_references_lea_edi) / 4; i++)
	{
		/////2020-04-02
		//emerald->WriteDword(used_artifacts_references[i], (int)(save.used_artifacts) - base  );
		emerald->WriteDword(used_artifacts_references_lea_edi[i], (int)save.used_artifacts);
		emerald->WriteByte(used_artifacts_references_lea_edi[i] - 1, 0x3D);

		// *(int*)used_artifacts_references[i]+=(int)(save.used_artifacts) - base - 0x4E224;
	}


	for (int i = 0; i != sizeof(used_artifacts_references_lea_eax) / 4; i++)
	{
		/////2020-04-02
		//emerald->WriteDword(used_artifacts_references[i], (int)(save.used_artifacts) - base  );
		emerald->WriteDword(used_artifacts_references_lea_eax[i], (int)save.used_artifacts);
		emerald->WriteByte(used_artifacts_references_lea_eax[i] - 1, 0x05);

		// *(int*)used_artifacts_references[i]+=(int)(save.used_artifacts) - base - 0x4E224;
	}

	
	for (int i = 0; i != sizeof(used_artifacts_references_other) / 4; i++) //2020-04-04
	{
		//continue; 
		/////2020-04-02
		//emerald->WriteDword(used_artifacts_references[i], (int)(save.used_artifacts) - base  );
		emerald->WriteDword(used_artifacts_references_other[i], ((int)save.used_artifacts)  );

		// *(int*)used_artifacts_references[i]+=(int)(save.used_artifacts) - base - 0x4E224;
	}
	

	/*
	//lea eax, ds:[esi+0x4E2B4]
	int allowed_artifacts_references_lea_esi[] =
	{    // 0x4BCC8C,
		// 0x4BCCBC,
		
		// 0x4BE1A8, 0x4C0767, //
		// 0x4C21A2, 0x4C21EB, //
		// 0x4C2299, 
		// 0x4C24B1,
		// 0x4C24F7,  0x4C4BB7,  0x4C91E4, 0x4CE093,
		// 0x5701C4, 0x574AB2, 0x574FD4, 0x714EF5,
		// 0x714F6F, 0x74E7BF 
	};
	*/

	/*
	int allowed_artifacts_references_lea_edi[] =
	{
		0x4C21EB
	};
	*/

	// lea eax, ds: [eax + 0x4E2B4]
	int allowed_artifacts_references_lea_eax[] = 
	{	
		0x4BCC8C, // lea eax, ds:[esi+0x4E2B4]
		0x4BE1A8, // lea eax, ds:[ebx+0x4E2B4]

		/* 0x4C21EB, */ 
	/* 0x4C24B1, 0x4C24F7, 0x4C4BB7,  0x4C91E4, 
	 0x
4,  0x574AB2, 0x574FD4, 0x714EF5, 
	 0x714F6F, 0x74E7BF */
	
		0x4C0767, // lea eax, ds:[ecx+0x4E2B4]
		0x4BCCBC  // lea eax, ds:[esi+0x4E2B4]
	};
	
	// lea ecx, ds:[esi+0x4E2B4]
	emerald->WriteDword(0x4C21A2, (int)save.allowed_artifacts);
	emerald->WriteByte(0x4C21A2 - 1, 0x0d);

	// lea esi, ds:[ecx+0x4E2B4]
	emerald->WriteDword(0x4C2299, (int)save.allowed_artifacts);
	emerald->WriteByte(0x4C2299 - 1, 0x35);

	int allowed_artifacts_references_add_eax[] = {

		0x714EF5, // add eax, 0x4E2B4
		0x714F6F, // add eax, 0x4E2B4
		0x74E7BF, // add eax, 0x4E2B4
	};

	for (int i = 0; i != sizeof(allowed_artifacts_references_add_eax) / 4; i++)
	{
		/////2020-04-02
		
		emerald->WriteDword(allowed_artifacts_references_add_eax[i], (int)save.allowed_artifacts);
		emerald->WriteByte(allowed_artifacts_references_add_eax[i] - 1, 0xb8);
	}

	/*
	int allowed_artifacts_references_mov_ebx_plus_esi[] =
	{
		0x4C24B1, // mov al, byte ptr ds:[ebx+esi*1+0x4E2B4]
		0x4C24F7  // mov byte ptr ds:[ebx+esi*1+0x4E2B4], al
	};
	*/
	int allowed_artifacts_references_other[] = //2020-04-04
	{   0x4C4BB7, // mov byte ptr ds:[ecx+ebx*1+0x4E2B4], 0x1
		0x4C91E4, // mov cl, byte ptr ds:[edx+ebx*1+0x4E2B4] //(warning)
		0x5701C4, // mov byte ptr ds:[eax+edx*1+0x4E2B4], 0x1
		0x574AB2, // mov byte ptr ds:[edx+ecx*1+0x4E2B4], 0x1
	
		0x574FD4, // mov byte ptr ds:[ecx+eax*1+0x4E2B4], 0x1
		// 0x714EF5, // add eax, 0x4E2B4
		// 0x714F6F, // add eax, 0x4E2B4
		// 0x74E7BF, // add eax, 0x4E2B4
	
		0x4C21EB, // lea edi, ds:[eax+esi*1+0x4E2B4]

		// 0x4CE093 // lea edi, ds:[esi+0x4E2B4]

		0x4C24B1, // mov al, byte ptr ds:[ebx+esi*1+0x4E2B4]
		0x4C24F7  // mov byte ptr ds:[ebx+esi*1+0x4E2B4], al
	};

	 emerald->WriteDword(0x4C21B3, NEW_ARTS_AMOUNT*0x20); //2020-04-09 // cmp eax, 0x1200
	 emerald->WriteDword(0x4C2306, NEW_ARTS_AMOUNT*0x20); //2020-04-09 // cmp esi, 0x1200

	
	 emerald->WriteDword(0x4C21E0, NEW_ARTS_AMOUNT);  //2020-04-09 // mov ecx, 0x90
	 emerald->WriteDword(0x4C2279, NEW_ARTS_AMOUNT);  //2020-04-09 // cmp esi, 0x90   // cmp esi, 0xA0

	 emerald->WriteDword(0x44D1AA, NEW_ARTS_AMOUNT);  //2020-04-09 // cmp esi,0x90    // cmp esi, 0xA0                                                    |

	
	emerald->WriteDword(0x4CE093, (int)save.allowed_artifacts);
	emerald->WriteByte(0x4CE093 - 1, 0x3d);

	for (int i = 0; i != sizeof(allowed_artifacts_references_other) / 4; i++) //2020-04-04
	{
		//continue;
		/////2020-04-02
		emerald->WriteDword(allowed_artifacts_references_other[i], (int)save.allowed_artifacts /*- base + 0x4e2b4 */);
		//emerald->WriteDword(allowed_artifacts_references_other[i], (int)save.allowed_artifacts);

	}

	/*
	for (int i = 0; i != sizeof(allowed_artifacts_references_mov_ebx_plus_esi) / 4; i++)
	{
		continue;
		/////2020-04-02
		emerald->WriteDword(allowed_artifacts_references_mov_ebx_plus_esi[i], (int)save.allowed_artifacts - base + 0x4e2b4);
		//emerald->WriteDword(allowed_artifacts_references_mov_ebx_plus_esi[i], (int)save.allowed_artifacts);
		
	}
	*/


	/*
	for (int i=0; i!=sizeof(allowed_artifacts_references_lea_esi)/4; i++)
	{
		/////2020-04-02
		//emerald->WriteDword(allowed_artifacts_references[i], (int)(save.allowed_artifacts) - base );
		emerald->WriteDword(allowed_artifacts_references_lea_esi[i], (int)save.allowed_artifacts);
		emerald->WriteByte(allowed_artifacts_references_lea_esi[i] - 1, 0x3D);
	}
	*/


	for (int i = 0; i != sizeof(allowed_artifacts_references_lea_eax) / 4; i++)
	{
		/////2020-04-02
		//emerald->WriteDword(allowed_artifacts_references[i], (int)(save.allowed_artifacts) - base );
		emerald->WriteDword(allowed_artifacts_references_lea_eax[i], (int)save.allowed_artifacts);
		emerald->WriteByte(allowed_artifacts_references_lea_eax[i] - 1, 0x05);
	}


	//int allowed_artifacts_end = (int)save.marker_1;
	int allowed_artifacts_end = (int)(save.allowed_artifacts + NEW_ARTS_AMOUNT);


	int allowed_artifacts_end_references_lea[] =
	{   0x4C076D,  // lea esi, ds:[ecx+0x4E344]
		0x4C229F,  // lea eax, ds:[ecx+0x4E344]
		0x4C23DC   //add eax, 0x4E344
	};

	for (int i=0; i!=sizeof(allowed_artifacts_end_references_lea)/4; i++)
	{
		/////2020-04-02
		//emerald->WriteDword(allowed_artifacts_end_references[i], (int)(/*save.unknown_art1*/ /*save.footer*/ save.marker_1) - base  );
		emerald->WriteDword(allowed_artifacts_end_references_lea[i], allowed_artifacts_end);
		//emerald->WriteByte(allowed_artifacts_end_references_lea[i] - 1, 0x3D);
	}
	emerald->WriteByte(allowed_artifacts_end_references_lea[0] - 1, 0x35);
	emerald->WriteByte(allowed_artifacts_end_references_lea[1] - 1, 0x05);
	emerald->WriteByte(allowed_artifacts_end_references_lea[2] - 1, 0xB8);

	////add eax, 0x4E344
	//emerald->WriteDword(0x4C23DC, (int)save.marker_1);
	//emerald->WriteByte(0x4C23DC -1, 0xb8);

	const int max_art = NEW_ARTS_AMOUNT; 

	//emerald->WriteDword(0x4C076D, max_art + (int)(save.allowed_artifacts) - base);
	//emerald->WriteDword(0x4C229F, max_art + (int)(save.allowed_artifacts) - base);
	//emerald->WriteDword(0x4C23DC, max_art + (int)(save.allowed_artifacts) - base);
	
	 emerald->WriteDword(0x4C9248, max_art); //2020-04-09 // cmp eax, 0x90
	 emerald->WriteDword(0x4C91C2, max_art); //2020-04-09 // cmp eax, 0x90

	/*
	*(int*)(0x4C076B+2) += 188 + (int)(save.allowed_artifacts) - base - 0x4E2B4;
	*(int*)(0x4C229D+2) += 188 + (int)(save.allowed_artifacts) - base - 0x4E2B4;
	*(int*)(0x4C23DB+1) += 188 + (int)(save.allowed_artifacts) - base - 0x4E2B4;
	*/


	
        // *(int*)0x4C9248 = (int)188;
        // *(int*)0x4C91C2 = (int)188;


	//---------------------------------------------------------------------------------
	// 2020-04-04
	replace_byte opcodes_other[] = {
		{0x004C4BB4, 0x90}, {0x004C4BB5, 0xC6}, {0x004C4BB6, 0x81}, // seems to work
		{0x004C07E6, 0x90}, {0x004C07E7, 0xc6}, {0x004C07E8, 0x80}, // seems to work
		{0x004C91B2, 0x80}, {0x004C91B3, 0x3c}, {0x004C91B4, 0x05}, // seems to work
		{0x004C9234, 0x90}, {0x004C9235, 0x80}, {0x004C9236, 0xB8}, // seems to work
		{0x004C924F, 0x90}, {0x004C9250, 0xc6}, {0x004C9251, 0x80}, // seems to work

		{0x004C21E8, 0x8D}, {0x004C21E9, 0x3c}, {0x004C21EA, 0x35}, // guessed
		{0x004C24AE, 0x8a}, {0x004C24AF, 0x04}, {0x004C24B0, 0x35}, // guessed
		{0x004C24F4, 0x88}, {0x004C24F5, 0x04}, {0x004C24F6, 0x35}, // guessed

		{0x004c91e1, 0x8a}, {0x004c91e2, 0x0c}, {0x004c91e3, 0x15}, /// guessed (warning)
		{0x004C91EA, 0x88}, {0x004C91EB, 0x0c}, {0x004C91EC, 0x15}, // guessed


		 {0x005701C1, 0xc6}, {0x005701C2, 0x04}, {0x005701C3, 0x15}, // guessed
		 {0x00574AAF, 0xc6}, {0x00574AB0, 0x04}, {0x00574AB1, 0x0d}, // guessed
		 {0x00574FD1, 0xc6}, {0x00574FD2, 0x04}, {0x00574FD3, 0x05}, // guessed

		 {0x005701BC,0x90},{0x005701BD,0x90},{0x005701BE,0x90},{0x005701BF,0x90},{0x005701C0,0x90},
		 {0x00574AA9,0x90},{0x00574AAA,0x90},{0x00574AAB,0x90},{0x00574AAC,0x90},{0x00574AAD,0x90},{0x00574AAE,0x90},
		 {0x00574FCB,0x90},{0x00574FCC,0x90},{0x00574FCD,0x90},{0x00574FCE,0x90},{0x00574FCF,0x90},{0x00574FD0,0x90},


		// {0x005701C1, 0xc6}, {0x005701C2, 0x04}, {0x005701C3, 0x05}, // guessed
		// {0x00574AAF, 0xc6}, {0x00574AB0, 0x04}, {0x00574AB1, 0x15}, // guessed
		// {0x00574FD1, 0xc6}, {0x00574FD2, 0x04}, {0x00574FD3, 0x0d}, // guessed


		{0x0,0x0} // end of sequence
	};

	for (int i = 0;opcodes_other[i].address;i++) {
		emerald->WriteByte(opcodes_other[i].address, opcodes_other[i].new_byte);
	}

	/*
	// new dadresses 2020-04-09
	emerald->WriteDword(0x004DC31b, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004dc129, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x0048e5af, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004ddfa6, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004dc358, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004dc1dc, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004dc242, NEW_ARTS_AMOUNT);
	emerald->WriteDword(0x004dc26c, NEW_ARTS_AMOUNT);
	*/
}