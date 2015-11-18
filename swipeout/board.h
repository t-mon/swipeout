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

#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>
#include <QStack>

#include "level.h"

class BoardCell
{
public:
    BoardCell(const int &x = 0, const int &y = 0, const int &blockId = -1);

    int x() const;
    int y() const;

    int blockId() const;
    void setBlockId(const int &blockId);

    bool operator==(const BoardCell &other);

private:
    int m_x;
    int m_y;
    int m_blockId;
};

class Move
{
public:
    Move(const int &id = 0, const int &delta = 0): m_id(id), m_delta(delta) {}

    int id() const { return m_id; }
    int delta() const { return m_delta; }

private:
    int m_id;
    int m_delta;
};

class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Level* level READ level NOTIFY levelChanged)
    Q_PROPERTY(int moveCount READ moveCount NOTIFY moveCountChanged)

public:
    explicit Board(QObject *parent = 0);

    void clearLevel();
    Q_INVOKABLE void restartLevel();
    void loadLevel(Level *level);

    Level *level();

    int moveCount() const;

    Q_INVOKABLE int calculateLeftLimit(const int &blockId);
    Q_INVOKABLE int calculateRightLimit(const int &blockId);
    Q_INVOKABLE int calculateUpperLimit(const int &blockId);
    Q_INVOKABLE int calculateLowerLimit(const int &blockId);

    Q_INVOKABLE void moveBlock(const int &id, const int &delta, const bool &fromUndo = false);
    Q_INVOKABLE void undoMove();

    static void printBoard(const QVector<QVector<BoardCell> > &boardGrid);

private:
    QVector<QVector<BoardCell> > m_boardGrid;
    Level *m_level;
    int m_moveCount;

    QStack<Move> m_moveStack;

    void initBoard();

    void moveBlockX(const int &id, const int &newX);
    void moveBlockY(const int &id, const int &newY);

    void setMoveCount(const int &moveCount);

signals:
    void moveCountChanged();
    void levelCompleted();
    void levelChanged();
};

#endif // BOARD_H
