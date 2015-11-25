#ifndef LEVELPACK_H
#define LEVELPACK_H

#include <QObject>

#include "levels.h"

class LevelPack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(Levels *levels READ levels CONSTANT)

public:
    explicit LevelPack(const QString &levelDir, const QString &name, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    Levels *levels();

    void loadLevels();
    void unloadLevels();

private:
    QString m_levelDir;
    QString m_name;
    Levels *m_levels;

};

#endif // LEVELPACK_H
