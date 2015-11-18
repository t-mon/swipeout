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
#include "board.h"
#include "boardsolver.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Levels *levels READ levels NOTIFY levelsChanged)
    Q_PROPERTY(Board *board READ board NOTIFY levelsChanged)
    Q_PROPERTY(QString levelDir READ levelDir WRITE setLevelDir NOTIFY levelDirChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QString levelDir() const;
    void setLevelDir(const QString &levelDir);

    Levels *levels();
    Board *board();

    Q_INVOKABLE bool startLevel(const int &id);
    Q_INVOKABLE void solveBoard();

private:
    QString m_levelDir;
    Levels *m_levels;
    Board *m_board;
    BoardSolver *m_solver;
    QFutureWatcher<QStack<Move> > *m_watcher;

    QDateTime m_timestamp;

    void loadLevels();

private slots:
    void onSolverFinished();

signals:
    void levelDirChanged();
    void levelsChanged();

};

#endif // GAMEENGINE_H
