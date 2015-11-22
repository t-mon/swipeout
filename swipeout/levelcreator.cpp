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

#include "levelcreator.h"

#include <QStandardPaths>
#include <QJsonDocument>
#include <QDateTime>
#include <QGuiApplication>
#include <QDebug>
#include <QPoint>
#include <QFile>
#include <QDir>

LevelCreator::LevelCreator(QObject *parent) :
    QObject(parent),
    m_width(6),
    m_height(6),
    m_board(new Board(this, true)),
    m_level(new Level(this)),
    m_deleteToolSelected(false),
    m_twoHorizontalToolSelected(false),
    m_twoVerticalToolSelected(false),
    m_addMode(false)
{
    initLevel();
    qsrand(QDateTime::currentMSecsSinceEpoch());
    connect(m_board, SIGNAL(gridChanged()), this, SLOT(onGridChanged()));
}

int LevelCreator::width() const
{
    return m_width;
}

void LevelCreator::setWidth(const int &width)
{
    m_width = width;
    emit widthChanged();
}

int LevelCreator::height() const
{
    return m_height;
}

void LevelCreator::setHeight(const int &height)
{
    m_height = height;
    emit heightChanged();
}

void LevelCreator::createRandomLevel()
{
    initLevel();

    qDebug() << "------------------------------------";
    qDebug() << "Create random level: " << m_level->name();

    QList<Block *> blocks;

    int min = 3; int max = 6; int id = 1;
    int verticalBlockCount = (int)(qrand() % (max - min + 1) + min);

    for (int i = 0; i < verticalBlockCount; i++) {
        min = 2; max = 3; id++;
        int height = (int)(qrand() % (max - min + 1) + min);
        Block *block = new Block(id, 0, 0, height, 1, m_level);
        blocks.append(block);
    }

    min = 3; max = 6;
    int horizontalBlockCount = (int)(qrand() % (max - min + 1) + min);

    for (int i = 0; i < horizontalBlockCount; i++) {
        min = 2; max = 3; id++;
        int width = (int)(qrand() % (max - min + 1) + min);
        Block *block = new Block(id, 0, 0, 1, width, m_level);
        blocks.append(block);
    }

    // positioning all blocks
    foreach (Block *block, blocks) {
        if (block->orientation() == Block::Vertical) {
            QList<QPoint> positions = possiblePositions(block);

            if (positions.isEmpty()) {
                block->deleteLater();
            } else {
                int index = qrand() % positions.length();
                QPoint finalPosition = positions.at(index);
                block->setX(finalPosition.x());
                block->setY(finalPosition.y());
                m_level->blocks()->addBlock(block);
                m_board->updateBoardGrid();
            }
        } else if (block->orientation() == Block::Horizontal) {
            QList<QPoint> positions = possiblePositions(block);

            if (positions.isEmpty()) {
                block->deleteLater();
            } else {
                int index = qrand() % positions.length();
                QPoint finalPosition = positions.at(index);
                block->setX(finalPosition.x());
                block->setY(finalPosition.y());
                m_level->blocks()->addBlock(block);
                m_board->updateBoardGrid();
            }
        }
    }

    qDebug() << " All blocks";
    foreach (Block *block, m_level->blocks()->blocks()) {
        qDebug() << " -> Block" << block->id() << ":" << block->width() << "x" << block->height();
    }

    m_board->loadLevel(m_level);
}

void LevelCreator::saveLevel()
{
    QVariantMap levelMap;
    levelMap.insert("name", "Level " + QString::number(m_level->id()));
    levelMap.insert("id", m_level->id());
    levelMap.insert("height", m_level->height());
    levelMap.insert("width", m_level->width());

    QVariantList blockList;
    foreach (Block *block, m_level->blocks()->blocks()) {
        QVariantMap blockMap;
        blockMap.insert("id", block->id());
        blockMap.insert("x", block->x());
        blockMap.insert("y", block->y());
        blockMap.insert("height", block->height());
        blockMap.insert("width", block->width());
        blockList.append(blockMap);
    }
    levelMap.insert("blocks", blockList);

    QVariantList solutionList;
    for (int i = 0; i < m_level->solution().count(); i++) {
        QVariantMap moveMap;
        moveMap.insert("step", i);
        moveMap.insert("block", m_level->solution().at(i).id());
        moveMap.insert("delta", m_level->solution().at(i).delta());
        solutionList.append(moveMap);
    }
    levelMap.insert("solution", solutionList);

    QString path(QStandardPaths::locate(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory) + QGuiApplication::applicationName());
    QDir dir(path);
    if(!dir.exists()) {
        if (!dir.mkpath(".")) {
            qWarning() << "Could not create settings path";
            return;
        }
    }

    QFile levelFile;
    levelFile.setFileName(path + "/level-" + QString::number(m_level->id()) + ".json");
    if (!levelFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open level file" << levelFile.fileName();
        return;
    }

    QTextStream stream(&levelFile);
    stream << QJsonDocument::fromVariant(levelMap).toJson();
    levelFile.close();
    qDebug() << "Level saved successfully" << levelFile.fileName();
}

void LevelCreator::createBlock(const int &index)
{
    QPoint coordinates = getCoordinates(index);
    qDebug() << "create block" << index << " -> " << coordinates.x() <<  coordinates.y();

    Block *block = 0;

    if (twoVerticalToolSelected()) {
        block = new Block(m_level->blocks()->count() + 1, coordinates.x(), coordinates.y(), 2, 1, m_level);
    } else if (twoHorizontalToolSelected()) {
        block = new Block(m_level->blocks()->count() + 1, coordinates.x(), coordinates.y(), 1, 2, m_level);
    } else if (threeHorizontalToolSelected()) {
        block = new Block(m_level->blocks()->count() + 1, coordinates.x(), coordinates.y(), 1, 3, m_level);
    } else if (threeVerticalToolSelected()) {
        block = new Block(m_level->blocks()->count() + 1, coordinates.x(), coordinates.y(), 3, 1, m_level);
    } else {
        clearToolSelections();
        return;
    }

    QList<QPoint> possitions = possiblePositions(block);

    if (!possitions.contains(coordinates)) {
        clearToolSelections();
        return;
    }

    m_level->blocks()->addBlock(block);
    m_board->updateBoardGrid();
    clearToolSelections();
    Board::printBoard(m_board->boardGrid());
}

void LevelCreator::removeBlock(const int &id)
{
    if (id == 0) {
        clearToolSelections();
        return;
    }

    qDebug() << "Remove block" << id;
    Block * block = m_level->blocks()->get(id);
    m_level->blocks()->removeBlock(block);
    block->deleteLater();
    clearToolSelections();
    Board::printBoard(m_board->boardGrid());
}

void LevelCreator::clearBoard()
{
    initLevel();
    clearToolSelections();
}

bool LevelCreator::deleteToolSelected() const
{
    return m_deleteToolSelected;
}

void LevelCreator::setDeleteToolSelected(const bool &selected)
{
    clearToolSelections();
    m_deleteToolSelected = selected;
    emit deleteToolSelectedChanged();
}

bool LevelCreator::twoHorizontalToolSelected() const
{
    return m_twoHorizontalToolSelected;
}

void LevelCreator::setTwoHorizontalToolSelected(const bool &selected)
{
    clearToolSelections();
    setAddMode(selected);
    m_twoHorizontalToolSelected = selected;
    emit twoHorizontalToolSelectedChanged();
}

bool LevelCreator::twoVerticalToolSelected() const
{
    return m_twoVerticalToolSelected;
}

void LevelCreator::setTwoVerticalToolSelected(const bool &selected)
{
    clearToolSelections();
    setAddMode(selected);
    m_twoVerticalToolSelected = selected;
    emit twoVerticalToolSelectedChanged();
}

bool LevelCreator::threeHorizontalToolSelected() const
{
    return m_threeHorizontalToolSelected;
}

void LevelCreator::setThreeHorizontalToolSelected(const bool &selected)
{
    clearToolSelections();
    setAddMode(selected);
    m_threeHorizontalToolSelected = selected;
    emit threeHorizontalToolSelectedChanged();
}

bool LevelCreator::threeVerticalToolSelected() const
{
    return m_threeVerticalToolSelected;
}

void LevelCreator::setThreeVerticalToolSelected(const bool &selected)
{
    clearToolSelections();
    setAddMode(selected);
    m_threeVerticalToolSelected = selected;
    emit threeVerticalToolSelectedChanged();
}

bool LevelCreator::addMode() const
{
    return m_addMode;
}

void LevelCreator::setAddMode(const bool &addMode)
{
    m_addMode = addMode;
    emit addModeChanged();
}

Board *LevelCreator::board()
{
    return m_board;
}

void LevelCreator::onLevelCountChanged(const int &count)
{
    m_level->setId(count + 1);
}

void LevelCreator::initLevel()
{
    clearToolSelections();
    m_level->setName("Level " + QString::number(m_level->id()));
    m_level->setHeight(m_height);
    m_level->setWidth(m_width);
    m_board->clearSolution();

    m_level->destroyBlocks();

    // add start block
    m_level->blocks()->addBlock(new Block(0, (int)(qrand() % 3), 2, 1, 2, m_level));
    m_board->loadLevel(m_level);
}

QPoint LevelCreator::getCoordinates(const int &index)
{
    int i = 0;
    for (int y = 0; y < m_board->boardGrid().length(); y++) {
        for (int x = 0; x < m_board->boardGrid()[y].length(); x++) {
            if (i == index) {
                return QPoint(x, y);
            } else {
                i++;
            }
        }
    }
    return QPoint();
}

QList<QPoint> LevelCreator::possiblePositions(Block *block)
{
    QList<QPoint> possiblePositions;
    if (block->orientation() == Block::Vertical) {
        for (int y = 0; y < m_board->boardGrid().length(); y++) {
            for (int x = 0; x < m_board->boardGrid()[y].length(); x++) {
                // check if cell is free
                if (m_board->boardGrid()[x][y].blockId() == -1) {
                    // check if enough space for block
                    if (block->height() + y <= m_height) {
                        bool free = true;
                        for (int i = 0; i < block->height(); i++) {
                            if (m_board->boardGrid()[x][y + i].blockId() != -1) {
                                free = false;
                                break;
                            }
                        }

                        if (free)
                            possiblePositions.append(QPoint(x,y));
                    }
                }
            }
        }
    } else if (block->orientation() == Block::Horizontal) {
        for (int y = 0; y < m_board->boardGrid().length(); y++) {
            for (int x = 0; x < m_board->boardGrid()[y].length(); x++) {
                // check if cell is free
                if (m_board->boardGrid()[x][y].blockId() == -1) {
                    // dont place it in the same row as the 0 block
                    if (y != m_level->blocks()->get(0)->y()) {
                        // check if enough space for block
                        if (block->width() + x <= m_width) {
                            bool free = true;
                            for (int i = 0; i < block->width(); i++) {
                                if (m_board->boardGrid()[x + i][y].blockId() != -1) {
                                    free = false;
                                    break;
                                }
                            }

                            if (free)
                                possiblePositions.append(QPoint(x,y));

                        }
                    }
                }
            }
        }
    }
    return possiblePositions;
}

void LevelCreator::onGridChanged()
{
    qDebug() << "grid changed";
    clearToolSelections();
    m_board->clearSolution();
}

void LevelCreator::clearToolSelections()
{
    m_deleteToolSelected = false;
    emit deleteToolSelectedChanged();

    m_twoHorizontalToolSelected = false;
    emit twoHorizontalToolSelectedChanged();

    m_twoVerticalToolSelected = false;
    emit twoVerticalToolSelectedChanged();

    m_threeHorizontalToolSelected = false;
    emit threeHorizontalToolSelectedChanged();

    m_threeVerticalToolSelected = false;
    emit threeVerticalToolSelectedChanged();

    setAddMode(false);
}


