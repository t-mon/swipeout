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

#ifndef LEVELPACKS_H
#define LEVELPACKS_H

#include <QObject>
#include <QAbstractListModel>

#include "levelpack.h"

class LevelPacks : public QAbstractListModel
{
    Q_OBJECT
public:
    enum LevelRole {
        NameRole,
        LevelCountRole,
        CompletedCountRole,
        CompletedPerfectCountRole
    };

    explicit LevelPacks(QObject *parent = 0);

    QList<LevelPack *> levelPacks();
    Q_INVOKABLE LevelPack *get(const QString &name);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addLevelPack(LevelPack *levelPack);
    void sortLevelPacks();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<LevelPack *> m_levelPacks;

};

bool compareLevelPacks(LevelPack *levelPack1, LevelPack *levelPack2);

#endif // LEVELPACKS_H
