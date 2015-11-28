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

#include "levelpacks.h"

LevelPacks::LevelPacks(QObject *parent) :
    QAbstractListModel(parent)
{

}

QList<LevelPack *> LevelPacks::levelPacks()
{
    return m_levelPacks;
}

LevelPack *LevelPacks::get(const QString &name)
{
    foreach (LevelPack *levelPack, m_levelPacks) {
        if (levelPack->name() == name){
            return levelPack;
        }
    }
    return NULL;
}

int LevelPacks::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_levelPacks.count();
}

QVariant LevelPacks::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_levelPacks.count())
        return QVariant();

    LevelPack *levelPack = m_levelPacks.at(index.row());
    if (role == NameRole) {
        return levelPack->name();
    } else if (role == LevelCountRole) {
        return levelPack->levelCount();
    } else if (role == CompletedCountRole) {
        return levelPack->completedCount();
    } else if (role == CompletedPerfectCountRole) {
        return levelPack->completedPerfectCount();
    }

    return QVariant();
}

void LevelPacks::addLevelPack(LevelPack *levelPack)
{
    beginInsertRows(QModelIndex(), m_levelPacks.count(), m_levelPacks.count());
    m_levelPacks.append(levelPack);
    endInsertRows();
}

QHash<int, QByteArray> LevelPacks::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[LevelCountRole] = "levelCount";
    roles[CompletedCountRole] = "completedCount";
    roles[CompletedPerfectCountRole] = "completedPerfectCount";
    return roles;
}

