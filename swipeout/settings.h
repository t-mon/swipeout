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

public slots:
};

#endif // SETTINGS_H
