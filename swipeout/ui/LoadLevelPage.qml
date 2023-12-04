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
        title: i18n.tr("Load level")
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
        flickable: levelGrid
    }

    GridView {
        id: levelGrid
        anchors.fill: parent
        anchors.leftMargin: units.gu(0.5)
        anchors.rightMargin: units.gu(0.5)
        cellWidth: app.landscape ? width / 8 : width / 4
        cellHeight: cellWidth
        model: gameEngine.loadedLevels

        delegate: LevelSelectorItem {
            width: levelGrid.cellWidth
            height: levelGrid.cellHeight
            sourcePage: root
            level: gameEngine.loadedLevels.get(model.levelId)
            onSelected: {
                gameEngine.loadLevel(gameEngine.loadedLevels.get(levelId))
                pageLayout.addPageToCurrentColumn(root, Qt.resolvedUrl("BoardPage.qml"))
            }
        }
    }
}
