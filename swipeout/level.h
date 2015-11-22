/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2015 Simon Stuerz <stuerz.simon@gmail.com>               *
 *                                                                         *
 *  This file is part of Swipeout.                                         *
 *                                                                         *
 *  Swipeout is free software: you can redistribute it and/or modify       *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, version 3 of the License.                *
 *                                                                         *
 *  Swipeout is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with Swipeout. If not, see <http://www.gnu.org/licenses/>.       *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QStack>

#include "blocks.h"
#include "move.h"

class Move;

class Level : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Blocks *blocks READ blocks CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int id READ id CONSTANT)
    Q_PROPERTY(int width READ width CONSTANT)
    Q_PROPERTY(int height READ height CONSTANT)
    Q_PROPERTY(bool solutionAvailable READ solutionAvailable NOTIFY solutionAvailableChanged)

public:
    explicit Level(QObject *parent = 0);

    QVariantList blockData() const;
    void setBlockData(const QVariantList &blockData);

    Blocks *blocks();
    void loadBlocks();
    void destroyBlocks();

    QString name() const;
    void setName(const QString &name);

    int id() const;
    void setId(const int &id);

    int width() const;
    void setWidth(const int &width);

    int height() const;
    void setHeight(const int &height);

    bool solutionAvailable() const;

    QStack<Move> solution() const;
    void clearSolution();
    void setSolution(const QStack<Move> &solution);

private:
    QVariantList m_blockData;
    Blocks *m_blocks;
    QStack<Move> m_solution;

    QString m_name;
    int m_id;
    int m_width;
    int m_height;

signals:
    void solutionAvailableChanged();

};

#endif // LEVEL_H
