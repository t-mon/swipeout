#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>

#include "levels.h"
#include "board.h"

class GameEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Levels *levels READ levels NOTIFY levelsChanged)
    Q_PROPERTY(Board *board READ board NOTIFY levelsChanged)
    Q_PROPERTY(QString levelDir READ levelDir WRITE setLevelDir NOTIFY levelDirChanged)

public:
    explicit GameEngine(QObject *parent = 0);

    QString levelDir() const;
    void setLevelDir(const QString &levelDir);

    Levels *levels();
    Board *board();

    Q_INVOKABLE void loadLevel(const int &id);

private:
    QString m_levelDir;
    Levels *m_levels;
    Board *m_board;

    void loadLevels();

signals:
    void levelDirChanged();
    void levelsChanged();

};

#endif // GAMEENGINE_H
