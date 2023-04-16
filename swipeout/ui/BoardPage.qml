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
import Lomiri.Components 1.3
import Lomiri.Components.Popups 1.3
import Lomiri.Components.ListItems 1.3
import Swipeout 1.0

Page {
    id: root

    property var level: gameEngine.board.level
    property real borderWidth: units.gu(1.5)
    property real cellSize: Math.min(root.width / level.width , root.height / level.height)

    header: PageHeader {
        id: pageHeader
        title: i18n.tr(level.name)
        trailingActionBar.actions: [
            Action {
                id: infoAction
                iconName: "info"
                text: i18n.tr("About")
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("AboutPage.qml"))
            },
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
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("SettingsPage.qml"))
            }
        ]
    }

    Connections {
        target: gameEngine.board
        onLevelChanged: {
            console.log("Level changed")
            blockRepeater.model = null
            blockRepeater.model = level.blocks
        }

    }

    GridLayout {
        id: mainGrid
        anchors.fill: parent
        anchors.topMargin: pageHeader.height + units.gu(2)
        columns: app.landscape ? 3 : 1
        columnSpacing: 0
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: units.gu(8)
            Layout.minimumWidth: units.gu(8)


            GridLayout {
                anchors.fill: parent
                anchors.margins: units.gu(1)
                columns: app.landscape ? 1 : 2

                LomiriShape {
                    id: movesShape
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: units.gu(12)
                    Layout.preferredHeight: app.landscape ? height : units.gu(7)
                    Layout.alignment: !app.landscape ? Qt.AlignBottom : Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: "#44444444"

                    Column {
                        anchors.centerIn: parent
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            // TRANSLATORS: Moves rectangle in the play view.
                            text: i18n.tr("MOVES")
                        }
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                            font.pixelSize: units.gu(2)
                            text: gameEngine.board.moveCount
                        }
                    }
                }

                LomiriShape {
                    id: highscoreShape
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.preferredWidth: units.gu(12)
                    Layout.preferredHeight: app.landscape ? height : units.gu(7)
                    Layout.alignment: !app.landscape ? Qt.AlignBottom : Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: "#44444444"

                    Column {
                        anchors.centerIn: parent
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            // TRANSLATORS: Highscore rectangle in the play view.
                            text: i18n.tr("HIGHSCORE")
                        }
                        Label {
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.bold: true
                            font.pixelSize: units.gu(2)
                            text: (level.record != 0 ? level.record : "-") + " / " + level.solutionCount
                        }
                    }
                }
            }
        }

        Item {
            Layout.preferredHeight: Math.min(parent.height, parent.width)
            Layout.preferredWidth: Math.min(parent.height, parent.width)

            LomiriShape {
                id: boardBackground
                anchors.fill: parent
                backgroundColor: boardBoarderColor

                LomiriShape {
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

                    // Fix the block positions if the board size changed
                    onWidthChanged: {
                        blockRepeater.model = null
                        blockRepeater.model = level.blocks
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: units.gu(8)
            Layout.minimumWidth: units.gu(8)

            GridLayout {
                anchors.fill: parent
                anchors.margins: units.gu(1)
                columns: app.landscape ? 1 : 3

                LomiriShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.minimumWidth: units.gu(8)
                    Layout.preferredHeight: app.landscape ? parent.height / 3 : units.gu(7)
                    Layout.alignment: !app.landscape ? Qt.AlignTop | Qt.AlignHCenter : Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: undoMouseArea.pressed ? "#88888888": "#44444444"

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

                LomiriShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.minimumWidth: units.gu(8)
                    Layout.preferredHeight: app.landscape ? parent.height / 3 : units.gu(7)
                    Layout.alignment: !app.landscape ? Qt.AlignTop | Qt.AlignHCenter : Qt.AlignVCenter | Qt.AlignHCenter

                    backgroundColor: restartMouseArea.pressed ? "#88888888": "#44444444"

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

                LomiriShape {
                    Layout.fillHeight: app.landscape
                    Layout.fillWidth: !app.landscape
                    Layout.minimumWidth: units.gu(8)
                    Layout.preferredHeight: app.landscape ? parent.height / 3 : units.gu(7)
                    Layout.alignment: !app.landscape ? Qt.AlignTop | Qt.AlignHCenter : Qt.AlignVCenter | Qt.AlignHCenter

                    visible: app.debug
                    backgroundColor: showSolutionMouseArea.pressed ? "#88888888": "#44444444"

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
            title: level.name
            // TRANSLATORS: Level completed view.
            text: i18n.tr("Level completed!")

            ThinDivider { }

            Label {
                anchors.left: parent.left
                anchors.right: parent.right
                height: units.gu(5)
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                font.pixelSize: units.gu(3)
                text: gameEngine.board.moveCount + " / " + level.solutionCount
            }

            Label {
                anchors.left: parent.left
                anchors.right: parent.right
                height: units.gu(5)
                visible: gameEngine.board.moveCount <= level.solutionCount
                horizontalAlignment: Text.AlignHCenter
                font.bold: true
                // TRANSLATORS: Level completed view.
                text: i18n.tr("You have found the perfect solution!")
            }

            ThinDivider { }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.width / 4

                Button {
                    visible: gameEngine.hasPreviousLevel
                    anchors.left: parent.left
                    width: parent.width / 4
                    height: width
                    onClicked: {
                        gameEngine.loadPreviousLevel(level)
                        PopupUtils.close(completedDialog)
                    }

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "back"
                    }
                }

                Button {
                    anchors.centerIn: parent
                    width: parent.width / 4
                    height: width
                    onClicked: {
                        PopupUtils.close(completedDialog)
                        gameEngine.board.restartLevel()
                    }

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "reload"
                    }
                }

                Button {
                    visible: gameEngine.hasNextLevel
                    anchors.right: parent.right
                    width: parent.width / 4
                    height: width
                    onClicked: {
                        gameEngine.loadNextLevel(level)
                        PopupUtils.close(completedDialog)
                    }

                    Icon {
                        anchors.fill: parent
                        anchors.margins: units.gu(2)
                        name: "next"
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
