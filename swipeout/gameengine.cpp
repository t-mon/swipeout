#include "gameengine.h"

#include <QDir>
#include <QDebug>
#include <QJsonDocument>

GameEngine::GameEngine(QObject *parent) :
    QObject(parent),
    m_levels(new Levels(this))
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
            Block *block = new Block(level);
            block->setId(blockData.value("id").toInt());
            block->setX(blockData.value("x").toInt());
            block->setY(blockData.value("y").toInt());
            block->setWidth(blockData.value("width").toInt());
            block->setHeight(blockData.value("height").toInt());
            level->addBlock(block);
        }

        m_levels->addLevel(level);
    }
}
