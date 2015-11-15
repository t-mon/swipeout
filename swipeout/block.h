#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>

class Block : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int startX READ startX CONSTANT)
    Q_PROPERTY(int startY READ startY CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)


public:
    explicit Block(const int &id,  const int &x, const int &y, const int &height, const int &width, QObject *parent = 0);

    int id() const;
    void setId(const int &id);

    int startX() const;
    int x()const;
    void setX(const int &x);

    int startY() const;
    int y()const;
    void setY(const int &y);

    int width()const;
    void setWidth(const int &width);

    int height()const;
    void setHeight(const int &height);

    void resetPosition();

private:
    int m_id;
    int m_startX;
    int m_x;
    int m_startY;
    int m_y;
    int m_height;
    int m_width;

signals:
    void xChanged();
    void yChanged();
    void positionResetted();

};

#endif // BLOCK_H
