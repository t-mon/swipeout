import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Item {
    id: root
    property int levelId: levelId

    signal selected()

    UbuntuShape {
        anchors.fill: parent
        anchors.margins: units.gu(1)

        Text {
            anchors.centerIn: parent
            text: levelId
        }

        MouseArea {
            id: levelMouseArea
            anchors.fill: parent
            onClicked: {
                //if (unlocked) {
                    root.selected()
                //}
            }
        }
    }

}
