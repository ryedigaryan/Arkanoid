//
// Created by ryedigaryan on 2/26/2018.
//

#ifndef ARCANOID_GAMEOBJECT_H
#define ARCANOID_GAMEOBJECT_H

#include "Geometry/Geometry.h"
#include "Interfaces/GameObjectDelegate.h"

class GameObject {
public:
    explicit GameObject(string texturePath = "", Point position = Point(), Size size = Size())
            : m_position(position), m_size(size), m_texturePath(texturePath) {}

    ~GameObject();

    unsigned getIdentifier() const;

    void setDelegate(GameObjectDelegate* dlgate);

    void setPosition(const Point& position);
    void setSize(const Size& size);
    Point getPosition() const;
    Size getSize() const;

    void set(const Axis axis, const int value);
    void set(const Dimension dimension, const int value);
    int get(const Axis axis) const;
    int get(const Dimension dimension) const;

    string m_texturePath;

protected:
    Point m_position;
    Size m_size;

    GameObjectDelegate* m_delegate = nullptr;

protected:
    const unsigned m_identifier = GameObject::generateIdentifier();
    static unsigned generateIdentifier() {
        static unsigned lastIdentifier;
        return lastIdentifier++;
    }
};

#endif //ARCANOID_GAMEOBJECT_H
