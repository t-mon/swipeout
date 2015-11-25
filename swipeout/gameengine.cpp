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
#include "move.h"

#include <QDir>
#include <QDebug>
#include <QJsonDocument>
#include <QGuiApplication>
#include <QtConcurrent/QtConcurrent>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    m_levelPack(0),
    m_levelPacks(new LevelPacks(this)),
    m_createdLevels(new Levels(this)),
    m_levelCreator(new LevelCreator(this)),
    m_board(new Board(this)),
    m_solver(new BoardSolver(this)),
    m_watcher(new QFutureWatcher<QStack<Move> >(this)),
    m_solverRunning(false)
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
    loadLevelPacks();
    loadCreatedLevels();
    emit levelDirChanged();
}

LevelPack *GameEngine::levelPack()
{
    return m_levelPack;
}

LevelPacks *GameEngine::levelPacks()
{
    return m_levelPacks;
}

LevelCreator *GameEngine::levelCreator()
{
    return m_levelCreator;
}

Board *GameEngine::board()
{
    return m_board;
}

void GameEngine::loadLevelPack(const QString &name)
{
    LevelPack *levelPack = m_levelPacks->get(name);

    if (!levelPack) {
        qWarning() << "Could not find level pack" << name;
        return;
    }

    // check if already loaded
    if (levelPack == m_levelPack) {
        qWarning() << "Level pack" << name << "already loaded";
        return;
    }

    m_board->clearLevel();

    if (m_levelPack)
        m_levelPack->unloadLevels();

    m_levelPack = levelPack;
    emit levelPackChanged();

    m_levelPack->loadLevels();
}

void GameEngine::solveBoard()
{
    m_timestamp = QDateTime::currentDateTime();
    setSolverRunning(true);
    m_solverBoard = m_levelCreator->board();
    foreach (Block *block, m_solverBoard->level()->blocks()->blocks()) {
        block->setStartX(block->x());
        block->setStartY(block->y());
    }
    m_watcher->setFuture(QtConcurrent::run(m_solver, &BoardSolver::calculateSolution, m_levelCreator->board()));
}

void GameEngine::stopSolvingBoard()
{
    qDebug() << "Cancel solving process.";
    m_solver->stopSolver();
}

Levels *GameEngine::loadedLevels()
{
    return m_createdLevels;
}

void GameEngine::loadCreatedLevels()
{
    QString fileDir = QStandardPaths::locate(QStandardPaths::ConfigLocation, QString(), QStandardPaths::LocateDirectory) + QGuiApplication::applicationName();

    QDir dir(fileDir);
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
        if (levelAlreadyLoaded(levelData.value("id").toInt())) {
            qWarning() << "Level" << levelData.value("id").toInt() << "already loaded -> skipping";
            continue;
        }

        qDebug() << "   -> loading created level" << levelData.value("id").toInt() << "...";
        Level *level = new Level(this);
        level->setName(levelData.value("name").toString());
        level->setId(levelData.value("id").toInt());
        level->setHeight(levelData.value("height").toInt());
        level->setWidth(levelData.value("width").toInt());
        level->setBlockData(levelData.value("blocks").toList());

        // load solution moves
        QList<Move> moves;
        foreach (const QVariant &moveData, levelData.value("solution").toList()) {
            QVariantMap moveMap = moveData.toMap();
            Move move(moveMap.value("block").toInt(), moveMap.value("step").toInt(), moveMap.value("delta").toInt());
            moves.append(move);
        }
        qSort(moves.begin(), moves.end(), compareMove);

        QStack<Move> solution;
        for (int i = 0; i < moves.count(); i++) {
            solution.push(moves.at(i));
        }
        level->setSolution(solution);
        m_createdLevels->addLevel(level);
    }
    m_levelCreator->onLevelCountChanged(m_createdLevels->levels().count());
}

bool GameEngine::solverRunning() const
{
    return m_solverRunning;
}

void GameEngine::loadLevelPacks()
{
    qDebug() << "Loading level packs" << m_levelDir;
    QDir dir(m_levelDir);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    dir.setSorting(QDir::Name);

    QFileInfoList levelFiles = dir.entryInfoList();
    foreach (const QFileInfo &levelFileInfo, levelFiles) {
        qDebug() << levelFileInfo.fileName();
        m_levelPacks->addLevelPack(new LevelPack(m_levelDir, levelFileInfo.fileName(), this));
    }
}

bool GameEngine::levelAlreadyLoaded(const int &id)
{
    foreach (Level *level, m_createdLevels->levels()) {
        if (level->id() == id) {
            return true;
        }
    }
    return false;
}

void GameEngine::setSolverRunning(const bool &solverRunning)
{
    m_solverRunning = solverRunning;
    emit solverRunningChanged();
}

void GameEngine::onSolverFinished()
{
    setSolverRunning(false);
    QDateTime time = QDateTime::fromMSecsSinceEpoch(QDateTime::currentMSecsSinceEpoch() - m_timestamp.toMSecsSinceEpoch());
    QStack<Move> solution = m_watcher->future().result();
    if (solution.isEmpty()) {
        qDebug() << "----------------------------------";
        qDebug() << "No solution found";
        qDebug() << "Process time:" << time.toString("mm:ss.zzz");
        qDebug() << "----------------------------------";
    } else {
        qDebug() << "----------------------------------";
        qDebug() << "Solution found!";
        foreach (const Move &move, solution) {
            qDebug() << "    " << move.step() << "|" << move.id() << " -> " << move.delta();
        }
        qDebug() << "----------------------------------";
        qDebug() << "Solvable in" <<  solution.count() << "moves!";
        qDebug() << "Process time:" << time.toString("mm:ss.zzz");
        qDebug() << "----------------------------------";
    }
    m_solverBoard->level()->setSolution(solution);
    m_solverBoard->setSolution(solution);

    emit solutionReady(time.toString("mm:ss.zzz"));
}

