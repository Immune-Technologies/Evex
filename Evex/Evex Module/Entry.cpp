/*
* Credit To Rexi Been A Great Friend And Tought Me A Lot Of C++ And Roblox Internals Related Stuff 
*/

/* <-- Includes --> */
#include <Windows.h>
#include <string>
#include <thread>
#include <iostream>

/* <-- Third Party Libraries --> */
#include "Addresses/Addresses.h"
#include "Libraries/Console/Console.hpp"

/* <-- Config --> */
#include "Config.h"

#define Debug true /* Determines If Console Is Hidden : Visible */

namespace Initialization
{
	unsigned long __stdcall Pipe(void*) {
		char Buffer[999999];
		DWORD Len;
		HANDLE NamedPipe = CreateNamedPipe(TEXT(LuaPipe),
			PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE, PIPE_WAIT,
			1, NULL, NULL, NMPWAIT_USE_DEFAULT_WAIT, NULL);

		while (NamedPipe != INVALID_HANDLE_VALUE)
		{
			if (ConnectNamedPipe(NamedPipe, NULL) != FALSE)
			{
				while (ReadFile(NamedPipe, Buffer, sizeof(Buffer) - 1, &Len, NULL) != FALSE)
				{
					Buffer[Len] = '\0';
				}
				Roblox::Print(0, Buffer);
			}
			DisconnectNamedPipe(NamedPipe);
		}
	}

	void Init()
	{
		Roblox::Print(1, "Powered By Evex | Open Source "); /* Keep This Or You As Script Kiddie */
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialization::Pipe), 0, 0, 0);
		std::cout << "Ready To Print To Pipe : " << LuaPipe;

		std::string Input;
		for (; ;)
		{
			std::cout << " > ";
			std::cin >> Input;
			Roblox::Print(0, Input.c_str());
		}
	}
}

void Thread() { Initialization::Init(); }

BOOL APIENTRY DllMain(HMODULE hModule, std::int32_t CallReason, LPVOID lpReserved)
{
	if (CallReason)
	{
		Console::Initialize(ExploitName);

		if (!Debug == true)
			Console::Hide();

		std::thread(Thread).detach();
	}
	return 1;
}
