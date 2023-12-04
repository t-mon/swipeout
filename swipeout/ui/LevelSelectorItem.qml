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

Item {
    id: root
    property var level: null
    property var sourcePage
    signal selected()

    LomiriShape {
        id: shape
        anchors.fill: parent
        anchors.margins: units.gu(1)
        backgroundColor: level.completed && level.completedPerfect ? completedPerfectColor : level.completed ? completedColor : uncompletedColor

        Column {
            anchors.centerIn: parent

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: level.id
                font.bold: true
                color: shape.backgroundColor == uncompletedColor ? "white" : "black"
            }
        }

        MouseArea {
            id: levelMouseArea
            anchors.fill: parent
            onClicked: {
                gameEngine.loadLevel(level)
                pageLayout.addPageToCurrentColumn(sourcePage, Qt.resolvedUrl("BoardPage.qml"))
            }
        }
    }
}
