#ifndef BLOCKS_H
#define BLOCKS_H

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

#include <QObject>
#include <QAbstractListModel>

#include "block.h"

class Blocks : public QAbstractListModel
{
    Q_OBJECT

public:
    enum BlockRole {
        IdRole,
        XRole,
        YRole,
        WidthRole,
        HeightRole
    };

    explicit Blocks(QObject *parent = 0);

    QList<Block *> blocks();
    Q_INVOKABLE Block *get(int id);
    Q_INVOKABLE void resetBlockPositions();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    void addBlock(Block* block);

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Block *> m_blocks;

};

#endif // BLOCKS_H
