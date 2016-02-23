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

#include "settings.h"

#include <QSettings>
#include <QDebug>

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Load game settings" << endl << "--------------------------------------";
    QSettings settings;
    settings.beginGroup("Swipeout");
    setShowSolutionSpeed(settings.value("showSolutionSpeed", 500).toInt());
    setVibrations(settings.value("vibrations", true).toBool());
    setSounds(settings.value("sounds", true).toBool());
    setSoundsVolume(settings.value("soundsVolume", 50).toInt());
    setBlockTheme(settings.value("blockTheme", "Dark").toString());
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

bool Settings::sounds() const
{
    return m_sounds;
}

void Settings::setSounds(const bool &sounds)
{
    m_sounds = sounds;
    qDebug() << "sounds = " << sounds;
    QSettings settings;
    settings.beginGroup("Swipeout");
    settings.setValue("sounds", sounds);
    settings.endGroup();
    emit soundsChanged();
}

int Settings::soundsVolume() const
{
    return m_soundsVolume;
}

void Settings::setSoundsVolume(const int &volume)
{
    m_soundsVolume = volume;
    qDebug() << "sounds volume = " << volume;
    QSettings settings;
    settings.beginGroup("Swipeout");
    settings.setValue("soundsVolume", volume);
    settings.endGroup();
    emit soundsVolumeChanged();
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

QString Settings::blockTheme() const
{
    return m_blockTheme;
}

void Settings::setBlockTheme(const QString &blockTheme)
{
    m_blockTheme = blockTheme;
    qDebug() << "block theme = " << blockTheme;
    QSettings settings;
    settings.beginGroup("Swipeout");
    settings.setValue("blockTheme", blockTheme);
    settings.endGroup();
    emit blockThemeChanged();
}

void Settings::resetSettings()
{
    setShowSolutionSpeed(500);
    setVibrations(true);
    setVibrations(true);

    QSettings settings;
    settings.beginGroup("levelpacks");
    settings.remove("");
    settings.endGroup();
}

