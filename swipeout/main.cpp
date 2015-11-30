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

#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QDebug>
#include <QDir>

#include "gameengine.h"
#include "block.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setApplicationName("Swipeout");
    app.setApplicationVersion("0.1.0");

    // command line parser
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    parser.setApplicationDescription(QString("\nClassic swipe out game.\n\n"
                                             "Copyright %1 2015 Simon Stürz <stuerz.simon@gmail.com>\n"
                                             "Released under the GNU GPLv3.").arg(QChar(0xA9)));
    parser.addPositionalArgument("levelPath", "The relative file path where the \"levels\" folders can be found (optional).", "[levelPath]");
    parser.process(app);

    qmlRegisterType<GameEngine>("Swipeout", 1, 0, "GameEngine");
    qmlRegisterUncreatableType<Board>("Swipeout", 1, 0, "Board", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Level>("Swipeout", 1, 0, "Level", "Can't create this in QML. Get it from Levels.");
    qmlRegisterUncreatableType<Levels>("Swipeout", 1, 0, "Levels", "Can't create this in QML. Get it from the LevelPack.");
    qmlRegisterUncreatableType<LevelPack>("Swipeout", 1, 0, "LevelPack", "Can't create this in QML. Get it from the LevelPacks.");
    qmlRegisterUncreatableType<LevelPacks>("Swipeout", 1, 0, "LevelPacks", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<LevelCreator>("Swipeout", 1, 0, "LevelCreator", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Block>("Swipeout", 1, 0, "Block", "Can't create this in QML. Get it from Blocks.");
    qmlRegisterUncreatableType<Blocks>("Swipeout", 1, 0, "Blocks", "Can't create this in QML. Get it from the Level.");
    qmlRegisterUncreatableType<Settings>("Swipeout", 1, 0, "Settings", "Can't create this in QML. Get it from the GameEngine.");

    QQuickView view;
    if (!parser.positionalArguments().isEmpty()) {
        QDir dataDir(QDir::cleanPath(QCoreApplication::applicationDirPath() + "/" + parser.positionalArguments().first()));
        if (!dataDir.exists()) {
            qWarning() << dataDir.path() << "does not exist.";
            exit(-1);
        }
        view.engine()->rootContext()->setContextProperty("levelDirectory", dataDir.path() + "/");
        dataDir.cdUp();
        view.engine()->rootContext()->setContextProperty("soundDirectory", dataDir.path() + "/sounds/");
    } else {
        view.engine()->rootContext()->setContextProperty("levelDirectory",QCoreApplication::applicationDirPath() + "/../../../swipeout/levels/");
        view.engine()->rootContext()->setContextProperty("soundDirectory",QCoreApplication::applicationDirPath() + "/../../../swipeout/sounds/");
    }
    view.engine()->rootContext()->setContextProperty("version", app.applicationVersion());
    view.setSource(QUrl(QStringLiteral("qrc:///ui/Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();

    return app.exec();
}

