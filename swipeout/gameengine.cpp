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
#include "boardsolver.h"

#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QtConcurrent/QtConcurrent>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    m_levels(new Levels(this)),
    m_board(new Board(this)),
    m_solver(new BoardSolver(this)),
    m_watcher(new QFutureWatcher<QStack<Move> >(this))
{
    qDebug() << "Created game engine";

    connect(m_watcher, SIGNAL(finished()), this, SLOT(onSolverFinished()));
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

bool GameEngine::startLevel(const int &id)
{
    Level *level = m_levels->get(id);
    if (!level) {
        qWarning() << "Could not find level" << id;
        return false;
    }

    m_board->loadLevel(level);
    return true;
}

void GameEngine::solveBoard()
{
    m_timestamp = QDateTime::currentDateTime();
    m_watcher->setFuture(QtConcurrent::run(m_solver, &BoardSolver::calculateSolution, m_board));
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
        level->setBlockData(levelData.value("blocks").toList());
        m_levels->addLevel(level);
    }
}

void GameEngine::onSolverFinished()
{
    QDateTime time = QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - m_timestamp.toMSecsSinceEpoch());
    QStack<Move> solution = m_watcher->future().result();
    if (solution.isEmpty()) {
        qDebug() << "----------------------------------";
        qWarning() << "No solution found";
        qDebug() << "----------------------------------";
    } else {
        qDebug() << "----------------------------------";
        qDebug() << "Solution found!";
        foreach (const Move &move, solution) {
            qDebug() << "    " << move.id() << " -> " << move.delta();
        }
        qDebug() << "----------------------------------";
        qDebug() << "Solvable in" <<  solution.count() << "moves!";
        qDebug() << "Process time:" << time.toString("mm:ss.zzz");
        qDebug() << "----------------------------------";
    }
    m_board->setSolution(solution);
}
