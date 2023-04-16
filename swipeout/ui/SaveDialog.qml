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
import Lomiri.Components 1.3
import Lomiri.Components.Popups 1.3
import Lomiri.Components.ListItems 1.3
import Swipeout 1.0

Dialog {
    id: root
    // TRANSLATORS: Title of the save dialog.
    title: i18n.tr("Save Level")

    property int levelId : gameEngine.levelCreator.board.level.id

    // TRANSLATORS: Save question.
    text: i18n.tr("Do you want to save this level?")

    ThinDivider { }

    Label {
        id: pathText
        horizontalAlignment: Text.AlignHCenter
        text: "level-" + levelId + ".json"
    }

    ThinDivider { }

    Button {
        // TRANSLATORS: Save the current board.
        text: i18n.tr("Save")
        onClicked: {
            creator.saveLevel()
            gameEngine.loadCreatedLevels()
            creator.clearBoard()
            onClicked: PopupUtils.close(root)
        }
    }

    Button {
        // TRANSLATORS: Cancel the save process.
        text: i18n.tr("Cancel")
        onClicked: PopupUtils.close(root)
    }

}
