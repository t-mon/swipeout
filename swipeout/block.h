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

#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QColor>

class Block : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(QColor color READ color NOTIFY colorChanged)
    Q_PROPERTY(int startX READ startX CONSTANT)
    Q_PROPERTY(int startY READ startY CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)

public:
    enum Orientation {
        Horizontal,
        Vertical
    };

    explicit Block(const int &id,  const int &x, const int &y, const int &height, const int &width, QObject *parent = 0);
    Block(Block* other);

    Orientation orientation() const;

    int id() const;
    void setId(const int &id);

    int startX() const;
    int x()const;
    void setX(const int &x);

    int startY() const;
    int y()const;
    void setY(const int &y);

    int width()const;
    void setWidth(const int &width);

    int height()const;
    void setHeight(const int &height);

    QColor color() const;

    void resetPosition();

private:
    int m_id;
    int m_startX;
    int m_x;
    int m_startY;
    int m_y;
    int m_height;
    int m_width;

    QColor m_color;

    void setColor();

signals:
    void xChanged();
    void yChanged();
    void colorChanged();
    void positionResetted();

};

#endif // BLOCK_H
