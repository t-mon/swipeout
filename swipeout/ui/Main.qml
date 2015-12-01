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
import QtMultimedia 5.4
import Ubuntu.Components 1.3
import Swipeout 1.0

MainView {
    id: app
    objectName: "mainView"
    applicationName: "swipeout.t-mon"

    property bool debug: false
    property bool landscape: height < width

    property color boardBoarderColor: "#333333"
    property color boardColor: "#ff555555"
    property color uncompletedColor: "#88888888"
    property color completedColor: "#aaffd040"
    property color completedPerfectColor: "#aa6ad709"

    height: units.gu(70)
    width: units.gu(40)

    Component.onCompleted: {
        i18n.domain = "swipeout.t-mon"
        Theme.name = "Ubuntu.Components.Themes.SuruDark"
    }

    SoundEffect {
        id: soundEffect
        source: "file://" + dataDirectory + "sounds/pop.wav"
        volume: gameEngine.settings.soundsVolume / 100
        Component.onCompleted: console.log("Sound effect: " + dataDirectory + "sounds/pop.wav")
    }

    GameEngine {
        id: gameEngine
        dataDir: dataDirectory
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(Qt.resolvedUrl("MainPage.qml"))
    }
}

