#pragma once
#include <Windows.h>
#include <cstdint>
#include <cmath>

#define aslr(x) (x - 0x400000 + reinterpret_cast<std::uintptr_t>(GetModuleHandleW(0)))

namespace Roblox
{
	using PrintType = int(__cdecl*)(int Type, const char* Message);
	PrintType Print = (PrintType)(aslr(0x75C120));
}
