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

#include "blocks.h"

Blocks::Blocks(QObject *parent) :
    QAbstractListModel(parent)
{
}

Blocks::Blocks(Blocks *other, QObject *parent = 0):
    QAbstractListModel(parent)
{
    foreach (Block *block, other->blocks()) {
        addBlock(new Block(block, parent));
    }
}

QList<Block *> Blocks::blocks()
{
    return m_blocks;
}

Block *Blocks::get(int id)
{
    foreach (Block *block, m_blocks) {
        if (block->id() == id)
            return block;
    }
    return NULL;
}

int Blocks::count() const
{
    return m_blocks.count();
}

void Blocks::resetBlockPositions()
{
    foreach (Block *block, m_blocks) {
        block->resetPosition();
    }
}

int Blocks::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_blocks.count();
}

QVariant Blocks::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= m_blocks.count())
        return QVariant();

    Block *block= m_blocks.at(index.row());
    if (role == IdRole) {
        return block->id();
    } else if (role == XRole) {
        return block->x();
    } else if (role == YRole) {
        return block->y();
    } else if (role == HeightRole) {
        return block->height();
    } else if (role == WidthRole) {
        return block->width();
    } else if (role == ColorRole) {
        return block->color();
    }
    return QVariant();
}

void Blocks::addBlock(Block *block)
{
    beginInsertRows(QModelIndex(), m_blocks.count(), m_blocks.count());
    m_blocks.append(block);
    endInsertRows();
}

void Blocks::removeBlock(Block *block)
{
    int index = m_blocks.indexOf(block);
    beginRemoveRows(QModelIndex(), index, index);
    m_blocks.removeAt(index);
    endRemoveRows();
    block->deleteLater();
}

void Blocks::deleteAllBlocks()
{
    foreach (Block *block, m_blocks) {
        removeBlock(block);
    }
}

QHash<int, QByteArray> Blocks::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "blockId";
    roles[XRole] = "blockX";
    roles[YRole] = "blockY";
    roles[WidthRole] = "blockWidth";
    roles[HeightRole] = "blockHeigth";
    roles[ColorRole] = "blockColor";
    return roles;
}
