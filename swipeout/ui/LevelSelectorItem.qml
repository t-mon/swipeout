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

Item {
    id: root
    property var level: null

    signal selected()

    UbuntuShape {
        anchors.fill: parent
        anchors.margins: units.gu(1)
        backgroundColor: level.completed && level.completedPerfect ? "green" : level.completed ? "orange" : "#88888888"

        Column {
            anchors.centerIn: parent

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: level.id
                font.bold: true
            }
        }

        MouseArea {
            id: levelMouseArea
            anchors.fill: parent
            onClicked: {
                gameEngine.board.loadLevel(level)
                pageStack.push(Qt.resolvedUrl("BoardPage.qml"))
            }
        }
    }
}
