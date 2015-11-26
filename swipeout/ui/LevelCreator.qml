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
    title: "Level " + level.id

    property var creator: gameEngine.levelCreator
    property var level: creator.board.level
    property real borderWidth: units.gu(1.5)
    property real cellSize: Math.min(width / creator.width , height / creator.height)

    head.actions: [
        Action {
            id: settingsAction
            iconName: "info"
            text: i18n.tr("Info")
            onTriggered: app.debug = !app.debug
        }
    ]

    Column {
        anchors.centerIn: parent
        spacing: units.gu(1)
        Row {
            id: toolRow
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)

            LevelCreatorDeleteTool {
                id: deleteTool
                width: parent.width / 5
                height: width
            }
            LevelCreatorTwoHorizontalTool {
                id: twoHorizontalTool
                width: parent.width / 5
                height: width
            }

            LevelCreatorThreeHorizontalTool {
                id: threeHorizontalTool
                width: parent.width / 5
                height: width
            }

            LevelCreatorTwoVerticalTool {
                id: twoVerticalTool
                width: parent.width / 5
                height: width
            }

            LevelCreatorThreeVerticalTool {
                id: threeVerticalTool
                width: parent.width / 5
                height: width
            }

        }

        UbuntuShape {
            id: boardBackground
            width: creator.width * cellSize
            height: creator.height * cellSize

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
                    height: Math.min(parent.width / creator.width , parent.height / creator.height)
                    anchors.right: parent.right
                    anchors.rightMargin: -borderWidth
                    anchors.top: parent.top
                    anchors.topMargin: 2 * height
                }

                Repeater {
                    id: blockRepeater
                    anchors.fill: parent
                    model: level.blocks
                    delegate: BlockItem {
                        cellSize: Math.min(boardArea.width / creator.width , boardArea.height / creator.height)
                        board: creator.board
                        block: level.blocks.get(model.blockId)
                    }
                }
            }

            UbuntuShape {
                id: addingArea
                anchors.fill: parent
                anchors.margins: borderWidth
                backgroundColor: "transparent"

                Grid {
                    columns: creator.width
                    visible: gameEngine.levelCreator.addMode
                    Repeater {
                        id: fieldRepeater
                        model: level.width * level.height
                        delegate: Rectangle {
                            height: Math.min(addingArea.width / creator.width , addingArea.height / creator.height)
                            width: height
                            color: "transparent"
                            border.color: "#aaaaaaaa"

                            MouseArea {
                                anchors.fill: parent
                                onClicked:  {
                                    if (!creator.board.showSolutionRunning)
                                        creator.createBlock(index)

                                }
                            }
                        }
                    }
                }
            }

        }

        Item {
            id: buttons
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(1)
            height: parent.width / 5

            Row {
                id: buttonRow
                anchors.fill: parent

                Item {
                    width: parent.width / 5
                    height: width

                    UbuntuShape {
                        anchors.fill: parent
                        anchors.margins: units.gu(0.5)
                        backgroundColor: deleteMouseArea.pressed ? "#44444444" : "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "delete"
                        }

                        MouseArea {
                            id: deleteMouseArea
                            anchors.fill: parent
                            onClicked: {
                                if (!creator.board.showSolutionRunning)
                                    creator.clearBoard()

                            }
                        }
                    }
                }

                Item {
                    width: parent.width / 5
                    height: width

                    UbuntuShape {
                        anchors.fill: parent
                        anchors.margins: units.gu(0.5)
                        backgroundColor: createRandomLevelMouseArea.pressed ? "#44444444" : "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "view-refresh"
                        }

                        MouseArea {
                            id: createRandomLevelMouseArea
                            anchors.fill: parent
                            onClicked: {
                                if (!creator.board.showSolutionRunning)
                                    creator.createRandomLevel()

                            }
                        }
                    }
                }

                Item {
                    width: parent.width / 5
                    height: width

                    UbuntuShape {
                        anchors.fill: parent
                        anchors.margins: units.gu(0.5)
                        backgroundColor: solveMouseArea.pressed ? "#44444444" : "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "torch-on"
                        }

                        MouseArea {
                            id: solveMouseArea
                            anchors.fill: parent
                            onClicked: {
                                if (!creator.board.showSolutionRunning) {
                                    gameEngine.solveBoard()
                                    PopupUtils.open(Qt.resolvedUrl("SolveDialog.qml"))
                                }
                            }
                        }
                    }
                }

                Item {
                    width: parent.width / 5
                    height: width

                    visible: creator.board.solutionAvailable

                    UbuntuShape {
                        anchors.fill: parent
                        anchors.margins: units.gu(0.5)
                        backgroundColor: saveMouseArea.pressed ? "#44444444" : "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "save"
                        }

                        MouseArea {
                            id: saveMouseArea
                            anchors.fill: parent
                            onClicked:  {
                                if (!gameEngine.solver.board.showSolutionRunning)
                                    PopupUtils.open(Qt.resolvedUrl("SaveDialog.qml"))

                            }
                        }
                    }
                }

                Item {
                    width: parent.width / 5
                    height: width

                    visible: creator.board.solutionAvailable

                    UbuntuShape {
                        anchors.fill: parent
                        anchors.margins: units.gu(0.5)
                        backgroundColor: showSolutionMouseArea.pressed ? "#44444444" : "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "torch-off"
                        }

                        MouseArea {
                            id: showSolutionMouseArea
                            anchors.fill: parent
                            onClicked: {
                                if (!creator.board.showSolutionRunning)
                                    gameEngine.levelCreator.board.showSolution()

                            }
                        }
                    }
                }
            }
        }
    }
}
