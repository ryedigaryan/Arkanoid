#include <iostream>

#include "ArcanoidGameManager.h"

#define END system("pause"); return 0;

int main() {

    ArcanoidGameManager& manager = ArcanoidGameManager::getManager();
    ArcanoidGameDrawer drawer(Size(300, 330));
    ArcanoidGameEngine& engine = ArcanoidGameEngine::getEngine();
    manager.addAllLevelSpecsInPath(LevelSpecsPath, LevelSpecExtension, LevelCount);
    manager.setDrawer(&drawer);
    manager.setEngine(&engine);

    manager.startGame();

    std::cout << "Hello, World!" << std::endl;
    END
}