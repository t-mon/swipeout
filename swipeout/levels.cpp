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

#include "levels.h"

Levels::Levels(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Level *> Levels::levels()
{
    return m_levels;
}

Level *Levels::get(int id)
{
    foreach (Level *level, m_levels) {
        if (level->id() == id)
            return level;
    }
    return NULL;
}

int Levels::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_levels.count();
}

QVariant Levels::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_levels.count())
        return QVariant();

    Level *level= m_levels.at(index.row());
    if (role == IdRole) {
        return level->id();
    } else if (role == NameRole) {
        return level->name();
    } else if (role == WidthRole) {
        return level->width();
    } else if (role == HeightRole) {
        return level->height();
    }
    return QVariant();
}

void Levels::addLevel(Level *level)
{
    beginInsertRows(QModelIndex(), m_levels.count(), m_levels.count());
    m_levels.append(level);
    endInsertRows();
    QModelIndex i = index(m_levels.indexOf(level));
    emit dataChanged(i, i);
}

void Levels::resetLevelSettings()
{

}

void Levels::sortLevels()
{
    beginResetModel();
    qSort(m_levels.begin(), m_levels.end(), compareLevel);
    endResetModel();
}

QHash<int, QByteArray> Levels::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "levelId";
    roles[NameRole] = "levelName";
    roles[WidthRole] = "levelWidth";
    roles[HeightRole] = "levelHeigth";
    return roles;
}

bool compareLevel(Level *level1, Level *level2)
{
    return level1->id() < level2->id();
}
