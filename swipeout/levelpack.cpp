#include "levelpack.h"

#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QJsonDocument>

LevelPack::LevelPack(const QString &levelDir, const QString &name, QObject *parent) :
    QObject(parent),
    m_levelDir(levelDir),
    m_name(name),
    m_levels(new Levels(this))
{

}

QString LevelPack::name() const
{
    return m_name;
}

void LevelPack::setName(const QString &name)
{
    m_name = name;
}

Levels *LevelPack::levels()
{
    return m_levels;
}

void LevelPack::loadLevels()
{
    qDebug() << "Loading level pack"<< m_name <<  "from" << m_levelDir;

    QDir dir(m_levelDir + m_name);
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name);

    QFileInfoList levelFiles = dir.entryInfoList();
    foreach (const QFileInfo &levelFileInfo, levelFiles) {
        if (!levelFileInfo.fileName().startsWith("level") || !levelFileInfo.fileName().endsWith(".json"))
            continue;

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
        level->setBlockData(levelData.value("blocks").toList());
        level->setLevelPackName(m_name);

        // load record / completed
        QSettings settings;
        settings.beginGroup(m_name);
        settings.beginGroup(level->name());
        level->setCompleted(settings.value("completed", false).toBool());
        level->setRecord(settings.value("record", 0).toInt());
        settings.endGroup();
        settings.endGroup();

        // load solution moves
        QList<Move> moves;
        foreach (const QVariant &moveData, levelData.value("solution").toList()) {
            QVariantMap moveMap = moveData.toMap();
            Move move(moveMap.value("block").toInt(), moveMap.value("step").toInt(), moveMap.value("delta").toInt());
            moves.append(move);
        }
        qSort(moves.begin(), moves.end(), compareMove);

        QStack<Move> solution;
        for (int i = 0; i < moves.count(); i++) {
            solution.push(moves.at(i));
        }
        level->setSolution(solution);

        m_levels->addLevel(level);
    }
}

void LevelPack::unloadLevels()
{
    qDebug() << "Unload levels from levelpack" << m_name;
    m_levels->deleteAllLevels();
}

