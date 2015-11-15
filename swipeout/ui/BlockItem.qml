import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Item {
    id: root
    property real cellSize
    property int blockId
    property int blockWidth
    property int blockHeight
    property int blockX
    property int blockY

    UbuntuShape {
        width: blockWidth * cellSize
        height: blockHeight * cellSize
        color: "#888888"

        x: blockX * app.cellSize
        y: blockY * app.cellSize

        MouseArea {
            id: elementMouseArea
            anchors.fill: parent

            drag.target: parent
            drag.axis: width > height ? Drag.XAxis : Drag.YAxis
            drag.minimumX: 0
            drag.maximumX: board.width - width
            drag.minimumY: 0
            drag.maximumY: board.height - height

            onPressed: {
                console.log("calculate limits")
                if (width > height) {
                    // check x limits

                } else {
                    // check y limits

                }
            }
        }

        onXChanged: {
            //console.log("x ="+ x)
        }
        onYChanged: {
            //console.log("y ="+ x)
        }
    }
}

