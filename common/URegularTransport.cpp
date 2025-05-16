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
	TSocket sock;
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

// KDXClient.exe: 00500200
static bool gTRInitialized = false;

// KDXClient.exe: 0046f6a0
void __cdecl URegularTransport::ConfigureSocket(TSocket inSocket)
{
	char local_c[4];

	local_c[0] = '\0';
	local_c[1] = '\0';
	local_c[2] = '\x02';
	local_c[3] = '\0';
	setsockopt(inSocket, SOL_SOCKET, SO_SNDBUF, local_c, 4);
	setsockopt(inSocket, SOL_SOCKET, SO_RCVBUF, local_c, 4);
	local_c[0] = '\x01';
	local_c[1] = '\0';
	local_c[2] = '\0';
	local_c[3] = '\0';
	setsockopt(inSocket, IPPROTO_TCP, SO_DEBUG, local_c, 4);
	setsockopt(inSocket, SOL_SOCKET, SO_KEEPALIVE, local_c, 4);
	return;
}
