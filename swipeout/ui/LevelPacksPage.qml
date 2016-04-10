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
import Ubuntu.Components.ListItems 1.3

import Swipeout 1.0

Page {
    id: root

    header: PageHeader {
        id: pageHeader
        title: i18n.tr("Level Packs")
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
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("HelpMenuPage.qml"))
            },
            Action {
                id: settingsAction
                iconName: "settings"
                text: i18n.tr("Settings")
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("SettingsPage.qml"))
            }
        ]

        flickable: levelGrid
    }

    ListView {
        id: levelGrid
        anchors.fill: parent
        anchors.topMargin: units.gu(2)
        spacing: units.gu(2)
        model: gameEngine.levelPacks

        delegate: Item {
            anchors.left: parent.left
            anchors.leftMargin: units.gu(2)
            anchors.right: parent.right
            anchors.rightMargin: units.gu(2)
            height: units.gu(8)

            property var levelPack: gameEngine.levelPacks.get(model.name)

            RowLayout {
                anchors.fill: parent

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    UbuntuShape {
                        id: shape
                        anchors.fill: parent
                        backgroundColor: levelPack.completedPerfectCount == levelPack.levelCount ?
                                             completedPerfectColor : levelPack.completedCount == levelPack.levelCount && levelPack.completedPerfectCount != levelPack.levelCount ?
                                                 completedColor : uncompletedColor

                        Label {
                            anchors.left: parent.left
                            anchors.leftMargin: units.gu(2)
                            anchors.verticalCenter: parent.verticalCenter
                            text: model.name
                            font.bold: true
                            color: shape.backgroundColor == uncompletedColor ? "white" : "black"
                        }
                    }
                }

                Item {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: units.gu(10)

                    Column {
                        anchors.fill: parent

                        UbuntuShape {
                            width: parent.width
                            height: parent.height / 2
                            backgroundColor: completedColor

                            Label {
                                color: "black"
                                anchors.centerIn: parent
                                text: levelPack.completedCount + " / " + model.levelCount
                            }
                        }

                        UbuntuShape {
                            width: parent.width
                            height: parent.height / 2
                            backgroundColor: completedPerfectColor

                            Label {
                                color: "black"
                                anchors.centerIn: parent
                                text: levelPack.completedPerfectCount + " / " + model.levelCount
                            }
                        }
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    gameEngine.loadLevelPack(model.name)
                    pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("LevelSelectorPage.qml"))
                }
            }
        }
    }
}
