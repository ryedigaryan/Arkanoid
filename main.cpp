#include <iostream>

#include "ArcanoidGameManager.h"

int main() {
    ArcanoidGameManager& manage = ArcanoidGameManager::getManager();
    ArcanoidGameDrawer drawer(Size(10, 10));
    ArcanoidGameEngine& engine = ArcanoidGameEngine::getEngine();
    manage.setDrawer(&drawer);
    manage.setEngine(&engine);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}