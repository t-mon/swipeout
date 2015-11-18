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

#include "block.h"

Block::Block(const int &id, const int &x, const int &y, const int &height, const int &width, QObject *parent) :
    QObject(parent),
    m_id(id),
    m_startX(x),
    m_x(x),
    m_startY(y),
    m_y(y),
    m_height(height),
    m_width(width)
{
    setColor();
}

Block::Block(Block *other, QObject *parent) :
    QObject(parent),
    m_id(other->id()),
    m_startX(other->startX()),
    m_x(other->x()),
    m_startY(other->startY()),
    m_y(other->y()),
    m_height(other->height()),
    m_width(other->width())
{
    setColor();
}

Block::Orientation Block::orientation() const
{
    if (m_height > m_width) {
        return Vertical;
    }
    return Horizontal;
}

int Block::id() const
{
    return m_id;
}

void Block::setId(const int &id)
{
    m_id = id;
}

int Block::startX() const
{
    return m_startX;
}

int Block::x() const
{
    return m_x;
}

void Block::setX(const int &x)
{
    m_x = x;
    emit xChanged();
}

int Block::startY() const
{
    return m_startY;
}

int Block::y() const
{
    return m_y;
}

void Block::setY(const int &y)
{
    m_y = y;
    emit yChanged();
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

QColor Block::color() const
{
    return m_color;
}

void Block::resetPosition()
{
    setX(m_startX);
    setY(m_startY);
    emit positionResetted();
}

void Block::setColor()
{
    switch (m_id) {
    case 0:
        m_color = QColor("#DD4814");
        break;
    case 1:
        m_color = QColor("#9E7D96");
        break;
    case 2:
        m_color = QColor("#411934");
        break;
    case 3:
        m_color = QColor("#77216F");
        break;
    case 4:
        m_color = QColor("#6E3C61");
        break;
    case 5:
        m_color = QColor("#5E2750");
        break;
    case 6:
        m_color = QColor("#77216F");
        break;
    case 7:
        m_color = QColor("#772953");
        break;
    case 8:
        m_color = QColor("#F1B5A1");
        break;
    case 9:
        m_color = QColor("#BB90B7");
        break;
    case 10:
        m_color = QColor("#EA9172");
        break;
    case 11:
        m_color = QColor("#F4C8B8");
        break;
    default:
        break;
    }

    emit colorChanged();
}

