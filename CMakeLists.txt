cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AirMata)

add_executable(AirMata
    src/Core/IO/Loop.h
    src/Core/IO/Loop.cpp
    src/Core/IO/Resource.h
    src/Core/IO/Resource.cpp
    src/Core/IO/Action.h
    src/Core/IO/Action.cpp

    src/Core/Event/Event.h
    src/Core/Event/Event.cpp
    src/Core/Event/KeyEvent.h
    src/Core/Event/KeyEvent.cpp
    src/Core/Event/MouseEvent.h
    src/Core/Event/MouseEvent.cpp
    src/Core/Event/EventSystem.h

    src/Core/Utility/ByteChecker.h
    src/Core/Utility/ByteChecker.cpp
    src/Core/Utility/EnumBitManipulator.h

    src/Core/UI/Sequence.h

    src/Core/UI/Object/Object.h
    src/Core/UI/Object/Object.cpp
    src/Core/UI/Object/Document.h
    src/Core/UI/Object/Document.cpp

    src/Core/UI/Tree.h
    src/Core/UI/Tree.cpp
    src/Core/UI/Sequence.h
    src/Core/UI/InputSystem.h
    src/Core/UI/InputSystem.cpp

    src/Core/Container/Array.h
    src/Core/Container/String.h
    src/Core/Container/Function.h
    src/Core/Container/Vector.h
    src/Core/Container/Vector.cpp
    src/Core/Container/HashTable.h

    src/Core/ArgumentSolver.h
    src/Core/ArgumentSolver.cpp

    src/Core/Mode.h
    src/Core/Mode.cpp

    src/Core/Program.h
    src/Core/Program.cpp

	src/main.cpp
)

target_include_directories(AirMata PUBLIC src)
target_include_directories(AirMata PRIVATE /usr/local/include)

set_target_properties(AirMata PROPERTIES OUTPUT_NAME airmata)

# Async IO 
target_link_libraries(AirMata /usr/local/lib/libuv.a)

# Terminal sequence DB parser
target_link_libraries(AirMata /usr/local/lib/libunibilium.a)

