import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Page {
    id: boardPage
    title: i18n.tr("Swipeout")

    property var level: 0

    property real gridSizeX: level.width
    property real gridSizeY: level.height
    property real cellSize: Math.min(width / gridSizeX, height / gridSizeY)

    UbuntuShape {
        id: board
        anchors.centerIn: parent
        anchors.margins: units.gu(2)
        width:  gridSizeX * cellSize
        height:  gridSizeY * cellSize

        backgroundColor: UbuntuColors.warmGrey

        Repeater {
            anchors.fill: parent
            model: level.blocks
            delegate: BlockItem {
                cellSize: boardPage.cellSize
                blockId: model.blockId
                blockX: model.blockX
                blockY: model.blockY
                blockWidth: model.blockWidth
                blockHeight: model.blockHeigth
            }

        }



    }
}
