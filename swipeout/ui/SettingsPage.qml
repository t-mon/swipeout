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
import Ubuntu.Components.Popups 1.3
import Swipeout 1.0

Page {
    id: root
    // TRANSLATORS: Title of the settings page
    title: i18n.tr("Settings")

    Flickable {
        anchors.fill: parent
        contentHeight: columnLayout.height
        //enabled: height < columnLayout.height

        ColumnLayout {
            id: columnLayout
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: units.gu(2)


            Column {
                anchors.fill: parent
                anchors.margins: units.gu(2)

                spacing: units.gu(2)

                ThinDivider { }

                Label {
                    anchors.left: parent.left
                    // TRANSLATORS: In the settings page the slider description. Describes the speed of the animation while showing the solution.
                    text: i18n.tr("Show solution speed")
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
                        // TRANSLATORS: In the settings page the vibrations checkbox description.
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
                Item {
                    width: parent.width
                    height: units.gu(3)

                    Label {
                        anchors.left: parent.left
                        // TRANSLATORS: In the settings page the sound effect checkbox description.
                        text: i18n.tr("Sound effects")
                    }

                    CheckBox {
                        id: soundsCheckbox
                        anchors.right: parent.right
                        onCheckedChanged: {
                            gameEngine.settings.sounds = soundsCheckbox.checked
                        }
                        Component.onCompleted: checked = gameEngine.settings.sounds
                    }
                }
                ThinDivider { }

                Label {
                    anchors.left: parent.left
                    // TRANSLATORS: In the settings page the slider description.
                    text: i18n.tr("Sound volume")
                }

                Slider {
                    id: volumeSlider
                    width: parent.width

                    maximumValue: 100
                    minimumValue: 0
                    onValueChanged: {
                        gameEngine.settings.soundsVolume = volumeSlider.value
                    }
                    Component.onCompleted: value = gameEngine.settings.soundsVolume
                }


                ThinDivider { }

                Button {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    // TRANSLATORS: Reset game button in the settings page.
                    text: i18n.tr("Reset game")
                    color: "red"
                    onClicked: PopupUtils.open(resetComponent)
                }
                ThinDivider { }
            }
        }
    }

    Component {
        id: resetComponent
        Dialog {
            id: resetDialog
            // TRANSLATORS: Title of the reset dialog.
            title: i18n.tr("Reset game")
            // TRANSLATORS: Reset warning message. Please insert also the "\n" in the middle of the text!
            text: i18n.tr("Are you sure you want to reset all\ngame settings and achievements?")

            ThinDivider { }
            Button {
                // TRANSLATORS: Reset button in the reset dialog
                text: i18n.tr("Reset")
                color: "red"
                onClicked: {
                    gameEngine.resetSettings()
                    PopupUtils.close(resetDialog)
                }
            }

            Button {
                // TRANSLATORS: Button to cancel the reset request.
                text: i18n.tr("No")
                onClicked: PopupUtils.close(resetDialog)
            }
            ThinDivider { }

        }
    }

}
