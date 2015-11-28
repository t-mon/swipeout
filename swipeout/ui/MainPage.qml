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
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr("Swipeout")

    head.actions: [
        Action {
            id: infoAction
            iconName: "info"
            text: i18n.tr("About")
            onTriggered: pageStack.push(Qt.resolvedUrl("AboutPage.qml"))
        },
        Action {
            id: settingsAction
            iconName: "settings"
            text: i18n.tr("Settings")
            onTriggered: pageStack.push(Qt.resolvedUrl("SettingsPage.qml"))
        }
    ]

    Image {
        anchors.fill: parent
        opacity: 0.1
        source: app.landscape ? "qrc:///images/menu-background-landscape.svg" :  "qrc:///images/menu-background-portrait.svg"
    }

    Column {
        spacing: units.gu(3)
        anchors.centerIn: parent

        Button {
            text: i18n.tr("Play")
            font.bold:true
            color: "#ff888888"
            width: units.gu(20)
            height: units.gu(7)
            onClicked: {
                push(Qt.resolvedUrl("LevelPacksPage.qml"))
            }
        }

        Button {
            text: i18n.tr("Load level")
            color: "#ff333333"
            width: units.gu(20)
            height: units.gu(7)
            onClicked: {
                gameEngine.loadCreatedLevels()
                push(Qt.resolvedUrl("LoadLevelPage.qml"))
            }
        }

        Button {
            text: i18n.tr("Create level")
            color: "#ff333333"
            width: units.gu(20)
            height: units.gu(7)
            onClicked: {
                push(Qt.resolvedUrl("LevelCreator.qml"))
            }
        }
    }
}
