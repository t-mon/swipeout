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
    title: i18n.tr("Level creator")

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
            id: addDeviceAction
            iconName: "reload"
            text: i18n.tr("Create level")
            onTriggered: creator.createRandomLevel()
        }
    ]

    Column {
        anchors.centerIn: parent
        spacing: units.gu(2)

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
        }

        Row {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(1)
            spacing: units.gu(1)

            Button {
                text: i18n.tr("Save");
                onClicked: creator.saveLevel()
            }

            Button {
                visible: app.debug
                text: i18n.tr("Solve")
                onClicked: gameEngine.solveCreatorBoard()
                ActivityIndicator {
                    id: solverIndicator
                    running: gameEngine.solverRunning
                }
            }

            Button {
                visible: app.debug && creator.board.solutionAvailable
                text: i18n.tr("Show solution");
                onClicked: creator.board.showSolution()
            }
        }
    }
}
