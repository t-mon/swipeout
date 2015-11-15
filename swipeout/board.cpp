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

#include "board.h"

#include <QDebug>

BoardCell::BoardCell(const int &x, const int &y, const int &blockId):
    m_x(x),
    m_y(y),
    m_blockId(blockId)
{
}

int BoardCell::x() const
{
    return m_x;
}

int BoardCell::y() const
{
    return m_y;
}

int BoardCell::blockId() const
{
    return m_blockId;
}

void BoardCell::setBlockId(const int &blockId)
{
    m_blockId = blockId;
}

Board::Board(QObject *parent) :
    QObject(parent)
{

}

void Board::clearLevel()
{
    qDebug() << "Clear board";
    m_board.clear();
    m_board.resize(0);
    setMoveCount(0);
}

void Board::resetBoard()
{
    if (m_level) {
        setMoveCount(0);
        m_level->blocks()->resetBlockPositions();
    }
    initBoard();
}

void Board::loadLevel(Level *level)
{
    clearLevel();

    m_level = level;
    m_level->blocks()->resetBlockPositions();

    initBoard();
    printBoard();
}

Level *Board::level()
{
    return m_level;
}

int Board::moveCount() const
{
    return m_moveCount;
}

int Board::calculateLeftLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);
    int leftLimit = 0;
    for (int i = block->x() - 1; i >= 0; i--) {
        if (m_board[i][block->y()].blockId() != -1) {
            leftLimit = i + 1;
            break;
        }
    }
    qDebug() << "left limit" << leftLimit;
    return leftLimit;
}

int Board::calculateRightLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);

    bool freePath = true;
    int rightLimit = m_level->width() - block->width();
    for (int i = block->x() + block->width(); i < m_level->width(); i++) {
        if (m_board[i][block->y()].blockId() != -1) {
            rightLimit = i - block->width();
            freePath = false;
            break;
        }
    }

    if (block->id() == 0 && freePath)
        rightLimit += 2;

    qDebug() << "right limit" << rightLimit;
    return rightLimit;
}

int Board::calculateUpperLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);
    int upperLimit = 0;
    for (int i = block->y() - 1; i >= 0; i--) {
        if (m_board[block->x()][i].blockId() != -1) {
            upperLimit = i + 1;
            break;
        }
    }
    qDebug() << "upper limit" << upperLimit;
    return  upperLimit;
}

int Board::calculateLowerLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);
    int lowerLimit = m_level->height() - block->height();
    for (int i = block->y() + block->height(); i < m_level->height(); i++) {
        if (m_board[block->x()][i].blockId() != -1) {
            lowerLimit = i - block->height();
            break;
        }
    }
    qDebug() << "lower limit" << lowerLimit;
    return lowerLimit;
}

void Board::moveBlockX(const int &id, const int &newX)
{
    Block *block = m_level->blocks()->get(id);

    if (newX < 0 || newX + block->width() > m_level->width()) {
        emit levelCompleted();
        return;
    }

    if (block->x() == newX)
        return;

    for (int i = 0; i < block->width(); i++) {
        m_board[block->x()  + i][block->y()].setBlockId(-1);
    }
    qDebug() << "move block" << id <<  " -> x = " << newX;
    block->setX(newX);

    for (int i = 0; i < block->width(); i++) {
        m_board[block->x()  + i][block->y()].setBlockId(block->id());
    }

    printBoard();
    setMoveCount(m_moveCount + 1);
}

void Board::moveBlockY(const int &id, const int &newY)
{
    Block *block = m_level->blocks()->get(id);

    if (block->y() == newY)
        return;

    for (int i = 0; i < block->height(); i++) {
        m_board[block->x()][block->y()  + i].setBlockId(-1);
    }
    qDebug() << "move block to y = " << newY;
    block->setY(newY);

    for (int i = 0; i < block->height(); i++) {
        m_board[block->x()][block->y()  + i].setBlockId(block->id());
    }

    printBoard();
    setMoveCount(m_moveCount + 1);
}

void Board::initBoard()
{
    m_board.clear();
    m_board.resize(m_level->width());
    for (int x = 0; x < m_level->width(); x++) {
        QVector<BoardCell> line;
        line.resize(m_level->height());
        for (int y = 0; y < m_level->height(); y++) {
            line[y] = (BoardCell(x, y));
        }
        m_board[x] = line;
    }
    // set blocks
    foreach (Block *block, m_level->blocks()->blocks()) {
        if (block->width() > block->height()) {
            for (int i = 0; i < block->width(); i++) {
                m_board[block->x()  + i][block->y()].setBlockId(block->id());
            }
        } else {
            for (int i = 0; i < block->height(); i++) {
                m_board[block->x()][block->y() + i].setBlockId(block->id());
            }
        }
    }
}

void Board::setMoveCount(const int &moveCount)
{
    m_moveCount = moveCount;
    emit moveCountChanged();
}

void Board::printBoard()
{
    QString output("------------------------------\n");
    for (int y = 0; y < m_board.length(); y++) {
        for (int x = 0; x < m_board[y].length(); x++) {
            if (m_board[x][y].blockId() == -1)
                output.append(" x");
            else
                output.append(" " + QString::number(m_board[x][y].blockId()));
        }
        output.append("\n");
    }
    qDebug() << output;
}
