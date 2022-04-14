#pragma once 

#include <Windows.h>
#include <cstdio>
#include <cstdint>
#include <memoryapi.h>
#include <consoleapi.h>
#include <ostream>

namespace Console
{
    void Initialize(const char* Name);
    void Hide();
}