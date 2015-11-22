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

#ifndef LEVELCREATOR_H
#define LEVELCREATOR_H

#include <QObject>

#include "board.h"
#include "blocks.h"

class LevelCreator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Board *board READ board CONSTANT)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool deleteToolSelected READ deleteToolSelected WRITE setDeleteToolSelected NOTIFY deleteToolSelectedChanged)
    Q_PROPERTY(bool twoHorizontalToolSelected READ twoHorizontalToolSelected WRITE setTwoHorizontalToolSelected NOTIFY twoHorizontalToolSelectedChanged)
    Q_PROPERTY(bool twoVerticalToolSelected READ twoVerticalToolSelected WRITE setTwoVerticalToolSelected NOTIFY twoVerticalToolSelectedChanged)
    Q_PROPERTY(bool threeHorizontalToolSelected READ threeHorizontalToolSelected WRITE setThreeHorizontalToolSelected NOTIFY threeHorizontalToolSelectedChanged)
    Q_PROPERTY(bool threeVerticalToolSelected READ threeVerticalToolSelected WRITE setThreeVerticalToolSelected NOTIFY threeVerticalToolSelectedChanged)


    Q_PROPERTY(bool addMode READ addMode WRITE setAddMode NOTIFY addModeChanged)
public:
    explicit LevelCreator(QObject *parent = 0);

    int width() const;
    void setWidth(const int &width);

    int height() const;
    void setHeight(const int &height);

    Q_INVOKABLE void createRandomLevel();
    Q_INVOKABLE void saveLevel();

    Q_INVOKABLE void createBlock(const int &index);
    Q_INVOKABLE void removeBlock(const int &id);

    Q_INVOKABLE void clearBoard();

    Q_INVOKABLE void clearToolSelections();

    bool deleteToolSelected() const;
    void setDeleteToolSelected(const bool &selected);

    bool twoHorizontalToolSelected() const;
    void setTwoHorizontalToolSelected(const bool &selected);

    bool twoVerticalToolSelected() const;
    void setTwoVerticalToolSelected(const bool &selected);

    bool threeHorizontalToolSelected() const;
    void setThreeHorizontalToolSelected(const bool &selected);

    bool threeVerticalToolSelected() const;
    void setThreeVerticalToolSelected(const bool &selected);


    bool addMode() const;
    void setAddMode(const bool &addMode);

    Board *board();

private:
    int m_width;
    int m_height;

    Board *m_board;
    Level *m_level;
    QVector<QVector<BoardCell> > m_boardGrid;

    bool m_deleteToolSelected;
    bool m_twoHorizontalToolSelected;
    bool m_twoVerticalToolSelected;
    bool m_threeHorizontalToolSelected;
    bool m_threeVerticalToolSelected;

    bool m_addMode;

    void initLevel();
    void updateGrid();

    QPoint getCoordinates(const int &index);
    QList<QPoint> possiblePositions(Block *block);

signals:
    void widthChanged();
    void heightChanged();
    void blocksChanged();

    void deleteToolSelectedChanged();
    void twoVerticalToolSelectedChanged();
    void twoHorizontalToolSelectedChanged();
    void threeVerticalToolSelectedChanged();
    void threeHorizontalToolSelectedChanged();

    void addModeChanged();
};

#endif // LEVELCREATOR_H
