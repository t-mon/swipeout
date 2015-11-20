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
    m_board(new Board(this)),
    m_level(0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
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
    if (!m_level)
        m_level = new Level(this);

    m_level->destroyBlocks();

    m_level->setId((int)(qrand() % (99999 - 999 + 1) + 999));
    m_level->setName("Random " + QString::number(m_level->id()));
    m_level->setHeight(m_height);
    m_level->setWidth(m_width);

    qDebug() << "------------------------------------";
    qDebug() << "Create random level: " << m_level->name();

    // add start block
    m_level->blocks()->addBlock(new Block(0, (int)(qrand() % 2), 2, 1, 2, m_level));

    initGrid();

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
            QList<QPoint> possiblePositions;

            for (int y = 0; y < m_boardGrid.length(); y++) {
                for (int x = 0; x < m_boardGrid[y].length(); x++) {
                    // check if cell is free
                    if (m_boardGrid[x][y].blockId() == -1) {
                        // check if enough space for block
                        if (block->height() + y <= m_height) {
                            bool free = true;
                            for (int i = 0; i < block->height(); i++) {
                                if (m_boardGrid[x][y + i].blockId() != -1) {
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

            int index = qrand() % possiblePositions.length();
            QPoint finalPosition = possiblePositions.at(index);
            block->setX(finalPosition.x());
            block->setY(finalPosition.y());
            m_level->blocks()->addBlock(block);
            initGrid();
        } else if (block->orientation() == Block::Horizontal) {
            QList<QPoint> possiblePositions;

            for (int y = 0; y < m_boardGrid.length(); y++) {
                for (int x = 0; x < m_boardGrid[y].length(); x++) {
                    // check if cell is free
                    if (m_boardGrid[x][y].blockId() == -1) {
                        // dont place it in the same row as the 0 block
                        if (block->y() != m_level->blocks()->get(0)->y()) {
                            // check if enough space for block
                            if (block->width() + x <= m_width) {
                                bool free = true;
                                for (int i = 0; i < block->width(); i++) {
                                    if (m_boardGrid[x + i][y].blockId() != -1) {
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

            if (possiblePositions.isEmpty()) {
                block->deleteLater();
            } else {
                int index = qrand() % possiblePositions.length();
                QPoint finalPosition = possiblePositions.at(index);
                block->setX(finalPosition.x());
                block->setY(finalPosition.y());
                m_level->blocks()->addBlock(block);
                initGrid();
            }
        }
    }

    qDebug() << " All blocks";
    foreach (Block *block, m_level->blocks()->blocks()) {
        qDebug() << " -> Block" << block->id() << ":" << block->width() << "x" << block->height();
    }

    m_board->loadLevel(m_level, true);
}

void LevelCreator::saveLevel()
{
    QVariantMap levelMap;
    levelMap.insert("name", "Level " + QString::number(m_level->id()));
    levelMap.insert("id", m_level->id());
    levelMap.insert("height", m_level->height());
    levelMap.insert("width", m_level->width());
    levelMap.insert("minimalMoveCount", m_level->minimalMoveCount());

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

Board *LevelCreator::board()
{
    return m_board;
}

void LevelCreator::initGrid()
{
    m_boardGrid.clear();
    m_boardGrid.resize(m_width);
    for (int x = 0; x < m_width; x++) {
        QVector<BoardCell> line;
        line.resize(m_height);
        for (int y = 0; y < m_height; y++) {
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
}


