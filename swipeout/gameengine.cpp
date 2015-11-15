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

#include "gameengine.h"

#include <QDir>
#include <QDebug>
#include <QJsonDocument>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    m_levels(new Levels(this)),
    m_board(new Board(this))
{
    qDebug() << "Created game engine";
}

QString GameEngine::levelDir() const
{
    return m_levelDir;
}

void GameEngine::setLevelDir(const QString &levelDir)
{
    m_levelDir = levelDir;
    loadLevels();
    emit levelDirChanged();
}

Levels *GameEngine::levels()
{
    return m_levels;
}

Board *GameEngine::board()
{
    return m_board;
}

void GameEngine::loadLevel(const int &id)
{
    qDebug() << "Start level" << id;
    Level *level = m_levels->get(id);
    m_board->loadLevel(level);
}

void GameEngine::loadLevels()
{
    qDebug() << "loading levels from" << m_levelDir;

    QDir dir(m_levelDir);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList levelFiles = dir.entryInfoList();
    foreach (const QFileInfo &levelFileInfo, levelFiles) {
        QFile levelFile(levelFileInfo.absoluteFilePath());
        if (!levelFile.open(QFile::ReadOnly)) {
            qDebug() << "Cannot open level file for reading:" << levelFileInfo.absoluteFilePath();
            continue;
        }

        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(levelFile.readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "Cannot parse level file:" << error.errorString();
            continue;
        }

        QVariantMap levelData = jsonDoc.toVariant().toMap();
        qDebug() << "   -> loading level" << levelData.value("id").toInt() << "...";
        Level *level = new Level(this);
        level->setName(levelData.value("name").toString());
        level->setId(levelData.value("id").toInt());
        level->setHeight(levelData.value("height").toInt());
        level->setWidth(levelData.value("width").toInt());

        foreach (const QVariant &blockVariant, levelData.value("blocks").toList()) {
            QVariantMap blockData = blockVariant.toMap();
            qDebug() << "      -> loading block" << blockData.value("id").toInt() << "...";
            Block *block = new Block(blockData.value("id").toInt(),
                                     blockData.value("x").toInt(),
                                     blockData.value("y").toInt(),
                                     blockData.value("height").toInt(),
                                     blockData.value("width").toInt(),
                                     level);
            level->addBlock(block);
        }

        m_levels->addLevel(level);
    }
}
