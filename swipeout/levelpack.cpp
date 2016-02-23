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

#include "levelpack.h"

#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QJsonDocument>

LevelPack::LevelPack(const QString &levelDir, const QString &name, QObject *parent) :
    QObject(parent),
    m_levelDir(levelDir),
    m_name(name),
    m_levels(new Levels(this)),
    m_difficulty(0)
{

}

QString LevelPack::name() const
{
    return m_name;
}

void LevelPack::setName(const QString &name)
{
    m_name = name;
}

Levels *LevelPack::levels()
{
    return m_levels;
}

int LevelPack::difficulty() const
{
    return m_difficulty;
}

void LevelPack::setDifficulty(const int &difficulty)
{
    m_difficulty = difficulty;
}

int LevelPack::levelCount() const
{
    return m_levelCount;
}

void LevelPack::setLevelCount(const int &levelCount)
{
    m_levelCount = levelCount;
    emit levelCountChanged();
}

int LevelPack::completedCount() const
{
    return m_completedCount;
}

void LevelPack::setCompletedCount(const int &completedCount)
{
    m_completedCount = completedCount;
    emit completedCountChanged();
}

int LevelPack::completedPerfectCount() const
{
    return m_completedPerfectCount;
}

void LevelPack::setCompletedPerfectCount(const int &completedPerfectCount)
{
    m_completedPerfectCount = completedPerfectCount;
    emit completedPerfectCountChanged();
}

void LevelPack::loadLevels()
{
    qDebug() << "Loading level pack"<< m_name <<  "from" << m_levelDir;

    QDir dir(m_levelDir + "/" + m_name);
    qDebug() << "Loading level pack" << dir.path();
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList levelFiles = dir.entryInfoList();
    foreach (const QFileInfo &levelFileInfo, levelFiles) {
        if (!levelFileInfo.fileName().startsWith("level") || !levelFileInfo.fileName().endsWith(".json"))
            continue;

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
        level->setBlockData(levelData.value("blocks").toList());
        level->setLevelPackName(m_name);

        // load solution moves
        QList<Move> moves;
        foreach (const QVariant &moveData, levelData.value("solution").toList()) {
            QVariantMap moveMap = moveData.toMap();
            Move move(moveMap.value("block").toInt(), moveMap.value("step").toInt(), moveMap.value("delta").toInt());
            moves.append(move);
        }
        qSort(moves.begin(), moves.end(), compareMove);

        QStack<Move> solution;
        for (int i = 0; i < moves.count(); i++)
            solution.push(moves.at(i));

        level->setSolution(solution);
        m_levels->addLevel(level);
    }
    loadLevelSettings();
    calculateStatistic();
}

void LevelPack::loadLevelSettings()
{
    foreach (Level *level, m_levels->levels()) {
        // load record / completed
        QSettings settings;
        settings.beginGroup("levelpacks");
        settings.beginGroup(m_name);
        settings.beginGroup(level->name());
        level->setCompleted(settings.value("completed", false).toBool());
        level->setCompletedPerfect(settings.value("completedPerfect", false).toBool());
        level->setRecord(settings.value("record", 0).toInt());
        settings.endGroup();
        settings.endGroup();
        settings.endGroup();
    }
}

void LevelPack::unloadLevels()
{
    qDebug() << "Unload levels from levelpack" << m_name;
    m_levels->deleteAllLevels();
}

void LevelPack::calculateStatistic()
{
    qDebug() << "Calculate statistics";
    setLevelCount(m_levels->levels().count());
    int completed = 0;
    int completedPerfect = 0;

    foreach (Level *level, m_levels->levels()) {
        if (level->completed())
            completed++;

        if (level->completedPerfect())
            completedPerfect++;
    }
    qDebug() << "   completed        " << completed << "/" << m_levels->levels().count();
    qDebug() << "   completed perfect" << completedPerfect << "/" << m_levels->levels().count();

    setCompletedCount(completed);
    setCompletedPerfectCount(completedPerfect);
}
