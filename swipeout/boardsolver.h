#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H

#include <QObject>
#include <QList>
#include <QMutex>

#include "board.h"
#include "block.h"
#include "blocks.h"

class Node : public QObject
{
    Q_OBJECT

public:
    Node(QObject *parent = 0);

    Move move() const;
    void setMove(const Move &move);

    Node *parentNode() const;
    void setParentNode(Node* parentNode);

    // f = g + h (A* algorithm)
    int f() const;

     // g... costs from start to this node
    int g() const;
    void setG(const int &g);

     // h...heuristic estimate (vector length
    int h() const;
    void setH(const int &h);

    Blocks *blocks();
    void setBlocks(Blocks *blocks, const int &width, const int &height);

    QVector<QVector<BoardCell> > boardGrid() const;

    bool operator==(Node *other);

private:
    Move m_move;

    int m_f;
    int m_g;
    int m_h;

    Blocks *m_blocks;
    Node *m_parentNode;
    QVector<QVector<BoardCell> > m_boardGrid;
};


class BoardSolver : public QObject
{
    Q_OBJECT
public:
    BoardSolver(QObject *parent = 0);

    QStack<Move> calculateSolution(Board *board);
    void stopSolver();

private:
    QObject *m_object;
    Blocks *m_blocks;
    int m_width;
    int m_height;

    Node *m_startNode;

    QList<Node *> m_openList;
    QList<Node *> m_closedList;

    void expand(Node *currentNode);

    bool inOpenList(Node *node);
    bool inClosedList(Node *node);

    void cleanUp();

    QMutex m_cancelMutex;
    bool m_cancel;

signals:
    void solutionFound(const QStack<Move> &solution);

};

bool openListLessThan(Node *a, Node *b);

#endif // BOARDSOLVER_H
