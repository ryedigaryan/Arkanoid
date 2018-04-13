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

class GameObject {
public: // public interface
    explicit GameObject(ObjectType type, Point position = Point(), Size size = Size()) : m_type(type), m_position(position), m_size(size), m_identifier(generateIdentifier()) {}

//    GameObject(GameObject& other) : m_position(other.m_position), m_size(other.m_size), m_delegate(other.m_delegate), m_identifier(other.m_identifier) {}

    ~GameObject();

    unsigned getIdentifier() const;

    void setDelegate(GameObjectDelegate* dlgate);

    void setPosition(const Point& position);
    void setSize(const Size& size);
    Point getPosition() const;
    Size getSize() const;
    Rect getRect() const;
    ObjectType getType() const;

    void set(const Axis& axis, const int& value);
    void set(const Dimension& dimension, const int& value);
    int get(const Axis& axis) const;
    int get(const Dimension& dimension) const;

protected: // data
    Point m_position;
    Size m_size;
    ObjectType m_type;

    GameObjectDelegate* m_delegate = nullptr;

protected:
    unsigned m_identifier;
    static unsigned generateIdentifier();
};

#endif //ARCANOID_GAMEOBJECT_H
