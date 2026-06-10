import shutil
import os

AddOption("--build", dest="build", type="string", nargs=1, action="store", help="Build using debug mode")
AddOption("--linker", dest="linker", type="string", nargs=1, action="store", help="change linker to link with")
AddOption("--compiler", dest="compiler", type="string", nargs=1, action="store", help="change compiler to build with")
AddOption("--asm", dest="asm", type="string", nargs=1, action="store", help="export assembler instruction (to analyze generated assembly code, only works in debug)")

#c and cpp standards
c_std = ["-std=c17"]
cpp_std = ["-std=c++20"]

#Compiler for c
c_Compiler = "gcc"
#Compiler for cpp
cpp_Compiler = "g++"

#Compiler Flags
c_CCFlags = [
        "-O2",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]

#Compiler Flags
cpp_CCFlags = ""

#Dep Flags
Dep_Flags = ["-O2"]

#Linker type
Linker = ["-fuse-ld=bfd"]

#Linker Flags
Link_Flags = ["-pthread"]

#Build path
Build_Path = "build_release"

if GetOption("build") == "debug":
    Build_Path = "build"

    Dep_Flags = [
        "-Og",
        "-g",
        "-ggdb3"]

    c_CCFlags = [
        "-Og",
        "-g",
        "-Wall",
        "-Wpedantic",
        "-Wextra",
        "-ggdb3"]
    
    if GetOption("asm") == "y":
        c_CCFlags += ["-S", "-fverbose-asm"]

elif GetOption("build") == "size":
    Build_Path = "build_size"

    Dep_Flags = ["-Os"]
    
    c_CCFlags = [
        "-Os",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]
elif GetOption("build") == "ex_size":
    Build_Path = "build_ex_size"

    Dep_Flags = ["-Oz"]

    c_CCFlags = [
        "-Oz",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]
elif GetOption("build") == "fast":
    Build_Path = "build_fast"

    Dep_Flags = ["-O3"]

    c_CCFlags = [
        "-O3",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]
elif GetOption("build") == "ex_fast":
    Build_Path = "build_ex_fast"

    Dep_Flags = ["-Ofast"]

    c_CCFlags = [
        "-Ofast",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]

if GetOption("linker") == "mold":
    Linker = ["-fuse-ld=mold"]
elif GetOption("linker") == "lld":
    Linker = ["-fuse-ld=lld"]
elif GetOption("linker") == "gold":
    Linker = ["-fuse-ld=gold"]

if GetOption("compiler") == "clang":
    #Compiler for c
    c_Compiler = "clang"
    #Compiler for cpp
    cpp_Compiler = "clang++"

cpp_CCFlags = c_CCFlags

#Dependency Environment build
c_Dep_Env = Environment(COMPILATIONDB_USE_ABSPATH=True)
c_Dep_Env.Tool('compilation_db')
c_Dep_Env.CompilationDatabase()
c_Dep_Env["LINKFLAGS"] += Link_Flags + Linker
c_Dep_Env["CC"] = c_Compiler
c_Dep_Env["CXX"] = cpp_Compiler
c_Dep_Env["CCFLAGS"] = Dep_Flags + c_std

cpp_Dep_Env = c_Dep_Env.Clone()
cpp_Dep_Env["CCFLAGS"] = Dep_Flags + cpp_std

#Kronos Engine Environment build
Kronos_Env = Environment(COMPILATIONDB_USE_ABSPATH=True)
Kronos_Env.Tool('compilation_db')
Kronos_Env.CompilationDatabase()
Kronos_Env["LINKFLAGS"] += Link_Flags + Linker
Kronos_Env["CC"] = c_Compiler
Kronos_Env["CXX"] = cpp_Compiler
Kronos_Env["CCFLAGS"] = cpp_CCFlags + cpp_std

#Build Dependencies
DepObj = SConscript("Dep/SConstruct", exports = ['c_Dep_Env', 'cpp_Dep_Env'])

#Build source code
SourceObj = SConscript("Source/SConstruct", exports = ["Kronos_Env"])

#Link Dependency Objects and Source Objects to KronosEngine executable
Source = [
    DepObj,
    SourceObj]

#Find path of libraries needed to link
LibPath = [
    "Dep/GLFW/Lib"]

#Libraries the executable needs to link
Libs = [
    "dl",
    "X11",
    "wayland-client",
    "GL",
    "glfw3",
    "assimp"]



#Link All
Kronos_Env.Program(Build_Path + "/KronosEngine", Source, LIBS=Libs, LIBPATH=LibPath)

#Copy needed resource for program to access during runtime
if not os.path.exists(Build_Path + "/Resource"):
    shutil.copytree("./Resource", Build_Path + "/Resource")
else:
    shutil.rmtree(Build_Path + "/Resource")
    shutil.copytree("./Resource", Build_Path + "/Resource")
