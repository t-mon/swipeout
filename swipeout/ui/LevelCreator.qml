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
            iconName: "settings"
            text: i18n.tr("Debug")
            onTriggered: app.debug = !app.debug
        },
        Action {
            id: clearAction
            iconName: "delete"
            text: i18n.tr("Clear board")
            onTriggered: creator.clearBoard()
        },
        Action {
            id: addDeviceAction
            iconName: "reload"
            text: i18n.tr("Create random level")
            onTriggered: creator.createRandomLevel()
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
            LevelCreatorTowHorizontalTool {
                id: twoHorizontalTool
                width: parent.width / 5
                height: width
            }

            LevelCreatorThreeHorizontalTool {
                id: threeHorizontalTool
                width: parent.width / 5
                height: width
            }

            LevelCreatorTowVerticalTool {
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
                                    creator.createBlock(index)
                                }
                            }
                        }
                    }
                }
            }

        }

        Row {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            spacing: units.gu(1)

            Button {
                text: i18n.tr("Save");
                onClicked: creator.saveLevel()
                color: "#88888888"
            }

            Button {
                text: i18n.tr("Solve")
                onClicked: PopupUtils.open(Qt.resolvedUrl("SolveDialog.qml"))
                color: "#88888888"
            }

            Button {
                visible: creator.board.level.solutionAvailable
                text: i18n.tr("Show solution");
                color: "#88888888"
                onClicked: creator.board.showSolution()
            }
        }
    }
}
