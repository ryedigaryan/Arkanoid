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
set(PROJECT_EXECUTABLES main.cpp Code/H/Geometry/Geometry.h Code/H/Geometry/Vector.h Code/H/Geometry/Point.h Code/H/Geometry/Size.h Code/H/Models/Interfaces/Attacker.h Code/H/Models/Interfaces/GameObject.h Code/H/Models/Interfaces/Mortal.h Code/H/Models/Interfaces/Movable.h Code/H/Models/AllGameObjects.h Code/H/Models/Ball.h Code/H/Models/Brick.h Code/H/Models/Border.h Code/H/Models/Paddle.h Code/CPP/Vector.cpp Code/H/GameStates/State.h Code/H/GameStates/MainMenuState.h Code/H/GameStates/GamingState.h Code/H/GameStates/PausedState.h Code/H/GameStates/LevelEndState.h Code/H/StateMachine.h Code/CPP/StateMachine.cpp Code/H/GameData.h Code/H/Definitions/ModelDefinitions.h Code/H/Interfaces/GameObjectDelegate.h Code/CPP/GameObject.cpp Code/H/Definitions/CommonDefinitions.h Code/H/ArkanoidEngine.h Code/H/ArkanoidDrawer.h Code/H/ArkanoidGameController.h Code/CPP/ArkanoidGameController.cpp Code/CPP/MainMenuState.cpp Code/CPP/PausedState.cpp Code/CPP/GamingState.cpp Code/CPP/LevelEndSatate.cpp Code/H/Interfaces/StateDelegate.h Code/CPP/ArkanoidDrawer.cpp Code/CPP/ArkanoidEngine.cpp)

include_directories("${PROJECT_BINARY_DIR}")
include_directories("${CMAKE_SOURCE_DIR}/Code/H")
include_directories("${CMAKE_SOURCE_DIR}/Resources")
include_directories("${PROJECT_BINARY_DIR}")
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML COMPONENTS audio network graphics window system)
if(SFML_FOUND)
    add_executable(Arcanoid ${PROJECT_EXECUTABLES})
#    target_link_libraries(Arcanoid ${CMAKE_SOURCE_DIR}/SFML/lib/libFLAC.a ${CMAKE_SOURCE_DIR}/SFML/lib/libfreetype.a ${CMAKE_SOURCE_DIR}/SFML/lib/libjpeg.a ${CMAKE_SOURCE_DIR}/SFML/lib/libogg.a ${CMAKE_SOURCE_DIR}/SFML/lib/libopenal32.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-audio-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-graphics-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-main.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-network-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-system-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libsfml-window-s.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbis.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbisenc.a ${CMAKE_SOURCE_DIR}/SFML/lib/libvorbisfile.a)
    target_link_libraries(Arcanoid ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
include(InstallRequiredSystemLibraries)