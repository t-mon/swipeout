/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Swipeout.                                         *
 *                                                                         *
 *  Swipeout is free software: you can redistribute it and/or modify       *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Swipeout is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Swipeout. If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

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

