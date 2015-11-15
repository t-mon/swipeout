#ifndef BLOCKS_H
#define BLOCKS_H

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
