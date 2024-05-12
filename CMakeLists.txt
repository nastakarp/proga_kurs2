cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp
        Util.cpp
        model/node/StringNode.cpp
        model/node/StringNode.h
        model/list/StringList.cpp
        model/list/StringList.h
        model/node/IntNode.cpp
        model/node/IntNode.h
        model/list/IntList.cpp
        model/list/IntList.h
        model/core/TeamStat.cpp
        model/node/TeamStatNode.cpp
        model/list/TeamStatList.h
        model/list/TeamStatList.cpp
        model/core/Player.cpp
        model/list/PlayerList.cpp
        model/node/PlayerNode.cpp
        Functional.cpp
        Functional.h)
