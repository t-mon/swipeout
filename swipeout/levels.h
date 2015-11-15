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
        HeightRole
    };

    explicit Levels(QObject *parent = 0);

    QList<Level *> levels();
    Q_INVOKABLE Level *get(int id);

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
