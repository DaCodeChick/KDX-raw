set(SOURCES
	GrafTypes.cpp
	UDateTime.cpp
	UError.cpp
	UKeyboard.cpp
	UMath.cpp
	UMemory.cpp
	UMouse.cpp
	USound.cpp
	UText.cpp
)

set(HEADERS
	GrafTypes.h
	typedefs.h
	UDateTime.h
	UError.h
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
