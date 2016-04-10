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
        // TRANSLATORS: Title of the Level Creator help screen.
        title: i18n.tr("Level creator help")
        flickable: helpFlickable
    }

    Flickable {
        id: helpFlickable
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
                spacing: units.gu(1)

                Text {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    wrapMode: Text.WordWrap
                    color: "white"
                    // TRANSLATORS: Level creator description in the help screen.
                    text: i18n.tr("In the level creator you can create your own levels containig the perfect solution by using the solver. Only solved boards can be stored as level. The level number will increase automatically. You can load and play created levels from the main menu \"Load level\".")
                }

                ThinDivider { }

                Label {
                    // TRANSLATORS: Sub title of the creator help screen for the block tools
                    text: i18n.tr("Block tools:")
                    font.bold: true
                    font.pixelSize: units.gu(3)
                }

                ThinDivider { }

                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    anchors.right: parent.left
                    anchors.rightMargin: units.gu(2)

                    spacing: units.gu(2)

                    UbuntuShape {
                        width: units.gu(5)
                        height: width
                        backgroundColor: "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "delete"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Delete block")
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
                        backgroundColor: "#88888888"

                        Image {
                            anchors.fill: parent
                            source: "qrc:///images/twoHorizontal.svg"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Create 2 x 1 block")
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
                        backgroundColor: "#88888888"

                        Image {
                            anchors.fill: parent
                            source: "qrc:///images/threeHorizontal.svg"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Create 3 x 1 block")
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
                        backgroundColor: "#88888888"

                        Image {
                            anchors.fill: parent
                            source: "qrc:///images/twoVertical.svg"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Create 1 x 2 block")
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
                        backgroundColor: "#88888888"

                        Image {
                            anchors.fill: parent
                            source: "qrc:///images/threeVertical.svg"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Create 1 x 3 block")
                    }
                }
            }


            Column {
                anchors.left: parent.left
                anchors.right: parent.right
                spacing: units.gu(1)

                ThinDivider { }

                Label {
                    // TRANSLATORS: Sub title of the creator help screen for the board tools
                    text: i18n.tr("Board tools:")
                    font.bold: true
                    font.pixelSize: units.gu(3)
                }

                ThinDivider { }

                Row {
                    anchors.left: parent.left
                    anchors.leftMargin: units.gu(2)
                    anchors.right: parent.left
                    anchors.rightMargin: units.gu(2)

                    spacing: units.gu(2)

                    UbuntuShape {
                        width: units.gu(5)
                        height: width
                        backgroundColor: "#88ff8888"

                        Icon {
                            anchors.centerIn: parent
                            width: Math.min(parent.height, parent.width) - units.gu(1)
                            height: Math.min(parent.height, parent.width) - units.gu(1)
                            name: "delete"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Clear board")
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
                        backgroundColor: "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "reload"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Create random level")
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
                        backgroundColor: "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "torch-on"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Solve board")
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
                        backgroundColor: "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "save"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Save level")
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
                        backgroundColor: "#88888888"

                        Icon {
                            anchors.fill: parent
                            anchors.margins: units.gu(1)
                            name: "torch-off"
                        }
                    }

                    Label {
                        anchors.verticalCenter: parent.verticalCenter
                        // TRANSLATORS: Tool description in the Creator Help view.
                        text: i18n.tr("Show solution")
                    }
                }
            }
        }
    }
}

