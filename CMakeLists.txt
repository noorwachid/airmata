cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AirMata)

add_executable(AirMata
    src/Core/IO/Loop.h
    src/Core/IO/Loop.cpp
    src/Core/IO/Resource.h
    src/Core/IO/Resource.cpp

    src/Core/Event/Event.h
    src/Core/Event/Event.cpp
    src/Core/Event/KeyEvent.h
    src/Core/Event/KeyEvent.cpp

    src/Core/Utility/ByteChecker.h
    src/Core/Utility/ByteChecker.cpp
    src/Core/Utility/EnumBitManipulator.h

    src/Core/UI/Sequence.h

    src/Core/UI/Component/Component.h
    src/Core/UI/Component/Component.cpp
    src/Core/UI/Component/Buffer.h
    src/Core/UI/Component/Buffer.cpp
    src/Core/UI/Component/StatusBar.h
    src/Core/UI/Component/StatusBar.cpp

    src/Core/Container/Array.h
    src/Core/Container/String.h
    src/Core/Container/Function.h
    src/Core/Container/Vector.h
    src/Core/Container/Vector.cpp

    src/Core/ArgumentSolver.h

    src/Core/Context.h

    src/Core/EntryPoint.h
    src/Core/EntryPoint.cpp

	src/main.cpp
)

target_include_directories(AirMata PUBLIC src)
target_include_directories(AirMata PRIVATE /usr/local/include)

set_target_properties(AirMata PROPERTIES OUTPUT_NAME airmata)

# Async IO 
target_link_libraries(AirMata /usr/local/lib/libuv.a)

# Terminal sequence DB parser
target_link_libraries(AirMata /usr/local/lib/libunibilium.a)

