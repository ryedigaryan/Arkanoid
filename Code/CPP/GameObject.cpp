//
// Created by ryedigaryan on 2/26/2018.
//

#include "Models/Interfaces/GameObject.h"

GameObject::~GameObject()
{
    if (m_delegate != nullptr) {
        m_delegate->go_isAtPeaceNow(m_identifier);
    }
}

unsigned GameObject::getIdentifier() const
{
    return m_identifier;
}

void GameObject::setDelegate(GameObjectDelegate* dlgate)
{
    if(dlgate != nullptr || dlgate != NULL) {
        m_delegate = dlgate;
        m_delegate->go_delegateSetted(this);
    }
}

void GameObject::setPosition(const Point& position)
{
    m_position.x = position.x;
    m_position.y = position.y;
    if(m_delegate != nullptr) {
        m_delegate->go_moved(m_identifier, m_position);
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

void GameObject::set(const Axis axis, const int value)
{
    axis == Axis::X ? m_position.x = value : m_position.y = value;
    if(m_delegate != nullptr) {
        m_delegate->go_moved(m_identifier, m_position);
    }
}

int GameObject::get(const Axis axis) const
{
    return (axis == Axis::X ? m_position.x : m_position.y);
}

void GameObject::set(const Dimension dimension, const int value)
{
    dimension == Dimension::Width ? m_size.width = value : m_size.height = value;
    if(m_delegate != nullptr) {
        m_delegate->go_sizeChanged(m_identifier, m_size);
    }
}

int GameObject::get(const Dimension dimension) const
{
    return (dimension == Dimension::Width ? m_size.width : m_size.height);
}
