cmake_minimum_required(VERSION 3.29)
project(DLLPlaylistForStudents)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DLLPlaylistForStudents
    DLL.cpp
    DLL.hpp
    DNode.hpp
    MainDLL.cpp
    Playlist.cpp
    Playlist.hpp
    Song.cpp
    Song.hpp
        DNode.cpp
        MyListOfSongs.txt
    ShortListofSongs.txt)
