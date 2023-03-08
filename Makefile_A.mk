################################################################################
#### Pre-Setup
################################################################################

#Get operating system.
ifeq ($(OS),Windows_NT)
	os = windows
else
	kernel_type = $(shell uname -s)
	ifeq ($(kernel_type),Darwin)
		os = macos
	else ifeq ($(kernel_type),Linux)
		os = linux
	endif
endif

#get processor architechure.
processor_architecture = universal
ifeq ($(os),windows)
	ifeq ($(win32),1)
		processor_architecture = win32
	else
		processor_architecture = win64
	endif
else
	_processor_architecture = $(shell uname -m)
	ifeq ($(os),linux)
		ifeq ($(_processor_architecture),x86_64)
			processor_architecture = amd64
		else ifeq ($(os),i386)
			processor_architecture = i686
		endif
	endif
endif

################################################################################
#### Build Setup
################################################################################
project_name = Better-Sonic-The-Hedgehog

assets_directory = "./assets"
assets_directory_win = $(subst /,\\,$(assets_directory))
build_directory = ./build
binary_directory = ./binary
binary_directory_win = $(subst /,\\,$(binary_directory))

include_directories = \
	-I "./Raylib/include" \
	-I "./source" \
	-I "./source/entities" \

build_architechure := $(processor_architecture)
build_type := release



################################################################################
#### Compiler Setup
################################################################################

#Which compiler?
ifeq ($(os),windows)
	windows_c_compiler_gcc = gcc
	windows_c_compiler_msvc = clang
else ifeq ($(os),macos)
	macos_c_compiler = clang
else ifeq ($(os),linux)
	linux_c_compiler = gcc
endif

ifeq ($(os),windows)
	build_toolchain := msvc #!!Windows only!!
else ifeq ($(os),macos)
	ifeq ($(macos_c_compiler),clang)
		build_toolchain = llvm
	else ifeq ($(macos_c_compiler),gcc)
		build_toolchain = gcc 
	endif
else ifeq ($(os),linux)
	ifeq ($(linux_c_compiler),clang)
		build_toolchain = llvm
	else ifeq ($(linux_c_compiler),gcc)
		build_toolchain = gcc 
	endif
endif

c_flags = \
	-std=c17 \
	-Wall \
	-Wpedantic \
	-Wextra \

c_pre_processor_flags = \
	-MMD \
	-MP \

#Get sources
source_directory = ./source
ifeq ($(os),windows)
	rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
	sources = $(call rwildcard,$(source_directory),*.c)
else
	sources = $(sort $(shell find $(source_directory) -name '*.c'))
endif

################################################################################
#### End
################################################################################
executable_file = $(project_name)
ifeq ($(os),windows)
	executable_file = $(project_name).exe
	ifeq ($(build_architechure),win32)
		c_flags = -m32
	else ifeq ($(build_architechure),win64)
		c_flags = -m64
	endif
else ifeq ($(os),linux)
	ifeq ($(build_architechure),i686)
		c_flags = -m32
	else ifeq ($(build_architechure),amd64)
		c_flags = -m64
	endif
else ifeq ($(os),macos)
	c_flags += -m64
endif

ifeq ($(build_type),release)
	c_flags += -O3
	c_pre_processor_flags += -DNDEBUG
else ifeq ($(build_type),debug)
	c_flags += -O0 -g
	c_pre_processor_flags += -D_DEBUG
endif

object_files = $(sources:$(source_directory)/%.c=$(build_directory)/$(os)/$(build_architechure)/$(build_toolchain)/$(build_type)/%.o)
dependencies = $(object_files:.o=.d)

################################################################################
#### Targets
################################################################################
build: $(binary_directory)/$(os)/$(build_architechure)/$(build_toolchain)/$(build_type)/$(executable_file)
clean: $(os)_clean
run: $(os)_$(build_architechure)_$(build_toolchain)_$(build_type)_run
################################################################################
#MacOS

#Linking the mach-o object files into an executable binary within an app bundle.
$(binary_directory)/macos/universal/llvm/release/$(executable_file): $(object_files)
	@echo "Linking object files for mach-o universal binary and turning it into an app bundle."

# Linking the binary
	@[ ! -d "$(@D)" ] && mkdir -p "$(@D)" || echo "$(@D) already exists."
	@export MACOSX_DEPLOYMENT_TARGET=10.9
	@$(macos_c_compiler) $^ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -L"./Raylib" -lraylib_macos_universal -o  $@

# Making the app bundle.
	@[ ! -d "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app" ] && mkdir -p "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app"

# Move the binary.
	@[ ! -d "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/MacOS" ] && mkdir -p "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/MacOS"
	@mv "$(@D)/$(executable_file)" "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/MacOS"

# Copy the resources,
	@[ ! -d "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources" ] && mkdir -p "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources"
	@cp -r "$(assets_directory)/game/." "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources"

# - this also includes the property list.
	@touch "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Info.plist"
	@cat "./Info.plist" > "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Info.plist"

# Clean up.
	@[ -d "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Github" ] && rm -rf "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Github" || echo "'$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Github' doesn't exist."
	@[ -d "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Game/Source" ] && rm -rf "$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Game/Source" || echo "'$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/Resources/Game/Source' doesn't exist."
	

#Linking the mach-o object files into an executable binary.
$(binary_directory)/macos/universal/llvm/debug/$(executable_file): $(object_files)
	@echo "Linking object files for mach-o universal binary."
	@[ ! -d "$(@D)" ] && mkdir -p "$(@D)" || echo "$(@D) already exists."
	@export MACOSX_DEPLOYMENT_TARGET=10.9
	@$(macos_c_compiler) $^ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -L"./Raylib" -lraylib_macos_universal -o $@
	@[ ! -d "$(binary_directory)/macos/universal/llvm/debug/resources" ] && mkdir -p "$(binary_directory)/macos/universal/llvm/debug/resources"
	@cp -r "$(assets_directory)/game/." "$(binary_directory)/macos/universal/llvm/debug/resources"



#Compiling mach-o object files.
$(build_directory)/macos/universal/$(build_toolchain)/$(build_type)/%.o: $(source_directory)/%.c
	@echo "Compiling: $< with $(build_toolchain) toolchain on univeral architechure for macos"
	@[ ! -d "$(@D)" ] && mkdir -p "$(@D)" || echo "$(@D) already exists."
	$(macos_c_compiler) $(c_pre_processor_flags) $(include_directories) $(c_flags) -c $< -o $@
################################################################################
#Windows

#Compiling windows object files.
$(build_directory)/windows/win64/msvc/$(build_type)/%.o: $(source_directory)/%.c
	@echo Compiling $< with @echo "Compiling: $< with msvc toolchain on win64 architechure for windows in $(build_type) mode."
	@IF exists "$(@D)" (echo '$(@D) already exists.') ELSE {mkdir "$(@D)"}
	@$(windows_c_compiler_msvc) $(c_pre_processor_flags)  $(c_flags) -c $< -o $@

################################################################################



-include $(dependencies)



macos_universal_llvm_release_run:
	@$(binary_directory)/macos/universal/$(build_toolchain)/release/$(project_name).app/Contents/MacOS/$(executable_file)

macos_universal_llvm_debug_run:
	@$(binary_directory)/macos/universal/$(build_toolchain)/debug/$(project_name)

macos_clean:
	@[ -d "$(build_directory)" ] && rm -rf "$(build_directory)" || echo "$(build_directory) doesn't exist."
	@[ -d "$(binary_directory)" ] && rm -rf "$(binary_directory)" || echo "$(binary_directory) doesn't exist."

windows_clean:
	@echo Cool!