#include "URegularTransport.h"
#include "CPtrList.h"

struct SSendBuf
{
	SSendBuf *next;
	byte *data;
	uint dataSize;
};

struct SRegularTransport
{
	SRegularTransport *next;
	uint tag;
	SOCKET sock;
	HWND hwnd;
	int id;
	TRHandlerProc msgProc;
	void *msgProcContext;
	HANDLE asyncTaskHandle;
	undefined4 field9_0x20;
	uint errorCode;
	CPtrList<SSendBuf> sendQueue;
	CPtrList<SSendBuf> field12_0x38;
	uint bytesSent;
	byte status;
	bool writePending;
	bool isShuttingDown;
	bool isClosed;
	bool isTemporary;
};

static bool gTRInitialized = false;
