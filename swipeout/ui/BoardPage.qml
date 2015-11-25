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

    head.actions: [
        Action {
            id: settingsAction
            iconName: "settings"
            text: i18n.tr("Debug")
            onTriggered: app.debug = !app.debug
        },
        Action {
            id: addDeviceAction
            iconName: "reload"
            text: i18n.tr("Restart level")
            onTriggered: gameEngine.board.restartLevel()
        }
    ]

    Column {
        anchors.centerIn: parent
        spacing: units.gu(1)

        Row {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)

            spacing: width / 3

            UbuntuShape {
                width: parent.width / 3
                height: width * 3 / 5
                backgroundColor: "#88888888"

                Column {
                    anchors.centerIn: parent
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: i18n.tr("MOVES")
                    }
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        text: gameEngine.board.moveCount
                    }
                }
            }

            UbuntuShape {
                width: parent.width / 3
                height: width * 3 / 5
                backgroundColor: "#88888888"

                Column {
                    anchors.centerIn: parent
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        text: i18n.tr("RECORD")
                    }
                    Label {
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.bold: true
                        text: (level.record != 0 ? level.record : "-") + " / " + level.solutionCount
                    }
                }
            }
        }


        UbuntuShape {
            id: boardBackground
            width: level.width * cellSize
            height: level.height * cellSize

            backgroundColor: "#88888888"

            UbuntuShape {
                id: boardArea
                anchors.fill: parent
                anchors.margins: borderWidth
                backgroundColor: UbuntuColors.darkGrey

                Rectangle {
                    id: exitShape
                    color: boardArea.backgroundColor
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
                        cellSize: Math.min(boardArea.width / level.width , boardArea.height / level.height)
                        board: gameEngine.board
                        block: level.blocks.get(model.blockId)
                    }
                }
            }
        }

        Row {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)

            Item {
                width: parent.width / 2
                height: width / 3

                UbuntuShape {
                    anchors.fill: parent
                    anchors.margins: units.gu(0.5)
                    backgroundColor: solveMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(1)
                        name: "undo"
                    }

                    MouseArea {
                        id: solveMouseArea
                        anchors.fill: parent
                        onClicked: {
                            if (!gameEngine.board.showSolutionRunning) {
                                gameEngine.board.undoMove()
                            }
                        }
                    }
                }
            }


            Item {
                width: parent.width / 2
                height: width / 3
                visible: app.debug

                UbuntuShape {
                    anchors.fill: parent
                    anchors.margins: units.gu(0.5)
                    backgroundColor: showSolutionMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(1)
                        name: "help"
                    }

                    MouseArea {
                        id: showSolutionMouseArea
                        anchors.fill: parent
                        onClicked: {
                            if (!gameEngine.board.showSolutionRunning) {
                                gameEngine.board.showSolution()
                            }
                        }
                    }
                }
            }
        }
    }

    Component {
        id: completedComponent
        Dialog {
            id: completedDialog
            title: i18n.tr("Level completed!")
            text: gameEngine.board.moveCount + " / " + level.solutionCount


            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.width / 4

                color: "transparent"

                Button {
                    anchors.left: parent.left
                    width: parent.width / 4
                    height: width
                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "back"
                    }

                    onClicked: {
                        PopupUtils.close(completedDialog)
                    }
                }

                Button {
                    anchors.centerIn: parent
                    width: parent.width / 4
                    height: width
                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "browser-tabs"
                    }

                    onClicked: {
                        PopupUtils.close(completedDialog)
                        pop()
                    }
                }

                Button {
                    anchors.right: parent.right
                    width: parent.width / 4
                    height: width

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "next"
                    }

                    onClicked: {
                        PopupUtils.close(completedDialog)
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
