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
import Ubuntu.Components.Popups 1.3
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr(level.name)

    property var level: gameEngine.board.level
    property real borderWidth: units.gu(1.5)
    property real cellSize: Math.min(width / level.width , height / level.height)

    head.actions: Action {
        id: addDeviceAction
        iconName: "reload"
        text: i18n.tr("Restart level")
        onTriggered: gameEngine.board.restartLevel()
    }

    Column {
        anchors.centerIn: parent
        spacing: units.gu(2)

        Row {
            anchors.horizontalCenter: boardBackground.horizontalCenter
            Label {
                text: i18n.tr("Moves: ")
            }
            Label {
                text: gameEngine.board.moveCount
                font.bold: true
            }
        }

        UbuntuShape {
            id: boardBackground
            width: level.width * cellSize
            height: level.height * cellSize

            backgroundColor: UbuntuColors.darkGrey

            UbuntuShape {
                id: board
                anchors.fill: parent
                anchors.margins: borderWidth
                backgroundColor: UbuntuColors.warmGrey

                Rectangle {
                    id: exitShape
                    color: board.backgroundColor
                    width: 2 * borderWidth
                    height: Math.min(parent.width / level.width , parent.height / level.height)
                    anchors.right: parent.right
                    anchors.rightMargin: -borderWidth
                    anchors.top: parent.top
                    anchors.topMargin: level.blocks.get(0).y * height
                }

                Repeater {
                    id: blockRepeater
                    anchors.fill: parent
                    model: level.blocks
                    delegate: BlockItem {
                        cellSize: Math.min(board.width / level.width , board.height / level.height)
                        block: level.blocks.get(model.blockId)
                    }
                }
            }
        }

        Row {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            spacing: units.gu(1)
            Button {
                text: i18n.tr("Undo")
                onClicked: gameEngine.board.undoMove()
            }

            Button {
                visible: app.debug
                text: i18n.tr("Solve")
                onClicked: gameEngine.solveBoard()
            }

            Button {
                visible: app.debug && gameEngine.board.solutionAvailable
                text: i18n.tr("Show solution");
                onClicked: gameEngine.board.showSolution()
            }
        }
    }

    Component {
        id: completedComponent
        Dialog {
            id: completedDialog
            title: i18n.tr("Level completed!")
            text: i18n.tr("You took " + gameEngine.board.moveCount + " moves.")

            Button {
                id: nextButton
                text: i18n.tr("Next level")
                onClicked: {
                    PopupUtils.close(completedDialog)
                    if (!gameEngine.startLevel(level.id + 1)) {
                        pageStack.pop()
                    }
                }
            }
        }
    }

    Connections {
        target: gameEngine.board
        onLevelCompleted: {
            PopupUtils.open(completedComponent)
        }
    }
}
