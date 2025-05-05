

cmake_minimum_required(VERSION 3.22)
project(MCXB1Netplay)
set (CMAKE_CXX_STANDARD 20)
# Add the dependency (lib/some_library)
add_subdirectory(lib/Lantern)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    Lantern
)


set(SRC_FILES
    src/framework.h
    src/LanternMain.cpp
    src/LanternMain.h
    src/McXb1NetplayMod.cpp
    src/McXb1NetplayMod.h
    src/Hooks/OutputStream.cpp
    src/Hooks/OutputStream.h
    src/Hooks/Socket.cpp
    src/Hooks/Socket.h
    src/Hooks/SocketOutputStreamLocal.cpp
    src/Hooks/SocketOutputStreamLocal.h

    src/pch.cpp
    src/pch.h
)

# DLL target
add_library(MCXB1Netplay SHARED
    ${SRC_FILES}
)

# Link the dependent library (assume it defines a target called 'SomeLibrary')
target_link_libraries(MCXB1Netplay PRIVATE Lantern ws2_32)
