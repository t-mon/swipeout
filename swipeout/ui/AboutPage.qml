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
    title: i18n.tr("About")

    Column {
        anchors.fill: parent
        spacing: units.gu(3)

        Column {
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: units.gu(2)
            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "Swipeout"
                font.bold: true
                font.pixelSize: units.gu(5)
            }

            Label {
                anchors.horizontalCenter: parent.horizontalCenter
                text: version
                font.bold: true
                font.pixelSize: units.gu(3)
            }

            ThinDivider { }
        }


        Column {
            spacing: units.gu(1)

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(5)
                spacing: units.gu(2)
                Label {
                    text: i18n.tr("Author:")
                    font.bold: true
                }
                Label { text: "Simon Stürz" }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(5)
                spacing: units.gu(2)
                Label {
                    text: i18n.tr("License:")
                    font.bold: true
                }
                Label {
                    text: "GPLv3"
                    font.underline: true
                    MouseArea {
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally("https://www.gnu.org/licenses/gpl-3.0.html")
                    }
                }
            }

            Row {
                anchors.left: parent.left
                anchors.leftMargin: units.gu(2)
                spacing: units.gu(2)
                Label {
                    text: "Source code:"
                    font.bold: true
                }
                Label {
                    font.underline: true
                    text: app.landscape ? "https://github.com/t-mon/swipeout" : "https://github.com/t-mon/\nswipeout"

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally("https://github.com/t-mon/swipeout")
                    }
                }
            }
        }

        ThinDivider { }

    }
}
