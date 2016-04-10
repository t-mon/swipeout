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
    header: PageHeader {
        id: pageHeader
        title: i18n.tr("Help")
    }

    Column {
        anchors.fill: parent
        anchors.topMargin: pageHeader.height + units.gu(2)
        anchors.leftMargin: units.gu(2)
        anchors.rightMargin: units.gu(2)
        spacing: units.gu(3)

        Column {
            spacing: units.gu(1)

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                anchors.right: parent.left
                anchors.rightMargin: units.gu(2)

                spacing: units.gu(2)

                UbuntuShape {
                    width: units.gu(5)
                    height: width
                    backgroundColor: uncompletedColor
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    // TRANSLATORS: Color description in the menu help screen for not completed levels.
                    text: i18n.tr("Not completed")
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                anchors.right: parent.left
                anchors.rightMargin: units.gu(2)

                spacing: units.gu(2)

                UbuntuShape {
                    width: units.gu(5)
                    height: width
                    backgroundColor: completedColor
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    // TRANSLATORS: Color description in the menu help screen for completed levels.
                    text: i18n.tr("Completed")
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                anchors.right: parent.left
                anchors.rightMargin: units.gu(2)

                spacing: units.gu(2)

                UbuntuShape {
                    width: units.gu(5)
                    height: width
                    backgroundColor: completedPerfectColor
                }

                Label {
                    anchors.verticalCenter: parent.verticalCenter
                    // TRANSLATORS: Color description in the menu help screen for completed perfect levels.
                    text: i18n.tr("Completed perfect")
                }
            }

            ThinDivider { }

        }
    }
}
