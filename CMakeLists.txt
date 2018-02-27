cmake_minimum_required(VERSION 2.6)
project(Arcanoid)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/SFML/include)
link_directories(${CMAKE_SOURCE_DIR}/SFML/lib)

add_executable(Arcanoid main.cpp Code/H/Geometry/Geometry.h Code/H/Geometry/Vector.h Code/H/Geometry/Point.h Code/H/Geometry/Size.h Code/H/Interfaces/ArcanoidGameEngineDelegate.h Code/H/Interfaces/ArcanoidGameDrawerDelegate.h Code/H/Interfaces/GameObjectDelegate.h Code/H/Models/Interfaces/Attacker.h Code/H/Models/Interfaces/GameObject.h Code/H/Models/Interfaces/Mortal.h Code/H/Models/Interfaces/Movable.h Code/H/Models/AllGameObjects.h Code/H/Models/Ball.h Code/H/Models/Brick.h Code/H/Models/Border.h Code/H/Models/Paddle.h Code/H/ArcanoidGameDrawer.h Code/H/ArcanoidGameEngine.h Code/H/ArcanoidGameManager.h Code/H/Definitions.h Code/CPP/ArcanoidGameDrawer.cpp Code/CPP/ArcanoidGameEngine.cpp Code/CPP/ArcanoidGameManager.cpp Code/CPP/GameObject.cpp Code/CPP/Vector.cpp)

target_link_libraries(Arcanoid ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
###################
cmake_minimum_required(VERSION 3.6)
project(Arcanoid)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arcanoid main.cpp Code/H/Geometry/Geometry.h Code/H/Geometry/Vector.h Code/H/Geometry/Point.h Code/H/Geometry/Size.h Code/H/Interfaces/ArcanoidGameEngineDelegate.h Code/H/Interfaces/ArcanoidGameDrawerDelegate.h Code/H/Interfaces/GameObjectDelegate.h Code/H/Models/Interfaces/Attacker.h Code/H/Models/Interfaces/GameObject.h Code/H/Models/Interfaces/Mortal.h Code/H/Models/Interfaces/Movable.h Code/H/Models/AllGameObjects.h Code/H/Models/Ball.h Code/H/Models/Brick.h Code/H/Models/Border.h Code/H/Models/Paddle.h Code/H/ArcanoidGameDrawer.h Code/H/ArcanoidGameEngine.h Code/H/ArcanoidGameManager.h Code/H/Definitions.h Code/CPP/ArcanoidGameDrawer.cpp Code/CPP/ArcanoidGameEngine.cpp Code/CPP/ArcanoidGameManager.cpp Code/CPP/GameObject.cpp Code/CPP/Vector.cpp)

# Set version information in a config.h file
set(Test_VERSION_MAJOR 1)
set(Test_VERSION_MINOR 0)
include_directories("${PROJECT_BINARY_DIR}")

# Detect and add SFML
#set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#set(SFML_ROOT "C:/SFML")
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system network audio graphics window)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Arcanoid ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${Test_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Test_VERSION_MINOR}")
include(CPack)