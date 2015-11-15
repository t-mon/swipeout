#include "blocks.h"

Blocks::Blocks(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Block *> Blocks::blocks()
{
    return m_blocks;
}

Block *Blocks::block(int id)
{
    foreach (Block *block, m_blocks) {
        if (block->id() == id)
            return block;
    }
    return NULL;
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
    }
    return QVariant();
}

void Blocks::addBlock(Block *block)
{
    beginInsertRows(QModelIndex(), m_blocks.count(), m_blocks.count());
    m_blocks.append(block);
    endInsertRows();
}

QHash<int, QByteArray> Blocks::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "blockId";
    roles[XRole] = "blockX";
    roles[XRole] = "blockY";
    roles[WidthRole] = "blockWidth";
    roles[HeightRole] = "blockHeigth";
    return roles;
}
