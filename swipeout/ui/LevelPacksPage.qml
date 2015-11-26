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
import Ubuntu.Components.ListItems 1.3

import Swipeout 1.0

Page {
    id: root
    title: i18n.tr("Level Packs")

    UbuntuListView {
        id: levelGrid
        anchors.fill: parent
        spacing: units.gu(2)
        model: gameEngine.levelPacks

        delegate: UbuntuShape {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(2)
            height: units.gu(8)

            backgroundColor: "#88888888"

            property var levelPack: gameEngine.levelPacks.get(model.name)

            Label {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                anchors.verticalCenter: parent.verticalCenter
                text: model.name
                font.bold: true
            }

            Item {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right

                width: parent.width / 3

                Column {
                    anchors.fill: parent

                    UbuntuShape {
                        width: parent.width
                        height: parent.height / 2
                        backgroundColor: completedColor

                        Label {
                            anchors.centerIn: parent
                            text: levelPack.completedCount + " / " + model.levelCount
                        }
                    }

                    UbuntuShape {
                        width: parent.width
                        height: parent.height / 2
                        backgroundColor: completedPerfectColor

                        Label {
                            anchors.centerIn: parent
                            text: levelPack.completedPerfectCount + " / " + model.levelCount
                        }
                    }
                }




            }


            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameEngine.loadLevelPack(model.name)
                    pageStack.push(Qt.resolvedUrl("LevelSelectorPage.qml"))
                }
            }
        }
    }
}
