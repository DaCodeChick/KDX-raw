#include "UMouse.h"

// AppearanceEdit.exe: 0046035c
static uint gCurCursorID = 0;

// AppearanceEdit.exe: 0047a084
static HCURSOR gCursors[17] = {NULL};

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
	return gCurCursorID;
}

// AppearanceEdit.exe: 00416540
void UMouse::GetLocation(SPoint *outLoc)
{
	GetCursorPos((LPPOINT)outLoc);
	return;
}

// AppearanceEdit.exe: 004163f0
void __cdecl UMouse::SetImage(uint inID)
{
	HCURSOR hCursor;

	if (gCursors[0] == NULL)
	{
		gCursors[0] = LoadCursorW(NULL, (LPCWSTR)IDC_ARROW);
		gCursors[1] = gCursors[0];
		gCursors[2] = LoadCursorW(NULL, (LPCWSTR)IDC_IBEAM);
		gCursors[3] = LoadCursorW(NULL, (LPCWSTR)IDC_CROSS);
		gCursors[4] = gCursors[3];
		gCursors[5] = LoadCursorW(NULL, (LPCWSTR)IDC_WAIT);
		gCursors[6] = LoadCursorW(NULL, (LPCWSTR)IDC_NO);
		gCursors[7] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZE);
		gCursors[8] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZEWE);
		gCursors[9] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENS);
		gCursors[10] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENWSE);
		gCursors[0xb] = LoadCursorW(NULL, (LPCWSTR)IDC_SIZENESW);
		gCursors[0xc] = gCursors[1];
		gCursors[0xd] = gCursors[1];
		gCursors[0xe] = gCursors[1];
		gCursors[0xf] = gCursors[1];
		gCursors[0x10] = gCursors[1];
	}
	if (0x11 < inID)
	{
		inID = 1;
	}
	hCursor = gCursors[inID];
	if (gCursors[inID] == NULL)
	{
		hCursor = gCursors[1];
	}
	SetCursor(hCursor);
	gCurCursorID = inID;
	return;
}
