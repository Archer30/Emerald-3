
int loc_4D979D = 0x4D979D;
int fun_4E67A0 = 0x4E67A0;
void __declspec(naked) SpellSet_LV5(void) {
	__asm {
	loc_4D9748:
			xor edi, edi
			xor esi, esi
			mov ebx, 0x5 //spell_level
	loc_4D9751:
			mov ecx, dword ptr ds : [0x687FA8]
			cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
	loc_4D9768:
			add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_LV4(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			mov ebx, 0x4 //spell_level
			loc_4D9751 :
			mov ecx, dword ptr ds : [0x687FA8]
			cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
			loc_4D9768 :
		add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_LV3(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			mov ebx, 0x3 //spell_level
			loc_4D9751 :
			mov ecx, dword ptr ds : [0x687FA8]
			cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
			loc_4D9768 :
		add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_LV2(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			mov ebx, 0x2 //spell_level
			loc_4D9751 :
			mov ecx, dword ptr ds : [0x687FA8]
			cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
			loc_4D9768 :
		add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_LV1(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			mov ebx, 0x1 //spell_level
			loc_4D9751 :
			mov ecx, dword ptr ds : [0x687FA8]
			cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
			loc_4D9768 :
		add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_ALL(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			//mov ebx, 0x1 //spell_level
			loc_4D9751 :
			//mov ecx, dword ptr ds : [0x687FA8]
			//cmp dword ptr ds : [esi + ecx + 0x18] , ebx
			//jne loc_4D9768
			push 0x1
			push edi
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0
			loc_4D9768 :
		add esi, 0x88
			inc edi
			cmp esi, 0x2530
			jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_EYE(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			loc_4D9751 :

			mov esi, (0x2*0x88)
			push 0x1
			push 0x2
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x3 * 0x88)
			push 0x1
			push 0x3
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x5 * 0x88)
			push 0x1
			push 0x5
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			// add esi, 0x88
			// inc edi
			// cmp esi, 0x2530
			mov esi, 0x2530

			// jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_ADV(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			loc_4D9751 :

		push 0x1
			push 0x0
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x1 * 0x88)
			push 0x1
			push 0x1
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x2 * 0x88)
			push 0x1
			push 0x2
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x3 * 0x88)
			push 0x1
			push 0x3
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x4 * 0x88)
			push 0x1
			push 0x4
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x5 * 0x88)
			push 0x1
			push 0x5
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x6 * 0x88)
			push 0x1
			push 0x6
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x7 * 0x88)
			push 0x1
			push 0x7
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x8 * 0x88)
			push 0x1
			push 0x8
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x9 * 0x88)
			push 0x1
			push 0x9
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			add esi, 0x88
			// inc edi
			// cmp esi, 0x2530
			mov esi, 0x2530
			//jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_TP(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			loc_4D9751 :

			mov esi, (0x3f * 0x88)
			push 0x1
			push 0x3f
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x8 * 0x88)
			push 0x1
			push 0x8
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x9 * 0x88)
			push 0x1
			push 0x9
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			// add esi, 0x88
			// inc edi
			// cmp esi, 0x2530
			mov esi, 0x2530

			// jl  loc_4D9751
			jmp loc_4D979D
	}
}


void __declspec(naked) SpellSet_4EL(void) {
	__asm {
	loc_4D9748:
		xor edi, edi
			xor esi, esi
			loc_4D9751 :


		mov esi, (0x42 * 0x88)
			push 0x1
			push 0x42
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

		mov esi, (0x43 * 0x88)
			push 0x1
			push 0x43
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x44 * 0x88)
			push 0x1
			push 0x44
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			mov esi, (0x45 * 0x88)
			push 0x1
			push 0x45
			lea ecx, dword ptr ss : [ebp - 0x1C]
			call fun_4E67A0

			// add esi, 0x88
			// inc edi
			// cmp esi, 0x2530
			mov esi, 0x2530

			// jl  loc_4D9751
			jmp loc_4D979D
	}
}