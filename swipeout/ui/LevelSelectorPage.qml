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

import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr("Levels")

    GridView {
        id: levelGrid
        anchors.fill: parent
        anchors.margins: units.gu(1)
        cellWidth: units.gu(10)
        cellHeight: units.gu(10)
        model: gameEngine.levels

        delegate: LevelSelectorItem {
            width: levelGrid.cellWidth
            height: levelGrid.cellHeight
            levelId: model.levelId
            onSelected: {
                var level = gameEngine.levels.get(levelId)
                pageStack.push(Qt.resolvedUrl("BoardPage.qml"), { level: level } )
                gameEngine.loadLevel(model.levelId)
            }
        }
    }
}
