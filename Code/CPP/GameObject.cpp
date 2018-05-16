//
// Created by ruben on 3/25/2018.
//

#include "Models/Interfaces/GameObject.h"

GameObject::~GameObject()
{
    if (m_delegate != nullptr) {
//        m_delegate->go_isAtPeaceNow(m_identifier);
    }
}

unsigned GameObject::getIdentifier() const
{
    return m_identifier;
}

void GameObject::setDelegate(GameObjectDelegate* dlgate)
{
    m_delegate = dlgate;
}

void GameObject::setPosition(const Point& position)
{
    float dx = position.x - m_position.x;
    float dy = position.y - m_position.y;
    m_position.x = position.x;
    m_position.y = position.y;
    if(m_delegate != nullptr) {
        m_delegate->go_moved(m_identifier, dx, dy);
    }
}

void GameObject::setSize(const Size& size)
{
    m_size.width = size.width;
    m_size.height = size.height;
    if(m_delegate != nullptr) {
        m_delegate->go_sizeChanged(m_identifier, m_size);
    }
}

Point GameObject::getPosition() const
{
    return m_position;
}

Size GameObject::getSize() const
{
    return m_size;
}

void GameObject::set(const Axis& axis, const float& value)
{
    axis == AxisX ? m_position.x = value : m_position.y = value;
}

float GameObject::get(const Axis& axis) const
{
    return (axis == AxisX ? m_position.x : m_position.y);
}

void GameObject::set(const Dimension& dimension, const float& value)
{
    dimension == Dimension::DimensionWidth ? m_size.width = value : m_size.height = value;
    if(m_delegate != nullptr) {
        m_delegate->go_sizeChanged(m_identifier, m_size);
    }
}

float GameObject::get(const Dimension& dimension) const
{
    return (dimension == Dimension::DimensionWidth ? m_size.width : m_size.height);
}

unsigned GameObject::generateIdentifier()
{
    static unsigned lastIdentifier;
    return lastIdentifier++;
}

ObjectType GameObject::getType() const
{
    return m_type;
}

Rect GameObject::rect() const {
    return Rect(m_position, m_size);
}
