import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

MainView {
    id: app
    objectName: "mainView"
    applicationName: "swipeout.t-mon"

    height: units.gu(70)
    width: units.gu(40)

    GameEngine {
        id: gameEngine
        levelDir: levelDirectory
    }

    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: push(Qt.resolvedUrl("MainPage.qml"))
    }
}

