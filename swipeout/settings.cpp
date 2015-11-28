#include "settings.h"

#include <QSettings>
#include <QDebug>

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    QSettings settings;
    settings.beginGroup("Swipeout");
    setShowSolutionSpeed(settings.value("showSolutionSpeed", 500).toInt());
    setVibrations(settings.value("vibrations", true).toBool());
    settings.endGroup();
}

bool Settings::vibrations() const
{
    return m_vibrations;
}

void Settings::setVibrations(const bool &vibrations)
{
    m_vibrations = vibrations;
    qDebug() << "vibrations = " << vibrations;
    QSettings settings;
    settings.beginGroup("Swipeout");
    settings.setValue("vibrations", vibrations);
    settings.endGroup();
    emit vibrationsChanged();
}

int Settings::showSolutionSpeed() const
{
    return m_showSolutionSpeed;
}

void Settings::setShowSolutionSpeed(const int &showSolutionSpeed)
{
    m_showSolutionSpeed = showSolutionSpeed;
    qDebug() << "show solution speed = " << showSolutionSpeed;
    QSettings settings;
    settings.beginGroup("Swipeout");
    settings.setValue("showSolutionSpeed", showSolutionSpeed);
    settings.endGroup();
    emit showSolutionSpeedChanged();
}

void Settings::resetSettings()
{
    setShowSolutionSpeed(500);
    setVibrations(false);

    QSettings settings;
    settings.beginGroup("levelpacks");
    settings.remove("");
    settings.endGroup();
}

