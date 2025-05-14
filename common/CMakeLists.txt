set(SOURCES
	GrafTypes.cpp
	UDateTime.cpp
	UError.cpp
	UKeyboard.cpp
	UMemory.cpp
	UText.cpp
)

set(HEADERS
	GrafTypes.h
	typedefs.h
	UDateTime.h
	UError.h
	UKeyboard.h
	UMemory.h
	UText.h
)

add_library(
	Haxial SHARED
	${SOURCES}
	${HEADERS}
)
