set(SOURCES
	ANSI.cpp
	GrafTypes.cpp
	UDateTime.cpp
	UDigest.cpp
	UError.cpp
	UGraphics.cpp
	UKeyboard.cpp
	UMath.cpp
	UMemory.cpp
	UMouse.cpp
	USound.cpp
	UText.cpp
)

set(HEADERS
	ANSI.h
	GrafTypes.h
	typedefs.h
	UDateTime.h
	UDigest.h
	UError.h
	UGraphics.h
	UKeyboard.h
	UMath.h
	UMouse.h
	UMemory.h
	USound.h
	UText.h
)

add_library(
	Haxial SHARED
	${SOURCES}
	${HEADERS}
)
