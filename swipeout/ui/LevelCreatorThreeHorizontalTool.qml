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

Item {
    id: root

    property bool selected: gameEngine.levelCreator.threeHorizontalToolSelected

    UbuntuShape {
        anchors.fill: parent
        backgroundColor: !selected ? "#88888888" : "#55555555"

        Image {
            id: image
            anchors.centerIn: parent
            width: Math.min(parent.height, parent.width)
            height: Math.min(parent.height, parent.width)
            source: "qrc:///images/threeHorizontal.svg"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (!gameEngine.levelCreator.board.showSolutionRunning)
                    gameEngine.levelCreator.threeHorizontalToolSelected = !selected

            }
        }
    }
}
