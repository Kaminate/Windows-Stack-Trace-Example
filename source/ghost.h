#pragma once

#include <vector>
#include <string>

#include <windows.h> // Must be included before DbgHelp
#include <DbgHelp.h> // SymFromAddr, HANDLE, must be included after windows.h

#pragma comment( lib, "Dbghelp.lib" ) // SymFromAddr

struct TacGhost
{
	void Init();
	void Update();
	void GetStack();
	void FuncA();
	void FuncB();
	void FuncC();

	HANDLE mProcess;
	std::vector< std::string > mStack;
};
