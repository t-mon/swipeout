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
import Ubuntu.Components 1.3
import Ubuntu.Components.Popups 1.3
import Ubuntu.Components.ListItems 1.3
import Swipeout 1.0

Dialog {
    id: root
    // TRANSLATORS: Title of the solver dialog
    title: i18n.tr("Level Solver")

    property bool solutionFound: false

    // TRANSLATORS: Status of the solver
    text: gameEngine.solverRunning ? i18n.tr("Solving...") : i18n.tr("Finished!")

    ThinDivider { }

    Text {
        id: runTimeText
        visible: !gameEngine.solverRunning && solutionFound
        horizontalAlignment: Text.AlignHCenter
        text: ""
    }

    Text {
        id: solutionText
        visible: !gameEngine.solverRunning
        horizontalAlignment: Text.AlignHCenter
        text: ""
    }

    Text {
        id: moveText
        visible: !gameEngine.solverRunning
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: units.gu(5)
        font.bold: true
        text: ""
    }

    ActivityIndicator {
        visible: gameEngine.solverRunning
        running: gameEngine.solverRunning
    }

    ThinDivider { }

    Button {
        visible: !gameEngine.solverRunning && solutionFound
        // TRANSLATORS: Save the solved level.
        text: i18n.tr("Save")
        onClicked: {
            gameEngine.levelCreator.saveLevel()
            gameEngine.loadCreatedLevels()
            gameEngine.levelCreator.clearBoard()
            onClicked: PopupUtils.close(root)
        }
    }

    Button {
        visible: !gameEngine.solverRunning && solutionFound
        // TRANSLATORS: Show the solution moves on the board.
        text: i18n.tr("Show solution")
        onClicked: {
            PopupUtils.close(root)
            gameEngine.levelCreator.board.showSolution()
        }
    }

    Button {
        text: gameEngine.solverRunning ? i18n.tr("Cancel") : i18n.tr("Close")
        onClicked: {
            if (gameEngine.solverRunning)
                gameEngine.stopSolvingBoard()

            PopupUtils.close(root)
        }
    }

    Connections {
        target: gameEngine
        onSolutionReady: {
            // TRANSLATORS: The runtime of the solver once he is finished.
            runTimeText.text = i18n.tr("Runtime") + ": " + runTime
            var moveCount = gameEngine.levelCreator.board.level.solutionCount
            if (moveCount == 0) {
                // TRANSLATORS: The message that this board cannot be solved (in the solver view).
                solutionText.text = i18n.tr("This board can't be solved.")
            } else {
                solutionFound = true
                // TRANSLATORS: Description of the solver result.
                solutionText.text = i18n.tr("Perfect solution:")
                moveText.text = moveCount
            }
        }
    }
}
