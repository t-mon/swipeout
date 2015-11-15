#include "levels.h"

Levels::Levels(QObject *parent) :
    QAbstractListModel(parent)
{
}

QList<Level *> Levels::levels()
{
    return m_levels;
}

Level *Levels::level(int id)
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
