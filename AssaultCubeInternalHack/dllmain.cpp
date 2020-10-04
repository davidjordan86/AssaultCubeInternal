// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "reclass.h"
#include "util.h"

typedef playerent* (__cdecl* tGetCrosshairEnt)();

tGetCrosshairEnt GetCrosshairEnt = nullptr;

DWORD WINAPI HackThread(const HMODULE hModule)
{
	//Create Console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	std::cout << "Internal hack injected...\n" << std::endl;

	// Get module base
	const auto module_base = reinterpret_cast<uintptr_t>(GetModuleHandle(L"ac_client.exe"));

	// Get function offset
	GetCrosshairEnt = reinterpret_cast<tGetCrosshairEnt>(module_base + 0x607C0);

	// Init local player
	playerent* local_player_ptr;


	auto b_health = false, b_ammo = false, b_recoil = false, b_trigger_bot = false;

	while (true)
	{
		if (GetAsyncKeyState(VK_END) & 1)
		{
			break;
		}

		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			b_health = !b_health;
			std::cout << b_health << std::endl;
		}

		if (GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			b_ammo = !b_ammo;
			std::cout << b_ammo << std::endl;
		}

		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			b_trigger_bot = !b_trigger_bot;
			std::cout << b_trigger_bot << std::endl;
		}

		//no recoil NOP
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			b_recoil = !b_recoil;

			if (b_recoil)
			{
				mem::Nop((BYTE*)(module_base + 0x63786), 10);
			}

			else
			{
				//50 8D 4C 24 1C 51 8B CE FF D2 the original stack setup and call
				mem::Patch((BYTE*)(module_base + 0x63786), (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10);
			}
		}

		//continuous writes / freeze

		local_player_ptr = *(playerent**)(module_base + 0x10F4F4);

		if (local_player_ptr)
		{
			// Unlimited health
			if (b_health)
			{
				local_player_ptr->health = 999;
			}

			// Unlimited ammo
			if (b_ammo)
			{
				local_player_ptr->current_weapon_ptr->clipPtr->ammo= 999;
			}

			// Trigger bot
			if (b_trigger_bot)
			{
				auto* player_in_crosshair = GetCrosshairEnt(); // Run GetCrosshairEnt function and return
				if (player_in_crosshair) // if the return was not a null value
				{
					if (local_player_ptr->team != player_in_crosshair->team) // if local player and aimed at player are on different teams
					{
						local_player_ptr->b_attacking= true;
					}
				}
				else
				{
					local_player_ptr->b_attacking = false;
				}
			}
		}
		Sleep(5);
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), hModule, 0,
		                         nullptr));
	case DLL_PROCESS_DETACH:
		break;
	default: ;
	}
	return TRUE;
}
