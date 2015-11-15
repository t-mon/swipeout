#include "level.h"

Level::Level(QObject *parent) :
    QObject(parent),
    m_blocks(new Blocks(this))
{

}

Blocks *Level::blocks()
{
    return m_blocks;
}

void Level::addBlock(Block *block)
{
    m_blocks->addBlock(block);
}

QString Level::name() const
{
    return m_name;
}

void Level::setName(const QString &name)
{
    m_name = name;
}

int Level::id() const
{
    return m_id;
}

void Level::setId(const int &id)
{
    m_id = id;
}

int Level::width() const
{
    return m_width;
}

void Level::setWidth(const int &width)
{
    m_width = width;
}

int Level::height() const
{
    return m_height;
}

void Level::setHeight(const int &height)
{
    m_height = height;
}

