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

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<LevelPack *> m_levelPacks;
};

#endif // LEVELPACKS_H
