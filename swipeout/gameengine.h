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
#include "levelcreator.h"
#include "board.h"
#include "boardsolver.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Levels *levels READ levels CONSTANT)
    Q_PROPERTY(Levels *loadedLevels READ loadedLevels CONSTANT)
    Q_PROPERTY(LevelCreator *levelCreator READ levelCreator CONSTANT)
    Q_PROPERTY(Board *board READ board CONSTANT)
    Q_PROPERTY(QString levelDir READ levelDir WRITE setLevelDir NOTIFY levelDirChanged)
    Q_PROPERTY(bool solverRunning READ solverRunning NOTIFY solverRunningChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QString levelDir() const;
    void setLevelDir(const QString &levelDir);

    Levels *levels();
    Levels *loadedLevels();
    LevelCreator *levelCreator();
    Board *board();

    Q_INVOKABLE bool startLevel(const int &id);
    Q_INVOKABLE void solveBoard();
    Q_INVOKABLE void solveCreatorBoard();

    Q_INVOKABLE void loadCreatedLevels();

    bool solverRunning() const;

private:
    QString m_levelDir;
    Levels *m_levels;
    Levels *m_loadedLevels;
    LevelCreator *m_levelCreator;
    Board *m_board;
    BoardSolver *m_solver;
    QFutureWatcher<QStack<Move> > *m_watcher;

    QDateTime m_timestamp;
    bool m_solverRunning;
    Board *m_solverBoard;

    void loadLevels();
    bool levelAlreadyLoaded(const int &id);

    void setSolverRunning(const bool &solverRunning);

private slots:
    void onSolverFinished();

signals:
    void levelDirChanged();
    void solverRunningChanged();

};

#endif // GAMEENGINE_H
