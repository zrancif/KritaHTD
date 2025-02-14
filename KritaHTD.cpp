/*
Krita: Touchpad as a Drawing Tablet
    Don't wanna buy a drawing tablet?
    Find drawing tablet weird to use?
    Find that MSPaint hold-space-to-draw very handy?
    Don't wanna download app to do this like AutoHotkey?

    Here's my untitled tool to replicate the MSPaint hold-space-to-draw!
    Requirements: 
        Optional: Universal (non-bluetooth) Stylus / a DIY stylus  > recommended
        Touchpad (cuz u might wanna use that as a mini drawing tablet) / mouse
    
        How to use:
        1. Use touchpad/mouse as normal, but for convenience, hold (`) or (*) to draw like MSPaint's hold-space-to-draw

Important Notes:
    1. Specifically made for Krita (window title = "Krita" on the window's top-left corner)
    2. Will not work on other apps

Notes:
    I did this because I don't wanna download extra files for a simple function. So I made this small program as small as I possibly can.
    Yeah... That's why.
*/
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// Function to get the window title of the currently focused window
string getActiveWindowTitle() {
    char windowTitle[256];
    HWND hwnd = GetForegroundWindow();
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
    return string(windowTitle);
}

int main() {
    cout<<"You can inspect it yourself. So you can see there is no virus whatsoever, I promise.\nI'm not familiar with GUI yet so its a console.\n\nThe button to initiate click is this >> ` [Right-Handed] or * [Left-handed, at numpad]\nLeave this running in the background while you use it.\n\nPress Ctrl + C in this window to stop and close.";
    
    bool isMouseHeld = false;  // Flag to track if the mouse is being held down

    while (true) {
        // Check if the active window is Krita
        string activeWindowTitle = getActiveWindowTitle();
        if (activeWindowTitle.find("Krita") != string::npos) {
            // Check if the backtick key (`) or numpad multiply key(*) is pressed
            bool backtickPressed = ((GetAsyncKeyState(VK_OEM_3) & 0x8000)) || ((GetAsyncKeyState(VK_MULTIPLY) & 0x8000));
            // If backtick is pressed and mouse isn't already held, simulate mouse press
            if (backtickPressed && !isMouseHeld) {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                isMouseHeld = true;  // Set flag to track the mouse is being held down
            }

            // If backtick is released, release the mouse
            if (!backtickPressed && isMouseHeld) {
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                isMouseHeld = false;  // Reset the flag to stop holding the mouse
            }
        }

        // Sleep to reduce CPU usage (10 ms)
        Sleep(10);
    }

    return 0;
}
