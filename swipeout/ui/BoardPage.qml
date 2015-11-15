import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr(level.name)

    property var level: null
    property real borderWidth: units.gu(1.5)
    property real cellSize: Math.min(width / level.width , height / level.height)

    head.actions: Action {
        id: addDeviceAction
        iconName: "reload"
        text: i18n.tr("Reset board")
        onTriggered: {
            gameEngine.board.resetBoard()
            //for (int i = 0; i < )

        }
    }


    Column {
        anchors.centerIn: parent
        UbuntuShape {
            id: boardBackground
            width: level.width * cellSize
            height: level.height * cellSize

            backgroundColor: UbuntuColors.darkGrey

            UbuntuShape {
                id: board
                anchors.fill: parent
                anchors.margins: borderWidth
                backgroundColor: UbuntuColors.warmGrey

                Rectangle {
                    id: exitShape
                    color: board.backgroundColor
                    width: 2 * borderWidth
                    height: Math.min(parent.width / level.width , parent.height / level.height)
                    anchors.right: parent.right
                    anchors.rightMargin: -borderWidth
                    anchors.top: parent.top
                    anchors.topMargin: level.blocks.get(0).y * height
                }

                Repeater {
                    id: blockRepeater
                    anchors.fill: parent
                    model: level.blocks
                    delegate: BlockItem {
                        cellSize: Math.min(board.width / level.width , board.height / level.height)
                        block: level.blocks.get(model.blockId)
                    }
                }
            }
        }

        Text {
            text: gameEngine.board.moveCount
        }
    }
}
