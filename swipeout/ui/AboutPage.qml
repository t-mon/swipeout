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
    title: i18n.tr("About")

    Flickable {
        anchors.fill: parent
        anchors.margins: units.gu(2)
        contentHeight: columnLayout.height

        ColumnLayout {
            id: columnLayout
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: units.gu(2)

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

                Label {
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "2015 © Simon Stürz"
                }

                ThinDivider { }
            }

            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: units.gu(1)

                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(5)
                    spacing: units.gu(2)
                    Label {
                        // TRANSLATORS: In the about screen.
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
                        // TRANSLATORS: In the about screen.
                        text: i18n.tr("Source code:")
                        font.bold: true
                    }
                    Label {
                        text: "GitHub"
                        font.underline: true

                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://github.com/t-mon/swipeout")
                        }
                    }
                }

                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    spacing: units.gu(2)
                    Label {
                        // TRANSLATORS: In the about screen.
                        text: i18n.tr("Bug tracker:")
                        font.bold: true
                    }
                    Label {
                        text: "GitHub issues"
                        font.underline: true

                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("https://github.com/t-mon/swipeout/issues")
                        }
                    }
                }
                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    spacing: units.gu(2)
                    Label {
                        // TRANSLATORS: In the about screen.
                        text: i18n.tr("Mail:")
                        font.bold: true
                    }
                    Label {
                        text: "stuerz.simon@gmail.com"
                        font.underline: true

                        MouseArea {
                            anchors.fill: parent
                            onClicked: Qt.openUrlExternally("mailto:stuerz.simon@gmail.com")
                        }
                    }
                }

                ThinDivider { }

                Label {
                    // TRANSLATORS: Thank you very much for helping with the translations!! :)
                    text: i18n.tr("Thanks to all translators!")
                    font.underline: true
                    wrapMode: Text.WordWrap
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    anchors.right: parent.right

                    MouseArea {
                        anchors.fill: parent
                        onClicked: Qt.openUrlExternally("https://translations.launchpad.net/swipeout")
                    }
                }

                ThinDivider { }

                Label {
                    // TRANSLATORS: Donate button description
                    text: i18n.tr("Enjoying the game?")
                    font.bold: true
                    wrapMode: Text.WordWrap
                    anchors.horizontalCenter: parent.horizontalCenter
                }

                Button {
                    id: donateButton
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(5)
                    anchors.right: parent.right
                    anchors.rightMargin: units.gu(5)
                    color: "green"
                    // TRANSLATORS: Text in the Donate button
                    text: i18n.tr("Donate via PayPal")
                    font.underline: true
                    onClicked: Qt.openUrlExternally("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=MTXAYC3R425NG")
                }

                ThinDivider { }

                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    wrapMode: Text.WordWrap
                    color: "white"
                    // TRANSLATORS: Game description in the about screen.
                    text: i18n.tr("Swipeout is a classic unblock game. A level can be completed by pushing the white block through the right exit.\nHorizontal blocks can only be pushed \"left\" and \"right\", vertical blocks only \"up\" and \"down\".")
                }

                ThinDivider { }
            }
        }
    }
}
