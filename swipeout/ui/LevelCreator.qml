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
import QtQuick.Layouts 1.1
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
            id: helpAction
            iconName: "help"
            text: i18n.tr("Help")
            onTriggered: pageStack.push(Qt.resolvedUrl("HelpCreatorPage.qml"))
        },
        Action {
            id: settingsAction
            iconName: "settings"
            text: i18n.tr("Settings")
            onTriggered: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
        }
    ]

    GridLayout {
        id: mainGrid
        anchors.fill: parent
        columns: app.landscape ? 3 : 1

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: units.gu(10)
            Layout.minimumWidth: units.gu(10)

            GridLayout {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                columns: app.landscape ? 1 : 5

                LevelCreatorDeleteTool {
                    id: deleteTool
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }
                LevelCreatorTwoHorizontalTool {
                    id: twoHorizontalTool
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }

                LevelCreatorThreeHorizontalTool {
                    id: threeHorizontalTool
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }

                LevelCreatorTwoVerticalTool {
                    id: twoVerticalTool
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }

                LevelCreatorThreeVerticalTool {
                    id: threeVerticalTool
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
                }
            }
        }

        Item {
            Layout.preferredHeight: Math.min(parent.height, parent.width)
            Layout.preferredWidth: Math.min(parent.height, parent.width)

            UbuntuShape {
                id: boardBackground
                anchors.fill: parent

                backgroundColor: boardBoarderColor

                UbuntuShape {
                    id: boardArea
                    anchors.fill: parent
                    anchors.margins: borderWidth
                    backgroundColor: boardColor

                    Rectangle {
                        id: exitShape
                        color: boardArea.backgroundColor
                        width: 2 * borderWidth
                        height: Math.min(parent.width / creator.width , parent.height / creator.height)
                        anchors.right: parent.right
                        anchors.rightMargin: -borderWidth
                        anchors.top: parent.top
                        anchors.topMargin: 2 * height

                        Image {
                            anchors.top: parent.top
                            anchors.bottom: parent.bottom
                            anchors.right: parent.right
                            width: borderWidth
                            source: "qrc:///images/exit.svg"
                        }
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

                    Rectangle {
                        visible: gameEngine.levelCreator.addMode
                        anchors.fill: parent
                        color: "transparent"
                        border.color: "#aaaaaaaa"
                        border.width: units.gu(0.2)
                    }

                    Grid {
                        columns: creator.width
                        visible: gameEngine.levelCreator.addMode

                        Repeater {
                            id: fieldRepeater
                            model: level.width * level.height
                            delegate: Rectangle {
                                anchors.margins: border.width / 2
                                height: Math.min(addingArea.width / creator.width , addingArea.height / creator.height)
                                width: height
                                color: "transparent"
                                border.color: "#aaaaaaaa"
                                border.width: units.gu(0.1)

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
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: units.gu(10)
            Layout.minimumWidth: units.gu(10)

            GridLayout {
                anchors.fill: parent
                anchors.margins: units.gu(2)
                columns: app.landscape ? 1 : 5

                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: deleteMouseArea.pressed ? "#44ff4444" : "#88ff8888"

                    Icon {
                        anchors.centerIn: parent
                        width: Math.min(parent.height, parent.width) - units.gu(1)
                        height: Math.min(parent.height, parent.width) - units.gu(1)
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



                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: createRandomLevelMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.centerIn: parent
                        width: Math.min(parent.height, parent.width) - units.gu(1)
                        height: Math.min(parent.height, parent.width) - units.gu(1)
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



                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: solveMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.centerIn: parent
                        width: Math.min(parent.height, parent.width) - units.gu(1)
                        height: Math.min(parent.height, parent.width) - units.gu(1)
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




                UbuntuShape {
                    visible: creator.board.solutionAvailable

                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: saveMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.centerIn: parent
                        width: Math.min(parent.height, parent.width) - units.gu(1)
                        height: Math.min(parent.height, parent.width) - units.gu(1)
                        name: "save"
                    }

                    MouseArea {
                        id: saveMouseArea
                        anchors.fill: parent
                        onClicked:  {
                            if (!creator.board.showSolutionRunning) {
                                PopupUtils.open(Qt.resolvedUrl("SaveDialog.qml"))
                            }
                        }
                    }
                }



                UbuntuShape {
                    visible: creator.board.solutionAvailable

                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.preferredHeight: app.landscape ? parent.height / 5 : parent.width / 5
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: showSolutionMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.centerIn: parent
                        width: Math.min(parent.height, parent.width) - units.gu(1)
                        height: Math.min(parent.height, parent.width) - units.gu(1)
                        name: "torch-off"
                    }

                    MouseArea {
                        id: showSolutionMouseArea
                        anchors.fill: parent
                        onClicked: {
                            if (!creator.board.showSolutionRunning)
                                creator.board.showSolution()

                        }
                    }
                }
            }
        }
    }
}

