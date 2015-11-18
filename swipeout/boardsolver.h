#ifndef BOARDSOLVER_H
#define BOARDSOLVER_H

#include <QObject>
#include <QThread>
#include <QList>

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


class BoardSolver : public QThread
{
    Q_OBJECT
public:
    BoardSolver(Board *board, QObject *parent = 0);

private:
    QStack<Move> m_solutionPath;

    Blocks *m_blocks;
    int m_width;
    int m_height;

    Node *m_startNode;

    QList<Node *> m_openList;
    QList<Node *> m_closedList;

    bool solve(Board *board);

    void expand(Node *currentNode);
    void insertInOpenList(Node *node);
    void removeFromOpenList(Node *node);

    bool inOpenList(Node *node);
    bool inClosedList(Node *node);

protected:
    void run();

signals:
    void solutionFound(QStack<Move> solution);

};

bool openListLessThan(Node *a, Node *b);

#endif // BOARDSOLVER_H
