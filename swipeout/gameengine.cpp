#include "gameengine.h"

#include <QDir>
#include <QDebug>
#include <QJsonDocument>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    m_levels(new Levels(this)),
    m_board(new Board(this))
{
    qDebug() << "Created game engine";
}

QString GameEngine::levelDir() const
{
    return m_levelDir;
}

void GameEngine::setLevelDir(const QString &levelDir)
{
    m_levelDir = levelDir;
    loadLevels();
    emit levelDirChanged();
}

Levels *GameEngine::levels()
{
    return m_levels;
}

Board *GameEngine::board()
{
    return m_board;
}

void GameEngine::loadLevel(const int &id)
{
    qDebug() << "Start level" << id;
    Level *level = m_levels->get(id);
    m_board->loadLevel(level);
}

void GameEngine::loadLevels()
{
    qDebug() << "loading levels from" << m_levelDir;

    QDir dir(m_levelDir);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList levelFiles = dir.entryInfoList();
    foreach (const QFileInfo &levelFileInfo, levelFiles) {
        QFile levelFile(levelFileInfo.absoluteFilePath());
        if (!levelFile.open(QFile::ReadOnly)) {
            qDebug() << "Cannot open level file for reading:" << levelFileInfo.absoluteFilePath();
            continue;
        }

        QJsonParseError error;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(levelFile.readAll(), &error);
        if (error.error != QJsonParseError::NoError) {
            qDebug() << "Cannot parse level file:" << error.errorString();
            continue;
        }

        QVariantMap levelData = jsonDoc.toVariant().toMap();
        qDebug() << "   -> loading level" << levelData.value("id").toInt() << "...";
        Level *level = new Level(this);
        level->setName(levelData.value("name").toString());
        level->setId(levelData.value("id").toInt());
        level->setHeight(levelData.value("height").toInt());
        level->setWidth(levelData.value("width").toInt());

        foreach (const QVariant &blockVariant, levelData.value("blocks").toList()) {
            QVariantMap blockData = blockVariant.toMap();
            qDebug() << "      -> loading block" << blockData.value("id").toInt() << "...";
            Block *block = new Block(blockData.value("id").toInt(),
                                     blockData.value("x").toInt(),
                                     blockData.value("y").toInt(),
                                     blockData.value("height").toInt(),
                                     blockData.value("width").toInt(),
                                     level);
            level->addBlock(block);
        }

        m_levels->addLevel(level);
    }
}
