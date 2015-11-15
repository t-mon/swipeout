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
    property real cellSize
    property var block: null


    Connections {
        target: block
        onPositionResetted: {
            blockShape.x = block.startX * cellSize
            blockShape.y = block.startY * cellSize
        }
    }

    UbuntuShape {
        id: blockShape
        width: block.width * cellSize
        height: block.height * cellSize
        color: block.id == 0 ? UbuntuColors.red : "#888888"

        x: block.x * cellSize
        y: block.y * cellSize

        Behavior on x {
            id: xBehavior
            enabled: false
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        Behavior on y {
            id: yBehavior
            enabled: false
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        Text {
            anchors.centerIn: parent
            text: blockId
        }

        MouseArea {
            id: elementMouseArea
            anchors.fill: parent

            drag.target: parent
            drag.axis: width > height ? Drag.XAxis : Drag.YAxis
            drag.minimumX: 0
            drag.maximumX: board.width - width
            drag.minimumY: 0
            drag.maximumY: board.height - height

            onPressed: {
                console.log("calculate limits")
                xBehavior.enabled = false
                yBehavior.enabled = false

                if (block.width > block.height) {
                    elementMouseArea.drag.minimumX = gameEngine.board.calculateLeftLimit(block.id) * root.cellSize
                    elementMouseArea.drag.maximumX = gameEngine.board.calculateRightLimit(block.id) * root.cellSize
                } else {
                    elementMouseArea.drag.minimumY = gameEngine.board.calculateUpperLimit(block.id) * root.cellSize
                    elementMouseArea.drag.maximumY = gameEngine.board.calculateLowerLimit(block.id) * root.cellSize
                }
            }

            onReleased: {
                if (block.width > block.height) {
                    xBehavior.enabled = true
                    var newX = Math.round(blockShape.x / cellSize)
                    gameEngine.board.moveBlockX(block.id, newX)
                    blockShape.x = newX * cellSize
                } else {
                    yBehavior.enabled = true
                    var newY = Math.round(blockShape.y / cellSize)
                    gameEngine.board.moveBlockY(block.id, newY)
                    blockShape.y = newY * cellSize
                }
            }
        }
    }
}

