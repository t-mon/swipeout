#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>

class Block : public QObject
{
    Q_OBJECT
public:
    explicit Block(QObject *parent = 0);

    int id() const;
    void setId(const int &id);

    int x()const;
    void setX(const int &x);

    int y()const;
    void setY(const int &y);

    int width()const;
    void setWidth(const int &width);

    int height()const;
    void setHeight(const int &height);

private:
    int m_id;
    int m_x;
    int m_y;
    int m_width;
    int m_height;

};

#endif // BLOCK_H
