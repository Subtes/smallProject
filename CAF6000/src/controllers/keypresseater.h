#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QObject>
#include <Windows.h>
#include <QDebug>

class KeyPressEater : public QObject
{
    Q_OBJECT
public:

    // Returns singleton instance
    static KeyPressEater * instance();

//    // Class destructor
    //~KeyPressEater();

    // Returns whether the keyboard hook is connected
    bool connected();

    // Connects / Disconnects the keyboard hook
    bool setConnected(bool state);

signals:
    // Broadcasts a key has been pressed
    void keyPressed(DWORD key);
    // Broadcasts a key has been released
    void keyReleased(DWORD key);

private:
    // Pointer to singleton instance
    static KeyPressEater *uniqueInstance;

    // Keyboard hook
    HHOOK keyboardHook;

    // Class constructor
    KeyPressEater();

    // Identifies hook activity
    static LRESULT CALLBACK keyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // KEYPRESSEATER_H




