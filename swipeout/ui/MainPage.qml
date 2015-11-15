import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr("Swipeout")

    Button {
        anchors.centerIn: parent
        text: "Play"
        onClicked: {
            push(Qt.resolvedUrl("LevelSelectorPage.qml"))
        }
    }

}
