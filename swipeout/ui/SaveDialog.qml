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
    title: i18n.tr("Save Level")

    property int levelId : gameEngine.levelCreator.board.level.id

    text: i18n.tr("Do you want to save this level?")

    ThinDivider { }

    Text {
        id: pathText
        horizontalAlignment: Text.AlignHCenter
        text: "level-" + levelId + ".json"
    }

    ThinDivider { }

    Button {
        text: i18n.tr("Save")
        onClicked: {
            creator.saveLevel()
            gameEngine.loadCreatedLevels()
            onClicked: PopupUtils.close(root)
        }
    }

    Button {
        text: i18n.tr("Cancel")
        onClicked: PopupUtils.close(root)
    }

}
