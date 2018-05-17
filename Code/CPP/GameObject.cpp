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

Point& GameObject::getPosition()
{
    return m_position;
}

const Point& GameObject::getPosition() const
{
    return m_position;
}

Size& GameObject::getSize()
{
    return m_size;
}

const Size& GameObject::getSize() const
{
    return m_size;
}

unsigned GameObject::generateIdentifier()
{
    static unsigned lastIdentifier;
    return lastIdentifier++;
}

Rect GameObject::rect() const {
    return Rect(m_position, m_size);
}
