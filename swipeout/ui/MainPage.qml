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
import Lomiri.Components 1.3
import Swipeout 1.0

Page {
    id: root
    header: PageHeader {
        id: pageHeader
        title: "Swipeout"
        trailingActionBar.actions: [
            Action {
                id: infoAction
                iconName: "info"
                text: i18n.tr("About")
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("AboutPage.qml"))
            },
            Action {
                id: settingsAction
                iconName: "settings"
                text: i18n.tr("Settings")
                onTriggered: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("SettingsPage.qml"))
            }
        ]
    }

    Image {
        anchors.fill: parent
        opacity: 0.1
        source: app.landscape ? "qrc:///images/menu-background-landscape.svg" :  "qrc:///images/menu-background-portrait.svg"
    }

    Column {
        spacing: units.gu(3)
        anchors.centerIn: parent

        Item {
            width: units.gu(20)
            height: units.gu(7)

            LomiriShape {
                anchors.fill: parent
                anchors.margins: units.gu(0.3)
                backgroundColor: "#8d8d8d"
            }

            LomiriShape {
                anchors.fill: parent
                backgroundColor: "#8d8d8d"
                opacity: 0.6
            }

            Button {
                // TRANSLATORS: Play button in the main view.
                text: i18n.tr("Play")
                font.bold:true
                anchors.fill: parent
                color: "transparent"
                onClicked: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("LevelPacksPage.qml"))
            }
        }

        Item {
            width: units.gu(20)
            height: units.gu(7)

            LomiriShape {
                anchors.fill: parent
                anchors.margins: units.gu(0.3)
                backgroundColor: "#ff333333"
            }

            LomiriShape {
                anchors.fill: parent
                backgroundColor: "#ff333333"
                opacity: 0.6
            }

            Button {
                // TRANSLATORS: "Load level" button in the main view.
                text: i18n.tr("Load level")
                font.bold:true
                anchors.fill: parent
                color: "transparent"
                onClicked: {
                    gameEngine.loadCreatedLevels()
                    pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("LoadLevelPage.qml"))
                }
            }
        }

        Item {
            width: units.gu(20)
            height: units.gu(7)

            LomiriShape {
                anchors.fill: parent
                anchors.margins: units.gu(0.3)
                backgroundColor: "#ff333333"
            }

            LomiriShape {
                anchors.fill: parent
                backgroundColor: "#ff333333"
                opacity: 0.6
            }

            Button {
                // TRANSLATORS: "Level Creator" button in the main view.
                text: i18n.tr("Level Creator")
                font.bold:true
                anchors.fill: parent
                color: "transparent"
                onClicked: pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("LevelCreator.qml"))
            }
        }
    }
}
