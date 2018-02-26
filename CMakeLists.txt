# cmake_minimum_required(VERSION <specify CMake version here>)
project(Arcanoid)

set(CMAKE_CXX_STANDARD 17)

add_executable(Arcanoid main.cpp Code/H/Geometry/Geometry.h Code/H/Geometry/Vector.h Code/H/Geometry/Point.h Code/H/Geometry/Size.h Code/H/Interfaces/ArcanoidGameEngineDelegate.h Code/H/Interfaces/ArcanoidGameDrawerDelegate.h Code/H/Interfaces/GameObjectDelegate.h Code/H/Models/Interfaces/Attacker.h Code/H/Models/Interfaces/GameObject.h Code/H/Models/Interfaces/Mortal.h Code/H/Models/Interfaces/Movable.h Code/H/Models/AllGameObjects.h Code/H/Models/Ball.h Code/H/Models/Brick.h Code/H/Models/Border.h Code/H/Models/Paddle.h Code/H/ArcanoidGameDrawer.h Code/H/ArcanoidGameEngine.h Code/H/ArcanoidGameManager.h Code/H/Definitions.h Code/CPP/ArcanoidGameDrawer.cpp Code/CPP/ArcanoidGameEngine.cpp Code/CPP/ArcanoidGameManager.cpp Code/CPP/GameObject.cpp Code/CPP/Vector.cpp)