#pragma once

#include "typedefs.h"

struct SRegularTransport;
typedef void (*TRHandlerProc)(ushort inListenPort, SRegularTransport *inTpt, int inType);

class EXPORT URegularTransport
{
};
