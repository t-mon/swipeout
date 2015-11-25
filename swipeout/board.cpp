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
#include <QTimer>
#include <QSettings>

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

bool BoardCell::operator==(const BoardCell &other)
{
    return x() == other.x() && y() == other.y() && blockId() == other.blockId();
}

Board::Board(QObject *parent, const bool &creatorBoard) :
    QObject(parent),
    m_creatorBoard(creatorBoard),
    m_level(0),
    m_showSolutionRunning(false)
{
}

void Board::clearLevel()
{
    qDebug() << " -> Clear board";
    m_boardGrid.clear();

    if (m_level)
        m_level->destroyBlocks();

    m_level = 0;

    setMoveCount(0);
}

void Board::restartLevel()
{
    if (m_level) {
        setMoveCount(0);
        m_level->blocks()->resetBlockPositions();
    }
    m_moveStack.clear();
    updateBoardGrid();
}

void Board::loadLevel(Level *level)
{

    if (m_creatorBoard) {
        qDebug() << "Set creator level" << level->id();
        m_level = level;
        emit levelChanged();
    } else {
        clearLevel();
        qDebug() << "Start level" << level->id();

        m_level = level;
        m_level->loadBlocks();
        emit levelChanged();
    }

    setSolution(m_level->solution());
    restartLevel();
    printBoard(m_boardGrid);
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
        if (m_boardGrid[i][block->y()].blockId() != -1) {
            leftLimit = i + 1;
            break;
        }
    }
    return leftLimit;
}

int Board::calculateRightLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);

    bool freePath = true;
    int rightLimit = m_level->width() - block->width();
    for (int i = block->x() + block->width(); i < m_level->width(); i++) {
        if (m_boardGrid[i][block->y()].blockId() != -1) {
            rightLimit = i - block->width();
            freePath = false;
            break;
        }
    }

    if (block->id() == 0 && freePath)
        rightLimit += 2;

    return rightLimit;
}

int Board::calculateUpperLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);
    int upperLimit = 0;
    for (int i = block->y() - 1; i >= 0; i--) {
        if (m_boardGrid[block->x()][i].blockId() != -1) {
            upperLimit = i + 1;
            break;
        }
    }
    return  upperLimit;
}

int Board::calculateLowerLimit(const int &blockId)
{
    Block *block = m_level->blocks()->get(blockId);
    int lowerLimit = m_level->height() - block->height();
    for (int i = block->y() + block->height(); i < m_level->height(); i++) {
        if (m_boardGrid[block->x()][i].blockId() != -1) {
            lowerLimit = i - block->height();
            break;
        }
    }
    return lowerLimit;
}

void Board::moveBlock(const int &id, const int &delta, const bool &fromUndo)
{
    Block *block = m_level->blocks()->get(id);

    if (delta == 0)
        return;

    if (block->orientation() == Block::Horizontal) {
        moveBlockX(id, block->x() + delta);
    } else {
        moveBlockY(id, block->y() + delta);
    }

    if (!fromUndo)
        m_moveStack.push(Move(id, moveCount(), delta));
}

void Board::undoMove()
{
    if (m_moveStack.isEmpty())
        return;

    qDebug() << "Undo move:" ;
    Move move = m_moveStack.pop();
    int undoDelta = move.delta() * -1;

    moveBlock(move.id(), undoDelta, true);
}

void Board::showSolution()
{
    m_solution = m_level->solution();

    // store current positions
    foreach (Block *block, m_level->blocks()->blocks()) {
        m_currentPositions.insert(block->id(), QPoint(block->x(), block->y()));
    }

    m_level->blocks()->resetBlockPositions();

    // start showing the solution
    QTimer::singleShot(400, this, SLOT(automaticMove()));
}

bool Board::showSolutionRunning() const
{
    return m_showSolutionRunning;
}

int Board::solutionCount() const
{
    return m_solution.count();
}

bool Board::solutionAvailable() const
{
    return !m_solution.isEmpty();
}

void Board::setSolution(const QStack<Move> &solution)
{
    m_solution = solution;
    emit solutionAvailableChanged();
    emit solutionCountChanged();
}

void Board::clearSolution()
{
    m_solution.clear();
    if (m_level)
        if (m_creatorBoard)
            m_level->clearSolution();

    emit solutionAvailableChanged();
    emit solutionCountChanged();
}

QVector<QVector<BoardCell> > Board::boardGrid() const
{
    return m_boardGrid;
}

void Board::printBoard(const QVector<QVector<BoardCell> > &boardGrid)
{
    QString output("------------------------------\n");
    for (int y = 0; y < boardGrid.length(); y++) {
        for (int x = 0; x < boardGrid[y].length(); x++) {
            if (boardGrid[x][y].blockId() == -1)
                output.append(" x");
            else
                output.append(" " + QString::number(boardGrid[x][y].blockId()));
        }
        output.append("\n");
    }
    qDebug() << output;
}

void Board::updateBoardGrid()
{
    m_boardGrid.clear();
    m_boardGrid.resize(m_level->width());
    for (int x = 0; x < m_level->width(); x++) {
        QVector<BoardCell> line;
        line.resize(m_level->height());
        for (int y = 0; y < m_level->height(); y++) {
            line[y] = (BoardCell(x, y));
        }
        m_boardGrid[x] = line;
    }

    // set blocks
    foreach (Block *block, m_level->blocks()->blocks()) {
        if (block->width() > block->height()) {
            for (int i = 0; i < block->width(); i++) {
                m_boardGrid[block->x()  + i][block->y()].setBlockId(block->id());
            }
        } else {
            for (int i = 0; i < block->height(); i++) {
                m_boardGrid[block->x()][block->y() + i].setBlockId(block->id());
            }
        }
    }
    emit gridChanged();
}

void Board::moveBlockX(const int &id, const int &newX)
{
    Block *block = m_level->blocks()->get(id);

    if (newX < 0 || newX + block->width() > m_level->width()) {
        setMoveCount(m_moveCount + 1);
        onLevelCompleted();
        return;
    }

    if (block->x() == newX)
        return;

    // remove old block position
    for (int i = 0; i < block->width(); i++) {
        m_boardGrid[block->x()  + i][block->y()].setBlockId(-1);
    }
    qDebug() << "move block" << id <<  " -> x = " << newX;
    block->setX(newX);

    // add new block position
    for (int i = 0; i < block->width(); i++) {
        m_boardGrid[block->x()  + i][block->y()].setBlockId(block->id());
    }

    printBoard(m_boardGrid);
    setMoveCount(m_moveCount + 1);
    updateBoardGrid();
}

void Board::moveBlockY(const int &id, const int &newY)
{
    Block *block = m_level->blocks()->get(id);

    if (block->y() == newY)
        return;

    for (int i = 0; i < block->height(); i++) {
        m_boardGrid[block->x()][block->y()  + i].setBlockId(-1);
    }
    qDebug() << "move block" << id <<  " -> y = " << newY;
    block->setY(newY);

    for (int i = 0; i < block->height(); i++) {
        m_boardGrid[block->x()][block->y()  + i].setBlockId(block->id());
    }

    printBoard(m_boardGrid);
    setMoveCount(m_moveCount + 1);
    updateBoardGrid();
}

void Board::setMoveCount(const int &moveCount)
{
    m_moveCount = moveCount;
    emit moveCountChanged();
}

void Board::automaticMove()
{
    if (!m_solution.isEmpty()) {
        if (!m_showSolutionRunning) {
            m_showSolutionRunning = true;
            emit showSolutionRunningChanged();
        }

        Move move = m_solution.takeFirst();
        moveBlock(move.id(), move.delta());
        QTimer::singleShot(400, this, SLOT(automaticMove()));
    } else {
        // finished, reset the position
        foreach (Block *block, m_level->blocks()->blocks()) {
            QPoint position = m_currentPositions.value(block->id());
            block->setX(position.x());
            block->setY(position.y());
        }
        updateBoardGrid();

        m_showSolutionRunning = false;
        emit showSolutionRunningChanged();
    }
}

void Board::onLevelCompleted()
{
    qDebug() << "Level completed with" << m_moveCount << "moves!!";

    QSettings settings;
    settings.beginGroup(m_level->levelPackName());
    settings.beginGroup(m_level->name());

    // set completed
    if (!settings.value("completed", false).toBool()) {
        m_level->setCompleted(true);
        settings.setValue("completed", true);
        qDebug() << "Level completed first time!! " << m_level->record();
    }

    // set record
    int record = settings.value("record", 0).toInt();
    if (record == 0)
        record = 9999;

    if (m_moveCount < record) {
        m_level->setRecord(m_moveCount);
        settings.setValue("record", m_moveCount);
        qDebug() << "New record!! " << m_level->record();
    }

    settings.endGroup();
    settings.endGroup();

    emit levelCompleted();
}
