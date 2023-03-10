################################################################################
#### Pre-Setup
################################################################################

#Getting the operating system.
ifeq ($(OS),Windows_NT)
	OPERATING_SYSTEM = Windows
else
	_KTYPE = $(shell uname -s) #Get the kernal name.
	ifeq ($(_KTYPE),Darwin)
		OPERATING_SYSTEM = Darwin
	else ifeq ($(_KTYPE),Linux)
		OPERATING_SYSTEM = Linux
	endif
endif

#Getting the computer's processor architecture.
ifeq ($(OPERATING_SYSTEM),Windows)
	ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
		PROCESSOR_ARCHITECTURE = x86_64
	else ifeq ($(PROCESSOR_ARCHITECTURE),ARM64)
		PROCESSOR_ARCHITECTURE = arm64
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
		PROCESSOR_ARCHITECTURE = arm64
	else ifeq ($(_PROCESSOR_ARCHITECTURE),arm)
		PROCESSOR_ARCHITECTURE = arm32
	endif
else
	PROCESSOR_ARCHITECTURE = Universal
endif

################################################################################
#### Build Setup
################################################################################
PROJECT_NAME = Better Sonic The Hedgehog ($(OS)-$(PROCESSOR_ARCHITECTURE))

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

ifeq ($(OPERATING_SYSTEM),Windows)

	ifeq ($(BUILD_TOOLCHAIN),NONE)
		BUILD_TOOLCHAIN = MINGW
	endif

	ifeq ($(BUILD_TOOLCHAIN),MSVC)
		C_COMPILER = cl
	else ifeq ($(BUILD_TOOLCHAIN),LLVM)
			C_COMPILER = clang
	else ifeq ($(BUILD_TOOLCHAIN),MINGW)
		C_COMPILER = gcc
	else
$(error No build toolchain was selected.)
	endif

endif

#Get source files
SOURCE_DIRECTORY = ./Source
ifeq ($(OPERATING_SYSTEM),Windows)
	#SOURCES = $(subst \,/, $(shell dir "$(subst /,\\,$(SOURCE_DIRECTORY))\*.c" /n /b /s))
	SOURCES = $(subst \,/, $(shell forfiles /s /m *.c /c "cmd /c echo @relpath"))
else
	SOURCES = $(sort $(shell find $(SOURCE_DIRECTORY) '*.c'))
endif

OBJECT_FILES = $(subst $(SOURCE_DIRECTORY),$(BUILD_DIRECTORY)/Standard/$(OS)/$(BUILD_TOOLCHAIN)/$(BUILD_ARCHITECTURE),$(SOURCES))

OBJECT_FILES := $(subst .c,.o,$(OBJECT_FILES))


DEPENDENCIES = $(patsubst %.o,%.d,"$(OBJECT_FILES)")

all:
	@echo $(DEPENDENCIES)