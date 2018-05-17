//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_GAMEOBJECT_H
#define ARCANOID_GAMEOBJECT_H

#include <Geometry/Rect.h>
#include "Definitions/CommonDefinitions.h"
#include "Geometry/Geometry.h"
#include "Interfaces/GameObjectDelegate.h"
#include "Definitions/ModelDefinitions.h"

class GameObject
{
public: // public interface
    explicit GameObject(Point position = Point(), Size size = Size()) : m_position(position), m_size(size), m_identifier(generateIdentifier()) {}

    ~GameObject();

    void setDelegate(GameObjectDelegate* dlgate);
    void setPosition(const Point& position);
    void setSize(const Size& size);

    Point& getPosition();
    Size&  getSize();
    const Point& getPosition()  const;
    const Size&  getSize()      const;
    unsigned getIdentifier()    const;
    Rect rect()                 const;

protected: // data
    unsigned m_identifier;
    Point m_position;
    Size m_size;

    GameObjectDelegate* m_delegate = nullptr;

protected:
    static unsigned generateIdentifier();
};

#endif //ARCANOID_GAMEOBJECT_H
