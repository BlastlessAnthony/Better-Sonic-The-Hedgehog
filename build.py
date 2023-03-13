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

match get_operating_system().lower():

    case "windows":
        if BUILD_TOOLCHAIN == "":
            BUILD_TOOLCHAIN = BUILD_TOOLCHAIN_MINGW
        
        if C_COMPILER == "":
            if BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_MSVC:
                C_COMPILER = "cl.exe"
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_MINGW:
                C_COMPILER = "gcc.exe"
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_LLVM:
                C_COMPILER = "clang.exe"

    case "mac os x":
        if BUILD_TOOLCHAIN == "":
            BUILD_TOOLCHAIN = BUILD_TOOLCHAIN_LLVM
        
        if C_COMPILER == "":
            if BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_GCC:
                C_COMPILER = "gcc"
            elif BUILD_TOOLCHAIN == BUILD_TOOLCHAIN_LLVM:
                C_COMPILER = "clang"

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
        
SOURCES: list[str] = []
for root, dirnames, filenames in os.walk(SOURCE_DIRECTORY):
    for filename in fnmatch.filter(filenames, '*.c'):
        SOURCES.append(os.path.join(root, filename))

BUILD_DIRECTORY: str = f"{get_working_directory()}{path_separator()}Build{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN}{path_separator()}{BUILD_ARCHITECTURE}{path_separator()}{BUILD_MODE}"

BINARY_DIRECTORY: str = f"{get_working_directory()}{path_separator()}Binary{path_separator()}{get_operating_system()}{path_separator()}{BUILD_TOOLCHAIN}{path_separator()}{BUILD_ARCHITECTURE}{path_separator()}{BUILD_MODE}"

C_FLAGS: list[str] = [
    "-std=c17",
    "-Wall",
    "-Wpedantic",
    "-Wextra"
]

C_PREPROCESSOR_FLAGS: list[str] = [
    "-MMD",
    "-MP"
]

INCLUDE_DIRECTORIES: list[str] = [
    f"{get_working_directory()}{path_separator()}Raylib{path_separator()}include",
    f"{get_working_directory()}{path_separator()}Source"
]

if get_operating_system().lower != "mac os x":
    if get_operating_system().lower == "windows": EXECUTABLE += ".exe"
    
    if BUILD_ARCHITECTURE.lower() in PROC_ARCHTITECTURE_32:
        C_FLAGS.append("-m32")
    elif BUILD_ARCHITECTURE.lower() in PROC_ARCHTITECTURE_64:
        C_FLAGS.append("-m64")
    else:
        exit("Build Error. No vaild build architecture was set.")

OBJECT_FILES: list[str] = []
for source in SOURCES:
    OBJECT_FILES.append(source.replace(SOURCE_DIRECTORY, BUILD_DIRECTORY).replace(".c", ".o"))

OBJECT_FILE_DEPENDENCIES: list[str] = []
for object_file in OBJECT_FILES:
    OBJECT_FILE_DEPENDENCIES.append(object_file.replace(".o", ".d"))
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


Source Files: {SOURCES}


Include Files: {INCLUDE_DIRECTORIES}


Compiler Flags: {C_FLAGS}


Compiler Pre-Processor Flags: {C_PREPROCESSOR_FLAGS}
        """)

    case "compile":
        ...

    case _:
        exit("No.")