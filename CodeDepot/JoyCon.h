#pragma once
#include <windows.h>
#include <Xinput.h>
#include <unordered_map>
#include <string>
#pragma comment(lib, "Xinput.lib")

struct JoyConState {
    WORD buttons = 0;

    // Left stick (Left Joy-Con)
    float leftStickX = 0;
    float leftStickY = 0;

    // Right stick (Right Joy-Con)
    float rightStickX = 0;
    float rightStickY = 0;
};

class JoyConInput {
public:
    JoyConInput();
    void Update();                    // Polls both Joy-Cons
    JoyConState GetJoycon1() const;      // Controller 0 // this gets both the left and right joycon pairs
    //JoyConState GetRight() const;     // Controller 1 // not used
    bool IsButtonPressed(int controllerIndex, WORD button) const;

private:
    JoyConState joyCon1; //gets the joycon(paired)                , right; // not used
    XINPUT_STATE previous[XUSER_MAX_COUNT];
    float NormalizeStick(SHORT value);
};

