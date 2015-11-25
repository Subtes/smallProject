#include "keypresseater.h"

KeyPressEater::KeyPressEater():
    QObject()
{
    // Assign to null
    keyboardHook = NULL;
}

LRESULT CALLBACK KeyPressEater::keyboardProcedure(int nCode, WPARAM wParam, LPARAM lParam)
{
    // Check for a key down press
    if (nCode == HC_ACTION)
    {
        if (wParam == WM_KEYDOWN)
        {
            KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
            emit KeyPressEater::instance()->keyPressed((DWORD) pKeyboard->vkCode);
        }
        else if (wParam == WM_KEYUP)
        {
            KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
            emit KeyPressEater::instance()->keyReleased((DWORD) pKeyboard->vkCode);
        }
        //reconnect
        //instance()->setConnected( false );
        //instance()->setConnected( true );
    }

    return false;
}

bool KeyPressEater::connected()
{
    return keyboardHook;
}

bool KeyPressEater::setConnected(bool state)
{
    if(state && keyboardHook == NULL)
    {
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProcedure, GetModuleHandle(NULL), 0);
        return keyboardHook;
    }
    else
    {
        UnhookWindowsHookEx(keyboardHook);
        keyboardHook = NULL;

        return keyboardHook;
    }
}

KeyPressEater* KeyPressEater::instance()
{
    static KeyPressEater* pKeyPressEaterInstance = new KeyPressEater();
    return pKeyPressEaterInstance;
}
