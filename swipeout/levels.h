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

#ifndef LEVELS_H
#define LEVELS_H

#include <QObject>
#include <QAbstractListModel>

#include "level.h"

class Levels : public QAbstractListModel
{
    Q_OBJECT

public:
    enum LevelRole {
        NameRole,
        IdRole,
        WidthRole,
        HeightRole,
        SolutionAvailableRole
    };

    explicit Levels(QObject *parent = 0);

    QList<Level *> levels();
    Q_INVOKABLE Level *get(int id);
    bool containsLevel(const int &id);


    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addLevel(Level* level);
    void resetLevelSettings();
    void sortLevels();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Level *> m_levels;

};

bool compareLevel(Level *level1, Level *level2);


#endif // LEVELS_H
