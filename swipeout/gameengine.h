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

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QFuture>
#include <QDateTime>

#include "levels.h"
#include "levelpack.h"
#include "levelpacks.h"
#include "levelcreator.h"
#include "board.h"
#include "boardsolver.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(LevelPack *levelPack READ levelPack NOTIFY levelPackChanged)
    Q_PROPERTY(LevelPacks *levelPacks READ levelPacks CONSTANT)
    Q_PROPERTY(Levels *loadedLevels READ loadedLevels CONSTANT)
    Q_PROPERTY(LevelCreator *levelCreator READ levelCreator CONSTANT)
    Q_PROPERTY(Board *board READ board CONSTANT)
    Q_PROPERTY(QString levelDir READ levelDir WRITE setLevelDir NOTIFY levelDirChanged)
    Q_PROPERTY(bool solverRunning READ solverRunning NOTIFY solverRunningChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QString levelDir() const;
    void setLevelDir(const QString &levelDir);

    LevelPack *levelPack();
    LevelPacks *levelPacks();
    LevelCreator *levelCreator();
    Board *board();

    Q_INVOKABLE void loadLevelPack(const QString &name);

    Q_INVOKABLE void solveBoard();
    Q_INVOKABLE void stopSolvingBoard();

    Levels *loadedLevels();
    Q_INVOKABLE void loadCreatedLevels();

    bool solverRunning() const;

private:
    QString m_levelDir;
    LevelPack *m_levelPack;
    LevelPacks *m_levelPacks;
    Levels *m_createdLevels;
    LevelCreator *m_levelCreator;
    Board *m_board;
    BoardSolver *m_solver;
    QFutureWatcher<QStack<Move> > *m_watcher;

    QDateTime m_timestamp;
    bool m_solverRunning;
    Board *m_solverBoard;

    void loadLevelPacks();
    bool levelAlreadyLoaded(const int &id);

    void setSolverRunning(const bool &solverRunning);

private slots:
    void onSolverFinished();

signals:
    void levelDirChanged();
    void solverRunningChanged();
    void solutionReady(const QString &runTime);
    void levelPackChanged();

};

#endif // GAMEENGINE_H
