#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>

#include "blocks.h"

class Level : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Blocks *blocks READ blocks CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)

public:
    explicit Level(QObject *parent = 0);

    Blocks *blocks();
    void addBlock(Block *block);

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(const int &id);

    int width() const;
    void setWidth(const int &width);

    int height() const;
    void setHeight(const int &height);

private:
    Blocks *m_blocks;
    QString m_name;
    int m_id;
    int m_width;
    int m_height;

};

#endif // LEVEL_H
