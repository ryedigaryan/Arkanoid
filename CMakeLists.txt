cmake_minimum_required(VERSION 2.6)
project(Arcanoid)

#C++ standard
set(CMAKE_CXX_STANDARD 17)
#the SFML's FIndSFML.cmake file path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
#root SFML file is not in standard path
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
#statick linking

set(SFML_STATIC_LIBRARIES TRUE)
#files which must be executed
set(PROJECT_EXECUTABLES main.cpp Code/H/Geometry/Geometry.h Code/H/Geometry/Vector.h Code/H/Geometry/Point.h Code/H/Geometry/Size.h Code/H/Interfaces/ArcanoidGameEngineDelegate.h Code/H/Interfaces/ArcanoidGameDrawerDelegate.h Code/H/Interfaces/GameObjectDelegate.h Code/H/Models/Interfaces/Attacker.h Code/H/Models/Interfaces/GameObject.h Code/H/Models/Interfaces/Mortal.h Code/H/Models/Interfaces/Movable.h Code/H/Models/AllGameObjects.h Code/H/Models/Ball.h Code/H/Models/Brick.h Code/H/Models/Border.h Code/H/Models/Paddle.h Code/H/ArcanoidGameDrawer.h Code/H/ArcanoidGameEngine.h Code/H/ArcanoidGameManager.h Code/H/Definitions.h Code/CPP/ArcanoidGameDrawer.cpp Code/CPP/ArcanoidGameEngine.cpp Code/CPP/ArcanoidGameManager.cpp Code/CPP/GameObject.cpp Code/CPP/Vector.cpp Code/CPP/Definitions.cpp)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/Code/H")
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML COMPONENTS audio network graphics window system)
if(SFML_FOUND)
    add_executable(Arcanoid ${PROJECT_EXECUTABLES})
#    target_link_libraries(Arcanoid ${CMAKE_SOURCE_DIR}/SFML/lib/libFLAC.a ${CMAKE_SOURCE_DIR}/SFML/lib/libfreetype.a ${CMAKE_SOURCE_DIR}/SFML/lib/libjpeg.a ${CMAKE_SOURCE_DIR}/SFML/lib/libogg.a ${CMAKE_SOURCE_DIR}/SFML/lib/libopenal32.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-audio-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-graphics-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-main.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-network-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-system-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-window-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbis.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbisenc.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbisfile.a)
    target_link_libraries(Arcanoid ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
include(InstallRequiredSystemLibraries)