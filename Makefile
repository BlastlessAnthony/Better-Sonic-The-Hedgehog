################################################################################
#### Pre-Setup
################################################################################

#Getting the operating system.
OPERATING_SYSTEM ?=
ifeq ($(OS),Windows_NT)
	OPERATING_SYSTEM = Windows
else
	KTYPE := $(shell uname -s) #Get the kernal name.
	ifeq ($(KTYPE),Darwin )
		OPERATING_SYSTEM = Darwin
	else ifeq ($(KTYPE),Linux)
		OPERATING_SYSTEM = Linux
	else
$(error Your operating system is not supported. '$(KTYPE)')
	endif
endif

#Getting the computer's processor architecture.
ifeq ($(OPERATING_SYSTEM),Windows)
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		PROCESSOR_ARCHITECTURE = x86_64
	else ifeq ($(PROCESSOR_ARCHITECTURE),ARM64)
		PROCESSOR_ARCHITECTURE = AARCH64
	else ifeq ($(PROCESSOR_ARCHITECTURE),x86)
		PROCESSOR_ARCHITECTURE = x86
	endif
else ifeq ($(OPERATING_SYSTEM),Linux)
	_PROCESSOR_ARCHITECTURE = $(shell uname -m)
	ifeq ($(_PROCESSOR_ARCHITECTURE),x86_64)
		PROCESSOR_ARCHITECTURE = x86_64
	else ifeq ($(_PROCESSOR_ARCHITECTURE),i386)
		PROCESSOR_ARCHITECTURE = x86
	else ifeq ($(_PROCESSOR_ARCHITECTURE),aarch64)
		PROCESSOR_ARCHITECTURE = AARCH64
	else ifeq ($(_PROCESSOR_ARCHITECTURE),arm)
		PROCESSOR_ARCHITECTURE = ARM
	endif
else ifeq ($(OPERATING_SYSTEM),Darwin)
	PROCESSOR_ARCHITECTURE = Universal
else
$(error No.)
endif

################################################################################
#### Build Setup
################################################################################
PROJECT_NAME = Better Sonic The Hedgehog ($(OPERATING_SYSTEM)-$(PROCESSOR_ARCHITECTURE))

#Directories
BUILD_DIRECTORY = ./Build
BINARY_DIRECTORY = ./Binary
INCLUDE_DIRECTORIES = \
	-I "./Raylib/include" \
	-I "./Source" \


BUILD_ARCHITECTURE := $(PROCESSOR_ARCHITECTURE)
BUILD_TYPE := DEBUG
BUILD_TOOLCHAIN ?= NONE


################################################################################
#### Compiler Setup
################################################################################

#Choosing which compiler.
ifeq ($(OPERATING_SYSTEM),Windows)

	#Set the default recommended toolchain.
	ifeq ($(BUILD_TOOLCHAIN),NONE)
		BUILD_TOOLCHAIN = MINGW
	endif

	#Set the compiler based off the toolchain.
	ifeq ($(BUILD_TOOLCHAIN),MSVC)
		C_COMPILER = cl
	else ifeq ($(BUILD_TOOLCHAIN),LLVM)
		C_COMPILER = clang
	else ifeq ($(BUILD_TOOLCHAIN),MINGW)
		C_COMPILER = gcc
	else
		$(error Build toolchain was invalid or none was selected.)
	endif

else
	
	#For Apple's OS' kernal.
	ifeq ($(OPERATING_SYSTEM),Darwin)

		#Set the default recommended toolchain.
		ifeq ($(BUILD_TOOLCHAIN),NONE)
			BUILD_TOOLCHAIN = LLVM
		endif

		#Set the compiler based off the toolchain.
		ifeq ($(BUILD_TOOLCHAIN),LLVM)
				C_COMPILER = clang
		else ifeq ($(BUILD_TOOLCHAIN),GCC)
			C_COMPILER = gcc
		else
			$(error Build toolchain was invalid or none was selected.)
		endif

	endif

endif

#Get source files
SOURCE_DIRECTORY = ./Source
ifeq ($(OPERATING_SYSTEM),Windows)
	#SOURCES = $(subst \,/, $(shell dir "$(subst /,\,$(SOURCE_DIRECTORY))\*.c" /n /b /s))
	SOURCES = $(subst \,/, $(shell forfiles /s /m *.c /c "cmd /c echo @relpath"))
else
	#SOURCES = $(sort $(shell find "$(SOURCE_DIRECTORY)" -name '*.c'))
	SOURCES =  $(shell find "$(SOURCE_DIRECTORY)" -name "*.c")
endif

OBJECTS = $(patsubst %.c,%.o,$(SOURCES))
OBJECT_DEPENDENCIES = $(patsubst %.o,%.d,$(OBJECTS))

all:
	@printf "$(OBJECT_DEPENDENCIES)"