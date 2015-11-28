#ifndef LEVELPACK_H
#define LEVELPACK_H

#include <QObject>

#include "levels.h"

class LevelPack : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(Levels *levels READ levels CONSTANT)
    Q_PROPERTY(int levelCount READ levelCount WRITE setLevelCount NOTIFY levelCountChanged)
    Q_PROPERTY(int completedCount READ completedCount WRITE setCompletedCount NOTIFY completedCountChanged)
    Q_PROPERTY(int completedPerfectCount READ completedPerfectCount WRITE setCompletedPerfectCount NOTIFY completedPerfectCountChanged)

public:
    explicit LevelPack(const QString &levelDir, const QString &name, QObject *parent = 0);

    QString name() const;
    void setName(const QString &name);

    Levels *levels();

    int levelCount() const;
    void setLevelCount(const int &levelCount);

    int completedCount() const;
    void setCompletedCount(const int &completedCount);

    int completedPerfectCount() const;
    void setCompletedPerfectCount(const int &completedPerfectCount);

    void loadLevels();
    void loadLevelSettings();
    void unloadLevels();

    Q_INVOKABLE void calculateStatistic();

private:
    QString m_levelDir;
    QString m_name;
    Levels *m_levels;

    int m_levelCount;
    int m_completedCount;
    int m_completedPerfectCount;

signals:
    void levelCountChanged();
    void completedCountChanged();
    void completedPerfectCountChanged();

};

#endif // LEVELPACK_H
