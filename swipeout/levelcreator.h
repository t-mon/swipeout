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

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <QObject>

#include "board.h"
#include "blocks.h"

class LevelCreator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Board *board READ board CONSTANT)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit LevelCreator(QObject *parent = 0);

    int width() const;
    void setWidth(const int &width);

    int height() const;
    void setHeight(const int &height);

    Q_INVOKABLE void createRandomLevel();
    Q_INVOKABLE void saveLevel();

    Board *board();

private:
    int m_width;
    int m_height;

    Board *m_board;
    Level *m_level;
    QVector<QVector<BoardCell> > m_boardGrid;

    void initGrid();

signals:
    void widthChanged();
    void heightChanged();
    void blocksChanged();

};

#endif // LEVELCREATOR_H
