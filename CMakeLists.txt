cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AirMata)

add_executable(AirMata
    src/Core/IO/Loop.hpp
    src/Core/IO/Loop.cpp
    src/Core/IO/Resource.hpp
    src/Core/IO/Resource.cpp

    src/Core/Event/Event.hpp
    src/Core/Event/Event.cpp
    src/Core/Event/KeyEvent.hpp
    src/Core/Event/KeyEvent.cpp

    src/Core/Utility/ByteChecker.hpp
    src/Core/Utility/ByteChecker.cpp
    src/Core/Utility/EnumBitManipulator.hpp

    src/Core/UI/Sequence.hpp

    src/Core/UI/Component/Component.hpp
    src/Core/UI/Component/Component.cpp
    src/Core/UI/Component/Buffer.hpp
    src/Core/UI/Component/Buffer.cpp
    src/Core/UI/Component/StatusBar.hpp
    src/Core/UI/Component/StatusBar.cpp

    src/Core/Container/Array.hpp
    src/Core/Container/String.hpp
    src/Core/Container/Function.hpp
    src/Core/Container/Vector.hpp
    src/Core/Container/Vector.cpp
    src/Core/Container/HashTable.hpp

    src/Core/ArgumentSolver.hpp
    src/Core/ArgumentSolver.cpp

    src/Core/Context.hpp

    src/Core/EntryPoint.hpp
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

