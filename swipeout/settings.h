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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool vibrations READ vibrations WRITE setVibrations NOTIFY vibrationsChanged)
    Q_PROPERTY(int showSolutionSpeed READ showSolutionSpeed WRITE setShowSolutionSpeed NOTIFY showSolutionSpeedChanged)

public:
    explicit Settings(QObject *parent = 0);

    bool vibrations() const;
    void setVibrations(const bool &vibrations);

    int showSolutionSpeed() const;
    void setShowSolutionSpeed(const int &showSolutionSpeed);

    void resetSettings();

private:
    bool m_vibrations;
    int m_showSolutionSpeed;

signals:
    void vibrationsChanged();
    void showSolutionSpeedChanged();

};

#endif // SETTINGS_H
