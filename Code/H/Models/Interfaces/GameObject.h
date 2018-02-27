//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_GAMEOBJECT_H
#define ARCANOID_GAMEOBJECT_H

#include "Geometry/Geometry.h"
#include "Interfaces/GameObjectDelegate.h"

class GameObject {
public:
    GameObject(Point position = Point(), Size size = Size(), int texture = 1)
            : m_position(position), m_size(size), m_texture(texture) {}

    ~GameObject();

    int getIdentifier() const;

    void setDelegate(GameObjectDelegate* dlgate);

    void setPosition(const Point& position);
    void setSize(const Size& size);
    Point getPosition() const;
    Size getSize() const;

    void set(const Axis axis, const int value);
    void set(const Dimension dimension, const int value);
    int get(const Axis axis) const;
    int get(const Dimension dimension) const;

    int m_texture;

protected:
    Point m_position;
    Size m_size;

    GameObjectDelegate* m_delegate = NULL;

protected:
    const unsigned m_identifier = GameObject::generateIdentifier();
    static unsigned generateIdentifier() {
        static unsigned lastIdentifier;
        return lastIdentifier++;
    }
};

#endif //ARCANOID_GAMEOBJECT_H
