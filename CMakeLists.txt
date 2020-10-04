cmake_minimum_required(VERSION 3.17)
project(AssaultCubeInternalHack)

set(CMAKE_CXX_STANDARD 14)

include_directories(AssaultCubeInternalHack)
include_directories(AssaultCubeInternalHack/Debug)
include_directories(AssaultCubeInternalHack/Release)

add_executable(AssaultCubeInternalHack
        AssaultCubeInternalHack/Debug/AssaultCubeInternalHack.pch
        AssaultCubeInternalHack/Release/AssaultCubeInternalHack.pch
        AssaultCubeInternalHack/dllmain.cpp
        AssaultCubeInternalHack/framework.h
        AssaultCubeInternalHack/pch.cpp
        AssaultCubeInternalHack/pch.h
        AssaultCubeInternalHack/reclass.h
        AssaultCubeInternalHack/resource.h
        AssaultCubeInternalHack/util.cpp
        AssaultCubeInternalHack/util.h)
