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
    property var board: null


    Connections {
        target: block
        onPositionResetted: {
            blockShape.x = block.startX * cellSize
            blockShape.y = block.startY * cellSize
        }
        onXChanged: {
            blockShape.x = block.x * cellSize
        }
        onYChanged: {
            blockShape.y = block.y * cellSize
        }
    }

    UbuntuShape {
        id: blockShape
        width: block.width * cellSize
        height: block.height * cellSize
        backgroundColor: block.color

        x: block.x * cellSize
        y: block.y * cellSize

        Behavior on x {
            id: xBehavior
            NumberAnimation {
                duration: 100
                easing.type: Easing.OutQuad
            }
        }

        Behavior on y {
            id: yBehavior
            NumberAnimation {
                duration: 100
                easing.type: Easing.OutQuad
            }
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

            onClicked: {
                if (gameEngine.levelCreator.deleteToolSelected) {
                    gameEngine.levelCreator.removeBlock(block.id)
                }
            }

            onPressed: {
                xBehavior.enabled = false
                yBehavior.enabled = false

                if (block.width > block.height) {
                    elementMouseArea.drag.minimumX = board.calculateLeftLimit(block.id) * root.cellSize
                    elementMouseArea.drag.maximumX = board.calculateRightLimit(block.id) * root.cellSize
                } else {
                    elementMouseArea.drag.minimumY = board.calculateUpperLimit(block.id) * root.cellSize
                    elementMouseArea.drag.maximumY = board.calculateLowerLimit(block.id) * root.cellSize
                }
            }

            onReleased: {
                if (block.width > block.height) {
                    xBehavior.enabled = true
                    var newX = Math.round(blockShape.x / cellSize)
                    board.moveBlock(block.id, newX - block.x)
                    blockShape.x = newX * cellSize
                } else {
                    yBehavior.enabled = true
                    var newY = Math.round(blockShape.y / cellSize)
                    board.moveBlock(block.id, newY - block.y)
                    blockShape.y = newY * cellSize
                }
            }
        }

        Label {
            visible: app.debug
            anchors.centerIn: parent
            text: blockId
        }

    }
}

