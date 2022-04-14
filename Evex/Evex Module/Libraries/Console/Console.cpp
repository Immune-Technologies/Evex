#include "Console.hpp"
#include <WinUser.h>
#include <consoleapi3.h>
#include <consoleapi.h>
#include <cstdint>
#include <memoryapi.h>
#include <ostream>
#include <iostream>

void FreeConsoleBypass()
{
    static auto ptr = reinterpret_cast<std::uintptr_t>(&FreeConsole);
    static auto ptr_jmp = ptr + 0x6;

    DWORD old{};

    VirtualProtect(reinterpret_cast<void*>(ptr), 0x6, PAGE_EXECUTE_READWRITE, &old);

    *reinterpret_cast<std::uintptr_t**>(ptr + 0x2) = &ptr_jmp;
    *reinterpret_cast<std::uint8_t*>(ptr + 0x6) = 0xC3;

    VirtualProtect(reinterpret_cast<void*>(ptr), 0x6, old, &old);
}

void Console::Initialize(const char* Name)
{
    FreeConsoleBypass();

    AllocConsole();
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
    SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT Rect = { 0,0, 80, 19 };
    SetConsoleWindowInfo(hConsole, TRUE, &Rect);
    ShowScrollBar(GetConsoleWindow(), SB_BOTH, 0);

    SetConsoleTitleA(Name);
}

void Console::Hide()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}