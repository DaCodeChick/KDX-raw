#pragma once

#include "typedefs.h"

#ifdef _WIN32
typedef SOCKET TSocket;
#else
typedef int TSocket;
#endif // _WIN32

/// @brief A structure representing a regular transport layer.
struct SRegularTransport;

/// @brief A function pointer type for handling transport events.
typedef void (*TRHandlerProc)(ushort inListenPort, SRegularTransport *inTpt, int inType);

class EXPORT URegularTransport
{
public:
	static void ConfigureSocket(TSocket inSocket);
};
