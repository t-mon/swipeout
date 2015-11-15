#include "block.h"

Block::Block(QObject *parent) : QObject(parent)
{

}

int Block::id() const
{
    return m_id;
}

void Block::setId(const int &id)
{
    m_id = id;
}

int Block::x() const
{
    return m_x;
}

void Block::setX(const int &x)
{
    m_x = x;
}

int Block::y() const
{
    return m_y;
}

void Block::setY(const int &y)
{
    m_y = y;
}

int Block::width() const
{
    return m_width;
}

void Block::setWidth(const int &width)
{
    m_width = width;
}

int Block::height() const
{
    return m_height;
}

void Block::setHeight(const int &height)
{
    m_height = height;
}

