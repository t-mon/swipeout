#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQuickView>
#include <QDebug>
#include <QDir>

#include "gameengine.h"

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
    qmlRegisterUncreatableType<Level>("Swipeout", 1, 0, "Level", "Can't create this in QML. Get it from Levels.");
    qmlRegisterUncreatableType<Levels>("Swipeout", 1, 0, "Levels", "Can't create this in QML. Get it from the GameEngine.");
    qmlRegisterUncreatableType<Block>("Swipeout", 1, 0, "Block", "Can't create this in QML. Get it from Blocks.");
    qmlRegisterUncreatableType<Blocks>("Swipeout", 1, 0, "Blocks", "Can't create this in QML. Get it from the Level.");

    QQuickView view;
    if (!parser.positionalArguments().isEmpty()) {
        QDir dataDir(QDir::cleanPath(QCoreApplication::applicationDirPath() + "/" + parser.positionalArguments().first()));
        if (!dataDir.exists()) {
            qWarning() << dataDir.path() << "does not exist.";
            exit(-1);
        }
        view.engine()->rootContext()->setContextProperty("levelDirectory", dataDir.path() + "/");
    } else {
        view.engine()->rootContext()->setContextProperty("levelDirectory",QCoreApplication::applicationDirPath() + "/../../../levels/");
    }
    view.engine()->rootContext()->setContextProperty("version", app.applicationVersion());
    view.setSource(QUrl(QStringLiteral("qrc:///ui/Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.show();
    return app.exec();
}

