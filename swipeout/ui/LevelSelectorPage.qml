import QtQuick 2.4
import Ubuntu.Components 1.3
import Swipeout 1.0

Page {
    id: root
    title: i18n.tr("Levels")

    GridView {
        id: levelGrid
        anchors.fill: parent
        anchors.margins: units.gu(1)
        cellWidth: units.gu(10)
        cellHeight: units.gu(10)
        model: gameEngine.levels

        delegate: LevelSelectorItem {
            width: levelGrid.cellWidth
            height: levelGrid.cellHeight
            levelId: model.levelId
            onSelected: {
                var level = gameEngine.levels.level(levelId)
                pageStack.push(Qt.resolvedUrl("BoardPage.qml"), { level: level } )
                //gameEngine.startGame(model.levelId)
            }
        }
    }
}
