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
    title: i18n.tr("Settings")

    Column {
        anchors.fill: parent
        anchors.margins: units.gu(3)

        spacing: units.gu(2)

        ThinDivider { }

        Label {
            anchors.left: parent.left
            text: i18n.tr("Show solution speed [ms]")
        }

        Slider {
            id: speedSlider
            width: parent.width
            maximumValue: 1000
            minimumValue: 250
            onValueChanged: {
                gameEngine.settings.showSolutionSpeed = speedSlider.value
            }
            Component.onCompleted: value = gameEngine.settings.showSolutionSpeed
        }

        ThinDivider { }

        Item {
            width: parent.width
            height: units.gu(3)

            Label {
                anchors.left: parent.left
                text: i18n.tr("Vibrations")
            }

            CheckBox {
                id: vibrationCheckbox
                anchors.right: parent.right
                onCheckedChanged: {
                    gameEngine.settings.vibrations = vibrationCheckbox.checked
                }
                Component.onCompleted: checked = gameEngine.settings.vibrations
            }
        }

        ThinDivider { }
    }
}
