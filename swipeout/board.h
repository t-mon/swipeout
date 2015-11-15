#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QVector>

#include "level.h"

class BoardCell
{
public:
    BoardCell(const int &x = 0, const int &y = 0, const int &blockId = -1);

    int x() const;
    int y() const;

    int blockId() const;
    void setBlockId(const int &blockId);

private:
    int m_x;
    int m_y;
    int m_blockId;
};


class Board : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Level* level READ level NOTIFY levelChanged)
    Q_PROPERTY(int moveCount READ moveCount NOTIFY moveCountChanged)

public:
    explicit Board(QObject *parent = 0);

    void clearLevel();
    Q_INVOKABLE void resetBoard();
    void loadLevel(Level *level);

    Level *level();

    int moveCount() const;

    QVector<QVector<BoardCell> > m_board;

    Q_INVOKABLE int calculateLeftLimit(const int &blockId);
    Q_INVOKABLE int calculateRightLimit(const int &blockId);
    Q_INVOKABLE int calculateUpperLimit(const int &blockId);
    Q_INVOKABLE int calculateLowerLimit(const int &blockId);

    Q_INVOKABLE void moveBlockX(const int &id, const int &newX);
    Q_INVOKABLE void moveBlockY(const int &id, const int &newY);

private:
    Level *m_level;
    int m_moveCount;

    void initBoard();
    void setMoveCount(const int &moveCount);
    void printBoard();

signals:
    void moveCountChanged();
    void levelCompleted();
    void levelChanged();
};

#endif // BOARD_H
