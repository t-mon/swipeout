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
    title: i18n.tr(level.name)

    property var level: gameEngine.board.level
    property real borderWidth: units.gu(1.5)
    property real cellSize: Math.min(root.width / level.width , root.height / level.height)

    head.actions: [
        Action {
            id: helpAction
            iconName: "help"
            text: i18n.tr("Help")
            onTriggered: app.debug = !app.debug
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
        anchors.centerIn: parent
        Layout.fillHeight: app.landscape
        Layout.fillWidth: !app.landscape
        columns: app.landscape ? 3 : 1

        // ###########################################
        Item {
            width: app.landscape ? root.height * 2 / 5 : root.width
            height: app.landscape ? root.height : root.width * 2 / 5
            Layout.maximumHeight: app.landscape ? height : units.gu(10)
            Layout.maximumWidth: app.landscape ? units.gu(10) : width
            Layout.fillHeight: app.landscape
            Layout.fillWidth: !app.landscape

            Rectangle {
                anchors.fill: parent
                color: "red"
                opacity: 0.5

            }

            GridLayout {
                anchors.fill: parent
                columns: app.landscape ? 1 : 2

                UbuntuShape {
                    id: movesShape
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

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
                    id: highscoreShape
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: "#88888888"

                    Column {
                        anchors.centerIn: parent
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            text: i18n.tr("HIGHSCORE")
                        }
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                            text: (level.record != 0 ? level.record : "-") + " / " + level.solutionCount
                        }
                    }
                }
            }
        }


        // ###########################################
        Item {
            anchors.centerIn: parent

            width: app.landscape ? root.height : root.width
            height: app.landscape ? root.height : root.width
            Layout.maximumWidth: width
            Layout.maximumHeight: height


            Rectangle {
                anchors.fill: parent
                color: "blue"
                opacity: 0.5
            }

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
                        height: Math.min(boardArea.width / level.width , boardArea.height / level.height)
                        anchors.right: parent.right
                        anchors.rightMargin: -borderWidth
                        anchors.top: parent.top
                        anchors.topMargin: level.blocks.get(0).y * height

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
                            cellSize: Math.min(boardArea.width / level.width , boardArea.height / level.height)
                            board: gameEngine.board
                            block: level.blocks.get(model.blockId)
                        }
                    }
                }
            }
        }

        // ###########################################
        Item {
            width: app.landscape ? root.height * 2 / 5 : root.width
            height: app.landscape ? root.height : root.width * 2 / 5
            Layout.maximumHeight: app.landscape ? height : units.gu(10)
            Layout.maximumWidth: app.landscape ? units.gu(10) : width
            Layout.fillHeight: app.landscape
            Layout.fillWidth: !app.landscape

            Rectangle {
                anchors.fill: parent
                color: "green"
                opacity: 0.5
            }

            GridLayout {
                anchors.fill: parent
                columns: app.landscape ? 1 : 3

                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: undoMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(1)
                        name: "undo"
                    }

                    MouseArea {
                        id: undoMouseArea
                        anchors.fill: parent
                        onClicked: {
                            if (!gameEngine.board.showSolutionRunning)
                                gameEngine.board.undoMove()
                        }
                    }
                }

                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: restartMouseArea.pressed ? "#44444444" : "#88888888"

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(1)
                        name: "reload"
                    }

                    MouseArea {
                        id: restartMouseArea
                        anchors.fill: parent
                        onClicked: {
                            if (!gameEngine.board.showSolutionRunning)
                                gameEngine.board.restartLevel()

                        }
                    }
                }

                UbuntuShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

                    visible: app.debug
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
                            if (!gameEngine.board.showSolutionRunning)
                                gameEngine.board.showSolution()

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

            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                height: units.gu(5)
                visible: gameEngine.board.moveCount == level.solutionCount
                text: i18n.tr("You found the perfect solution!")
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.width / 4

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
                        name: "view-grid-symbolic"
                    }

                    onClicked: {
                        PopupUtils.close(completedDialog)
                        pageStack.pop()
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
            gameEngine.levelPack.calculateStatistic()
            PopupUtils.open(completedComponent)
        }
    }
}
