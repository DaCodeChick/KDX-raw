#include "UMouse.h"

// AppearanceEdit.exe: 0046035c
static uint _gCurCursorID = 0;

// AppearanceEdit.exe: 0047a084
static HCURSOR _gCursors[17] = {NULL};

// AppearanceEdit.exe: 00416530
uint UMouse::GetDoubleClickTime(void)
{
	UINT UVar1;

	UVar1 = ::GetDoubleClickTime();
	return UVar1;
}

// AppearanceEdit.exe: 00416530
uint UMouse::GetImage(void)
{
	return _gCurCursorID;
}

// AppearanceEdit.exe: 00416540
void UMouse::GetLocation(LPPOINT outLoc)
{
	GetCursorPos(outLoc);
	return;
}

// AppearanceEdit.exe: 004163f0
void __cdecl UMouse::SetImage(uint inID)
{
	HCURSOR hCursor;

	if (_gCursors[0] == NULL)
	{
		_gCursors[0] = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
		_gCursors[1] = _gCursors[0];
		_gCursors[2] = LoadCursorW(NULL, (LPCWSTR)IDC_IBEAM);
		_gCursors[3] = LoadCursorW(NULL, (LPCWSTR)IDC_CROSS);
		_gCursors[4] = _gCursors[3];
		_gCursors[5] = LoadCursorW(NULL, (LPCWSTR)IDC_WAIT);
		_gCursors[6] = LoadCursorW(NULL, (LPCWSTR)IDC_NO);
		_gCursors[7] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZE);
		_gCursors[8] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZEWE);
		_gCursors[9] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENS);
		_gCursors[10] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENWSE);
		_gCursors[0xb] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENESW);
		_gCursors[0xc] = _gCursors[1];
		_gCursors[0xd] = _gCursors[1];
		_gCursors[0xe] = _gCursors[1];
		_gCursors[0xf] = _gCursors[1];
		_gCursors[0x10] = _gCursors[1];
	}
	if (0x11 < inID)
	{
		inID = 1;
	}
	hCursor = _gCursors[inID];
	if (_gCursors[inID] == NULL)
	{
		hCursor = _gCursors[1];
	}
	SetCursor(hCursor);
	_gCurCursorID = inID;
	return;
}
