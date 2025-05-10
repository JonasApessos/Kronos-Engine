import shutil
import os

AddOption("--build", dest="build", type="string", nargs=1, action="store", help="Build using debug mode")

print(GetOption("build"))

#c and cpp standards
c_std = ["-std=c17"]
cpp_std = ["-std=c++20"]

#Compiler for c
c_Compiler = "gcc"

#Compiler Flags
c_CCFlags = "";
cpp_CCFlags = "";

if GetOption("build") == "debug":
    c_CCFlags = [
        "-Og",
        "-g",
        "-Wall",
        "-Wpedantic",
        "-Wextra",
        "-ggdb3"]
else:
    c_CCFlags = [
        "-O2",
        "-Wall",
        "-Wpedantic",
        "-Wextra"]

#Compiler for cpp
cpp_Compiler = "g++"
#compiler Flags
cpp_CCFlags = c_CCFlags

#Linker type
Linker = ["-fuse-ld=gold"]

#Linker Flags
Link_Flags = ["-pthread"]

#Dependency's Environment build
c_Dep_Env = Environment()
c_Dep_Env["LINKFLAGS"] += Link_Flags + Linker
c_Dep_Env["CC"] = c_Compiler
c_Dep_Env["CXX"] = cpp_Compiler
c_Dep_Env["CCFLAGS"] = ["-O2"] + c_std

cpp_Dep_Env = c_Dep_Env.Clone()
cpp_Dep_Env["CCFLAGS"] = ["-O2"] + cpp_std

#Kronos Engine Environment build
Kronos_Env = Environment()
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
    "Dep/GLFW/Lib",
    "/usr/lib/x86_64-linux-gnu"]

#Libraries the executable needs to link
Libs = [
    "dl",
    "GL",
    "X11",
    "wayland-client",
    "glfw3",
    "assimp"]

if GetOption("build") == "debug":
    #Link All
    Kronos_Env.Program("build/KronosEngine", Source, LIBS=Libs, LIBPATH=LibPath)

    #Copy needed resource for program too access during runtime
    if not os.path.exists("build/Resource"):
        shutil.copytree("./Resource", "build/Resource")
else:
    #Link All
    Kronos_Env.Program("build_release/KronosEngine", Source, LIBS=Libs, LIBPATH=LibPath)

    #Copy needed resource for program too access during runtime
    if not os.path.exists("build_release/Resource"):
        shutil.copytree("./Resource", "build_release/Resource")