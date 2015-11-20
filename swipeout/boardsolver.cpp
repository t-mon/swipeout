#include "boardsolver.h"

#include <QDebug>

Node::Node(QObject *parent) :
    QObject(parent),
    m_f(0),
    m_g(0),
    m_h(0),
    m_blocks(0),
    m_parentNode(0)

{
}

Move Node::move() const
{
    return m_move;
}

void Node::setMove(const Move &move)
{
    m_move = move;
}

Node *Node::parentNode() const
{
    return m_parentNode;
}

void Node::setParentNode(Node *parentNode)
{
    m_parentNode = parentNode;
}

int Node::f() const
{
    return m_g + m_h;
}

int Node::g() const
{
    return m_g;
}

void Node::setG(const int &g)
{
    m_g = g;
}

int Node::h() const
{
    return m_h;
}

void Node::setH(const int &h)
{
    m_h = h;
}

Blocks *Node::blocks()
{
    return m_blocks;
}

void Node::setBlocks(Blocks *blocks, const int &width, const int &height)
{
    m_blocks = blocks;

    m_boardGrid.clear();
    m_boardGrid.resize(width);
    for (int x = 0; x < width; x++) {
        QVector<BoardCell> line;
        line.resize(height);
        for (int y = 0; y < height; y++) {
            line[y] = (BoardCell(x, y));
        }
        m_boardGrid[x] = line;
    }

    // set blocks
    foreach (Block *block, blocks->blocks()) {
        if (block->width() > block->height()) {
            for (int i = 0; i < block->width(); i++) {
                m_boardGrid[block->x()  + i][block->y()].setBlockId(block->id());
            }
        } else {
            for (int i = 0; i < block->height(); i++) {
                m_boardGrid[block->x()][block->y() + i].setBlockId(block->id());
            }
        }
    }

    // heuristic -> occupied stones between 0 and exit

    Block *block = blocks->get(0);

    int count = 0;
    for (int i = block->x() + block->width(); i < width; i++) {
        if (m_boardGrid[i][block->y()].blockId() != -1) {
            count += 1;
        }
    }
    setH(count);
}

QVector<QVector<BoardCell> > Node::boardGrid() const
{
    return m_boardGrid;
}

bool Node::operator==(Node *other)
{
    return other->boardGrid() == boardGrid();
}



BoardSolver::BoardSolver(QObject *parent) :
    QObject(parent)
{
}

QStack<Move> BoardSolver::calculateSolution(Board *board)
{
    m_object = new QObject();

    m_blocks = new Blocks(board->level()->blocks(), m_object);
    m_width = board->level()->width();
    m_height = board->level()->height();

    qDeleteAll(m_openList);
    m_openList.clear();

    qDeleteAll(m_closedList);
    m_closedList.clear();

    // create start node
    m_startNode = new Node(m_object);
    m_startNode->setG(0);
    m_startNode->setBlocks(m_blocks, m_width, m_height);

    Board::printBoard(m_startNode->boardGrid());

    // inset start node in the open list
    m_openList.append(m_startNode);

    qDebug() << " --> Start solving board";
    Node *currentNode;

    QStack<Move> solution;

    // A* Search algorithm
    // openList is empty (no path found)
    while (!m_openList.isEmpty()) {
        currentNode = m_openList.takeFirst();
        m_closedList.append(currentNode);

        // check if Block can be moved to exit
        if (currentNode->h() == 0) {
            if (currentNode->blocks()->get(0)->x() + currentNode->blocks()->get(0)->width() == m_width) {
                solution.push_front(currentNode->move());
                while (currentNode->parentNode() != 0) {
                    currentNode = currentNode->parentNode();
                    if (currentNode->boardGrid() != m_startNode->boardGrid()) {
                        solution.push_front(currentNode->move());
                    }
                }
                cleanUp();
                return solution;
            }
        }
        expand(currentNode);
    }
    cleanUp();
    return solution;
}

void BoardSolver::expand(Node *currentNode)
{
    // check possible moves

    QList<Node *> movements;

    // check each block for possible movements
    foreach (Block *block, currentNode->blocks()->blocks()) {
        // check possible x movements
        if (block->orientation() == Block::Horizontal) {
            // check right movements
            int rightDelta = 0;
            for (int i = block->x() + block->width(); i < m_width; i++) {
                if (currentNode->boardGrid()[i][block->y()].blockId() == -1) {
                    rightDelta += 1;
                } else {
                    break;
                }
            }
            //qDebug() << "block" << block->id() << "-> delta x+:" << rightDelta;
            // create right movements for each + delta
            for (int i = 1; i <= abs(rightDelta); ++i) {
                Node *node = new Node(m_object);
                node->setG(currentNode->g() + 1);
                Blocks *blocks = new Blocks(currentNode->blocks(), m_object);
                Block *movedBlock = blocks->get(block->id());
                movedBlock->setX(movedBlock->x() + i);
                node->setMove(Move(block->id(), i));
                node->setBlocks(blocks, m_width, m_height);
                movements.append(node);
            }

            // check left movements
            int leftDelta = 0;
            for (int i = block->x() - 1; i >= 0; i--) {
                if (currentNode->boardGrid()[i][block->y()].blockId() == -1) {
                    leftDelta -= 1;
                } else {
                    break;
                }
            }
            //qDebug() << "block" << block->id() << "-> delta x-:" << leftDelta;

            // create left movements for each - delta
            for (int i = 1; i <= abs(leftDelta); ++i) {
                Node *node = new Node(m_object);
                node->setG(currentNode->g() + 1);
                Blocks *blocks = new Blocks(currentNode->blocks(), m_object);
                Block *movedBlock = blocks->get(block->id());
                movedBlock->setX(movedBlock->x() - i);
                node->setMove(Move(block->id(), i *(-1)));
                node->setBlocks(blocks, m_width, m_height);
                movements.append(node);
            }
        }

        // check possible y movements
        if (block->orientation() == Block::Vertical) {
            // check down movements
            int lowerDelta = 0;
            for (int i = block->y() + block->height(); i < m_height; i++) {
                if (currentNode->boardGrid()[block->x()][i].blockId() == -1) {
                    lowerDelta += 1;
                } else {
                    break;
                }
            }
            //qDebug() << "block" << block->id() << "-> delta y+:" << lowerDelta;

            // create down movements for each + delta
            for (int i = 1; i <= abs(lowerDelta); ++i) {
                Node *node = new Node(m_object);
                node->setG(currentNode->g() + 1);
                Blocks *blocks = new Blocks(currentNode->blocks(), m_object);
                Block *movedBlock = blocks->get(block->id());
                movedBlock->setY(movedBlock->y() + i);
                node->setMove(Move(block->id(), i));
                node->setBlocks(blocks, m_width, m_height);
                movements.append(node);
            }

            // check up movements
            int upperDelta = 0;
            for (int i = block->y() - 1; i >= 0; i--) {
                if (currentNode->boardGrid()[block->x()][i].blockId() == -1) {
                    upperDelta -= 1;
                } else {
                    break;
                }
            }
            //qDebug() << "block" << block->id() << "-> delta y-:" << upperDelta;

            // create up movements for each - delta
            for (int i = 1; i <= abs(upperDelta); ++i) {
                Node *node = new Node(m_object);
                node->setG(currentNode->g() + 1);
                Blocks *blocks = new Blocks(currentNode->blocks(), m_object);
                Block *movedBlock = blocks->get(block->id());
                movedBlock->setY(movedBlock->y() - i);
                node->setMove(Move(block->id(), i *(-1)));
                node->setBlocks(blocks, m_width, m_height);
                movements.append(node);
            }
        }
    }

    foreach (Node *node, movements) {
        // check if this node is already in the closed list (already checked)
        if (inClosedList(node)) {
            delete node;
        } else {
            // check if this node is already in the openList
            if (inOpenList(node)) {
                // check if this node is a better parent as the current parent of this neighbor
                double withCurrentNodeG = currentNode->g() + 1;
                if (withCurrentNodeG <= node->g()) {
                    node->setG(withCurrentNodeG);
                    node->setParentNode(currentNode);
                }
            } else {
                node->setParentNode(currentNode);
                m_openList.append(node);
            }
        }
    }
    qSort(m_openList.begin(), m_openList.end(), openListLessThan);
}

bool BoardSolver::inOpenList(Node *node)
{
    foreach (Node *n, m_openList) {
        if (n->boardGrid() == node->boardGrid()) {
            return true;
        }
    }
    return false;
}

bool BoardSolver::inClosedList(Node *node)
{
    foreach (Node *n, m_closedList) {
        if (n->boardGrid() == node->boardGrid()) {
            return true;
        }
    }
    return false;
}

void BoardSolver::cleanUp()
{
    qDeleteAll(m_openList);
    m_openList.clear();

    qDeleteAll(m_closedList);
    m_closedList.clear();

    delete m_object;
}

bool openListLessThan(Node *a, Node *b)
{
    return a->f() < b->f();
}
