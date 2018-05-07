//
// Created by ruben on 3/25/2018.
//

#include "GameStates/GamingState.h"

GamingState::GamingState(GameData* gameData, unsigned startLevelNumber, unsigned lastLevelNumber) : State(gameData), m_firstLevelNumber(startLevelNumber), m_lastLevelNumber(lastLevelNumber)
{
    cout << "State: Gaming" << endl;
    m_gameData->engine->m_delegate = this;
}

void GamingState::init()
{
    m_gameData->drawer->drawGameScene(0);
    setEngineLevel(m_currentLevelNumber = m_firstLevelNumber);
}

void GamingState::handleInput()
{
    m_gameData->drawer->displayChanges();
    m_gameData->drawer->displayChanges();
    static sf::Event e;
    while(m_gameData->drawer->getDrawingWindow()->pollEvent(e)) {
        if(e.type == sf::Event::KeyPressed) {
            switch(e.key.code) {
                case PauseButton:
                    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress()));
                    return;
                case MoveLeftButton:
                    m_gameData->engine->movePlayer(SideLeft);
                    break;
                case MoveRightButton:
                    m_gameData->engine->movePlayer(SideRight);
                    break;
                //ToDo: These cases are for debugging
                case sf::Keyboard::Up:
                    m_gameData->engine->movePlayer(SideUp);
                    break;
                case sf::Keyboard::Down:
                    m_gameData->engine->movePlayer(SideDown);
                    break;
            }
        }
        else if(e.type == sf::Event::KeyReleased){
            switch(e.key.code) {
                case MoveLeftButton:
                    // if the right movement button is pressed then player should move right
                    if(!sf::Keyboard::isKeyPressed(MoveRightButton)) {
                        m_gameData->engine->stopPlayer();
                    }
                    break;
                case MoveRightButton:
                    // if the left movement button is pressed then player should move left
                    if(!sf::Keyboard::isKeyPressed(MoveLeftButton)) {
                        m_gameData->engine->stopPlayer();
                    }
                    break;
                //TODO: These cases are for debugging
                case sf::Keyboard::Up:
                case sf::Keyboard::Down:
                    m_gameData->engine->stopPlayer();
                    break;
            }
        }
    }
}

void GamingState::update()
{
    m_gameData->engine->process();
    m_currentLevelState = m_gameData->engine->getState();
    if(m_currentLevelState != LevelStateInProcess) {
        m_gameData->stateMachine->pushState(new LevelEndState(m_gameData, m_currentLevelNumber, m_currentLevelState, m_lastLevelNumber));
    }
}

void GamingState::draw() {
    m_gameData->drawer->displayChanges();
}

void GamingState::pause()
{
    // nothing must be done
}

void GamingState::resume()
{
    if(m_currentLevelState != LevelStateInProcess) {
        if(m_currentLevelNumber == m_lastLevelNumber) {
            m_gameData->stateMachine->popActiveState();
            return;
        }
        setEngineLevel(++m_currentLevelNumber);
    }
    // game scene must be updated 2 times because now screen may be modified (for example - pause info may be drawn)
    m_gameData->drawer->drawGameScene(m_gameData->engine->getProgress(false));
    m_gameData->drawer->drawGameScene(m_gameData->engine->getProgress(false));
}

void GamingState::setEngineLevel(const unsigned& levelNumber)
{
    Level level = m_gameData->resourceManager->getLevel(levelNumber);
    level.setGoDelegate(this, ObjectTypePaddle);
    level.setGoDelegate(this, ObjectTypeBall);
    level.setGoDelegate(this, ObjectTypeBrick);
    // we do not set delegate for border because it will not change it's position or size, or will not disappear
    m_gameData->engine->setLevel(level);
    m_currentLevelState = m_gameData->engine->getState();
    // drawing game scene just because pause pop-up must be drawn on it
    m_gameData->drawer->drawGameScene(m_gameData->engine->getProgress(false));
    m_gameData->stateMachine->pushState(new PausedState(m_gameData, m_currentLevelNumber, m_gameData->engine->getProgress(false)));
}

void GamingState::engine_levelSet(const Level& level)
{
    calculateScaling();
    ArkanoidDrawer* drawer = m_gameData->drawer;
    // draw blank game scene, without any object (brick, paddle or ball)
    // its like clearing the scene
    drawer->drawGameScene(m_gameData->engine->getProgress(false));
    // and then draw bricks, paddle(player) and ball
    unsigned drawnObjectID;
    m_bingingsOffset = level.smallestIdentifier();
    m_model2ViewBindings.clear();
    m_model2ViewBindings.resize(level.countOfGameObjects());
    for(auto brick : level.bricks) {
        drawnObjectID = drawer->drawObject(scale(brick->getPosition()), scale(brick->getSize()), m_gameData->resourceManager->getTexture(ObjectTypeBrick, static_cast<unsigned int>(brick->getHealth())));
        setViewForModel(brick->getIdentifier(), drawnObjectID);

    }
    drawnObjectID = drawer->drawObject(scale(level.player.getPosition()), scale(level.player.getSize()), m_gameData->resourceManager->getTexture(ObjectTypePaddle));
    setViewForModel(level.player.getIdentifier(), drawnObjectID);
    drawnObjectID = drawer->drawObject(scale(level.ball.getPosition()), scale(level.ball.getSize()), m_gameData->resourceManager->getTexture(ObjectTypeBall));
    setViewForModel(level.ball.getIdentifier(), drawnObjectID);
    drawer->displayChanges();
}

void GamingState::calculateScaling()
{
    Size engineLevelSize = m_gameData->engine->getLevel().getSize();
    sf::Vector2f drawerLevelSize = m_gameData->drawer->getLevelSize();
    m_scaleFactor.x = drawerLevelSize.x / engineLevelSize.width;
    m_scaleFactor.y = drawerLevelSize.y / engineLevelSize.height;
}

sf::Vector2f GamingState::scale(const Point& position)
{
    return sf::Vector2f(position.x * m_scaleFactor.x, position.y * m_scaleFactor.y);
}

sf::Vector2f GamingState::scale(const Size& size)
{
    return sf::Vector2f(size.width * m_scaleFactor.x, size.height * m_scaleFactor.y);
}

void GamingState::setViewForModel(unsigned modelID, unsigned viewiD)
{
    m_model2ViewBindings[modelID - m_bingingsOffset] = viewiD;
}

unsigned GamingState::getViewOfModel(unsigned modelID)
{
    return m_model2ViewBindings[modelID - m_bingingsOffset];
}

void GamingState::go_healthChanged(unsigned go_id, int go_health, int go_healthChange)
{

}

void GamingState::go_isAtPeaceNow(unsigned go_id)
{

}

void GamingState::go_moved(unsigned go_id, const int& dx, const int& dy)
{
    auto viewID = getViewOfModel(go_id);
    m_gameData->drawer->moveObject(viewID, sf::Vector2f(dx, dy));
}

void GamingState::go_sizeChanged(unsigned go_id, const Size &go_size)
{

}
