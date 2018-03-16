#include "ghost.h"
#include "imgui.h"


#include <iostream>



void TacGhost::Init()
{
	HANDLE process = GetCurrentProcess();
	PCSTR UserSearchPath = NULL;
	BOOL fInvadeProcess = TRUE;
	SymInitialize( process, UserSearchPath, fInvadeProcess );

	mProcess = process;
}
void TacGhost::Update()
{
	if( ImGui::Button( "A" ) )
		TacGhost::FuncA();
	ImGui::SameLine();
	if( ImGui::Button( "B" ) )
		TacGhost::FuncB();
	ImGui::SameLine();
	if( ImGui::Button( "C" ) )
		TacGhost::FuncC();
	if( ImGui::Button( "Clear" ) )
		mStack.clear();

	ImGui::Separator();
	ImGui::Text( "Stack Begin" );
	ImGui::Indent();
	for( auto line : mStack )
	{
		ImGui::Text( line.c_str() );
	}
	ImGui::Unindent();
	ImGui::Text( "Stack End" );
}
void TacGhost::GetStack()
{
	mStack.clear();
	DWORD FramesToSkip = 0;
	const DWORD FramesToCapture = 63; // https://msdn.microsoft.com/en-us/library/windows/desktop/bb204633(v=vs.85).aspx
	void* BackTrace[ FramesToCapture ];
	PDWORD BackTraceHash = NULL;
	USHORT capturedFrameCount = CaptureStackBackTrace( 
		FramesToSkip,
		FramesToCapture,
		BackTrace,
		BackTraceHash );
	for( USHORT frameIndex = 0; frameIndex < capturedFrameCount; ++frameIndex )
	{
		const int TacSymbolMaxNameByteCount = 1024;
		auto Address = ( DWORD64 )BackTrace[ frameIndex ];
		DWORD64 Displacement;
		const DWORD symbolInfoStructByteCount = sizeof( SYMBOL_INFOW );
		std::vector< char > symbol_and_name( symbolInfoStructByteCount+ TacSymbolMaxNameByteCount );
		auto symbolInfo = ( PSYMBOL_INFO )symbol_and_name.data();
		symbolInfo->MaxNameLen = TacSymbolMaxNameByteCount;
		symbolInfo->SizeOfStruct = symbolInfoStructByteCount;
		SymFromAddr( 
			mProcess,
			Address,
			&Displacement,
			symbolInfo );
		std::string symbolName( symbolInfo->Name, symbolInfo->NameLen );
		mStack.push_back( symbolName );
	}
}
void TacGhost::FuncA()
{
	FuncB();
}
void TacGhost::FuncB()
{
	FuncC();
}
void TacGhost::FuncC()
{
	GetStack();
}
