#!/usr/bin/env python3.10

################################################################################
#### Functions
################################################################################
def get_operating_system() -> str:
    import platform
    return platform.system()

def get_processor_architechure() -> str:
    import platform
    return platform.machine()

def get_working_directory() -> str:
    from pathlib import Path
    from os import chdir
    DIR = Path(__file__).parent.absolute()
    #DIR = f'{DIR}'.replace('\\','/')
    chdir(DIR)
    return DIR

def path_separator() -> str:
    if get_operating_system().lower() == "windows":
        return "\\"
    return "/"

def get_cli_arg(index: int) -> str | None:
    from sys import argv
    if index+1 > len(argv):
        return None
    else:
        return argv[int(index)]
    

def copy_file(file: str, desination: str):
    import shutil, os
    if not os.path.isfile(str(file)):
        raise FileNotFoundError
    
    if not os.path.exists(str(desination)):
        raise Exception("That path or directory doesn't exist.")
    
    shutil.copy(file, desination)

def remove_directory_tree(directory: str):
    import shutil, os
    if not os.path.exists(str(directory)): raise Exception("That path or directory doesn't exist.")
    shutil.rmtree(str(directory))
    del shutil

def create_directory(directory: str):
    import os
    os.makedirs(directory)
    del os

def create_directory_safe(directory: str):
    import os
    if os.path.exists(str(directory)):
        raise Exception("That path or directory already exists.")
    create_directory(directory)
    del os
    
import os
import fnmatch


################################################################################
#### Constants
################################################################################  
BUILD_TOOLCHAIN_MINGW:str = "MINGW"
BUILD_TOOLCHAIN_LLVM:str = "LLVM"
BUILD_TOOLCHAIN_MSVC:str = "MSVC"
BUILD_TOOLCHAIN_GCC:str = "GCC"
BUILD_MODE_RELEASE: str = "RELEASE"
BUILD_MODE_DEBUG: str = "DEBUG"
ACTION_COMPILE:str = "COMPILE"
ACTION_LINK:str = "LINK"
ACTION_BUILD:str = "BUILD"
ACTION_HELP:str = "HELP"
ACTION_VARS:str = "VARS"
PROC_ARCHTITECTURE_32: list[str] = ["i386", "i686", "x86", "ppc", "arm", "ppcle"]
PROC_ARCHTITECTURE_64: list[str] = ["x86_64", "aarch64_be" "aarch64", "armv8b", "armv8l", "ppc64", "ppc64le", "ia64", "arm64", "amd64"]
    
################################################################################
#### Project Setup
################################################################################
PROJECT_NAME:str = f"Better Sonic The Hedgehog ({get_operating_system()}-{get_processor_architechure()})"

SOURCE_DIRECTORY: str = f"{get_working_directory()}{path_separator()}Source"
ACTION: str = ""
BUILD_MODE: str = BUILD_MODE_RELEASE
################################################################################
#### Command Line Arguments
################################################################################
BUILD_ARCHITECTURE: str = ""
if get_cli_arg(1) != None:
    ACTION = get_cli_arg(1).upper()

if get_cli_arg(2) != None:
    if get_cli_arg(2).upper() == BUILD_MODE_RELEASE or get_cli_arg(2).upper() == BUILD_MODE_DEBUG:
        BUILD_MODE = get_cli_arg(2).capitalize()
    else:
        exit("Script error. Please select a valid build mode. [Release or Debug]")

if get_cli_arg(3) != None:
    if get_cli_arg(3).lower() in PROC_ARCHTITECTURE_32 or get_cli_arg(3).lower() in PROC_ARCHTITECTURE_64:
        BUILD_ARCHITECTURE = get_cli_arg(3).lower()
    else:
        exit(f"Script error. Please select a valid build architecture.\nList of possible processor architectures:\n{PROC_ARCHTITECTURE_32}\n{PROC_ARCHTITECTURE_64}")

################################################################################
#### Build Setup
################################################################################
EXECUTABLE: str = f"{PROJECT_NAME}"
BUILD_TOOLCHAIN: str = ""
if BUILD_ARCHITECTURE == "":
    BUILD_ARCHITECTURE = get_processor_architechure()
################################################################################
#### Compiler Setup
################################################################################
C_COMPILER: str = ""
SOURCES: list[str] = []
SOURCE_NAMES: list[str] = []
OBJECT_FILES: list[str] = []
OBJECT_FILE_NAMES: list[str] = []
OBJECT_FILE_DIRS: list[str] = []

#
C_FLAGS: list[str] = [
    "-std=c99",
    "-Wall",
    "-Wpedantic",
    "-Wextra"
]

C_PREPROCESSOR_FLAGS: list[str] = [
    "-MMD",
    "-MP"
]

LD_LIBRARIES: list[str] = []
LD_FLAGS: list[str] = []

#Operating system specific settings.
match get_operating_system().lower():

    case "windows":
        if BUILD_TOOLCHAIN == "":
            BUILD_TOOLCHAIN = BUILD_TOOLCHAIN_MINGW
        
        if C_COMPILER == "":
            if BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_MSVC:
                C_COMPILER = "cl.exe"
                LD_FLAGS.append("-static-libstdc++")
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_MINGW:
                C_COMPILER = "gcc.exe"
                LD_FLAGS.append("-static-libgcc")
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_LLVM:
                C_COMPILER = "clang.exe"
                LD_FLAGS.append("-static-libstdc++")


        
        if BUILD_MODE == BUILD_MODE_RELEASE:
            LD_FLAGS.append("-mwindows")
        
        if BUILD_ARCHITECTURE.lower() in ["amd64", "ia64"]:
            print(BUILD_MODE)
            LD_LIBRARIES += ["S"] if BUILD_MODE.capitalize() == BUILD_MODE_RELEASE else ["l"]

        LD_LIBRARIES += ["-lopengl32", "-lgdi32", "-lwinmm"]

    case "darwin":
        if BUILD_TOOLCHAIN == "":
            BUILD_TOOLCHAIN = BUILD_TOOLCHAIN_LLVM
        
        if C_COMPILER == "":
            if BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_GCC:
                C_COMPILER = "gcc"
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_LLVM:
                C_COMPILER = "clang"

        LD_LIBRARIES += ["-framework IOKit", "-framework Cocoa", "-framework OpenGL"]
        if BUILD_ARCHITECTURE.lower() == "x86_64": 
            LD_LIBRARIES += [f'"{get_working_directory()}{path_separator()}Raylib/libraylib-macos-x86_64.a"'] if BUILD_MODE == BUILD_MODE_RELEASE else [f'"{get_working_directory()}{path_separator()}Raylib/libraylib-macos-x86_64-d.a"']

    case "linux":
        if BUILD_TOOLCHAIN == "":
            BUILD_TOOLCHAIN = BUILD_TOOLCHAIN_GCC
        
        if C_COMPILER == "":
            if BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_GCC:
                C_COMPILER = "gcc"
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_LLVM:
                C_COMPILER = "clang"

    case _:
        exit("Build error. Your operating system is not supported.")
        
BUILD_DIRECTORY: str = f"{get_working_directory()}{path_separator()}Build{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}"
BINARY_DIRECTORY: str = f"{get_working_directory()}{path_separator()}Binary{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}"

#Finding all the source files.
for root, dirnames, filenames in os.walk(SOURCE_DIRECTORY):
    for filename in fnmatch.filter(filenames, '*.c'):
        SOURCES.append(os.path.join(root, filename))
        SOURCE_NAMES.append(filename)



INCLUDE_DIRECTORIES: list[str] = [
    f"-I{get_working_directory()}{path_separator()}Raylib{path_separator()}include",
    f"-I{get_working_directory()}{path_separator()}Source"
]

if get_operating_system().lower != "darwin":
    if get_operating_system().lower == "windows": EXECUTABLE += ".exe"
    
    if BUILD_ARCHITECTURE.lower() in PROC_ARCHTITECTURE_32:
        C_FLAGS.append("-m32")
    elif BUILD_ARCHITECTURE.lower() in PROC_ARCHTITECTURE_64:
        C_FLAGS.append("-m64")
    else:
        exit("Build Error. No vaild build architecture was set.")


for source in SOURCES:
    OBJECT_FILES.append(source.replace(SOURCE_DIRECTORY, BUILD_DIRECTORY).replace(".c", ".o"))

for srcn in SOURCE_NAMES:
    OBJECT_FILE_NAMES.append(srcn.replace(".c", ".o"))

for n, (obj, objn) in enumerate(zip(OBJECT_FILES, OBJECT_FILE_NAMES)):
    OBJECT_FILE_DIRS.append(obj.replace(objn, ""))

################################################################################
#### Actions
################################################################################
match ACTION.lower():
    case "help":
        print("""
Usage: python(x.xx) ./Build [Action] [Build Mode] [Build Architecture] [Build Toolchain] [Intermediate Build Directory] [Binary Directory] ...
        """)

    case "vars":
        print(f"""
Project Name:  {PROJECT_NAME}
Operating System: {get_operating_system()}
Processor Architecture: {get_processor_architechure()}
Project Directory: {get_working_directory()}
Build Directory: {BUILD_DIRECTORY}
Binary Directory: {BINARY_DIRECTORY}
Build Architecture: {BUILD_ARCHITECTURE}


>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
C Compiler: {C_COMPILER}

Source Files: {SOURCES}


Include Files: {INCLUDE_DIRECTORIES}


Compiler Flags: {C_FLAGS}


Compiler Pre-Processor Flags: {C_PREPROCESSOR_FLAGS}

Linker Flags: {LD_FLAGS}


Linker Libraries: {LD_LIBRARIES}
        """)

    case "compile":
        _cflags: str = ""
        for flag in C_FLAGS: _cflags += f" {flag}"
        _cppflags: str = ""
        for flag in C_PREPROCESSOR_FLAGS: _cppflags += f" {flag}"
        _includes: str = ""
        for dir in INCLUDE_DIRECTORIES: _includes += f' "{dir}"'

        for objd in OBJECT_FILE_DIRS:
            if not os.path.exists(str(objd)):
                os.makedirs(str(objd))
            else:
                for root, dirnames, filenames in os.walk(SOURCE_DIRECTORY):
                    for filename in fnmatch.filter(filenames, '*.o'):
                        if (os.path.isfile(filename)):
                            os.remove(filename)

        for n, (src, obj, objd) in enumerate(zip(SOURCES, OBJECT_FILES, OBJECT_FILE_DIRS)):
            os.system(f'{C_COMPILER} {_cppflags} {_cflags} {_includes} -c "{src}" -o "{obj}"')


    case "link":
        _ldflags: str = ""
        for flag in LD_FLAGS: _ldflags += f" {flag}"
        _ldlibs: str = ""
        for lib in LD_LIBRARIES: _ldlibs += f" {lib}"

        _objs: str  = ""
        for obj in OBJECT_FILES:
            _objs += f' "{obj}"' 

        if not os.path.exists(BINARY_DIRECTORY):
            os.makedirs(BINARY_DIRECTORY)
        else:
            remove_directory_tree(BINARY_DIRECTORY)
            os.makedirs(BINARY_DIRECTORY)

        print(f"{_ldlibs}")
        #os.system(f'{C_COMPILER} {_ldlibs} {_ldflags} {_objs} -o "{BINARY_DIRECTORY}{path_separator()}{EXECUTABLE}"')
    
    case "bundle":
        if get_operating_system().lower() == "windows":
            exit("Can't bundle application on Windows. " + 'Use "package" to package the executable into a zip.')

        if BUILD_MODE == BUILD_MODE_RELEASE: exit("There is no point to bundling a debug binary.")

        if get_operating_system().lower() == "darwin":
            if os.path.exists(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app"): remove_directory_tree(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app")
            os.makedirs(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app")
            os.mkdir(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app{path_separator()}Contents")
            os.mkdir(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app{path_separator()}Contents{path_separator()}MacOS")
            copy_file(f"{BINARY_DIRECTORY}{path_separator()}{EXECUTABLE}", f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app{path_separator()}Contents{path_separator()}MacOS")
            with open(f"{BINARY_DIRECTORY}{path_separator()}{PROJECT_NAME}.app{path_separator()}Contents{path_separator()}Info.plist", "w") as plist:
                plist.write(
f"""
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>NSHumanReadableCopyright</key>
	<string>Open Source (FOSS), No Copyright</string>
	<key>CFBundleName</key>
	<string>Better Sonic The Hedgehog (Darwin)</string>
	<key>CFBundleIconFile</key>
	<string></string>
	<key>LSApplicationCategoryType</key>
	<string>public.app-category.games</string>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleExecutable</key>
	<string>{EXECUTABLE}</string>
	<key>CFBundleIdentifier</key>
	<string>org.github.bettersth</string>
	<key>CFBundleShortVersionString</key>
	<string>100</string>
	<key>CFBundleVersion</key>
	<string>1.0.0</string>
	<key>NSHighResolutionCapable</key>
	<true/>
</dict>
</plist>    
""")

    case "clean":
        if os.path.exists(BUILD_DIRECTORY.replace(f"{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}", "")):
            remove_directory_tree(BUILD_DIRECTORY.replace(f"{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}", ""))

        if os.path.exists(BINARY_DIRECTORY.replace(f"{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}", "")):
            remove_directory_tree(BINARY_DIRECTORY.replace(f"{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN.capitalize()}{path_separator()}{BUILD_ARCHITECTURE.capitalize()}{path_separator()}{BUILD_MODE.capitalize()}", ""))
    
    case "run":
        if os.path.exists(f'"{BINARY_DIRECTORY}{path_separator()}{EXECUTABLE}"'):
            os.system(f'"{BINARY_DIRECTORY}{path_separator()}{EXECUTABLE}"')
        else: exit("The executable doesn't exist.")

    case _:
        exit('Please select a valid action. Type "help" for more information.')