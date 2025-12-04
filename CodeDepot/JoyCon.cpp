#include "JoyCon.h"
#include <iostream>

JoyConInput::JoyConInput() {
    ZeroMemory(previous, sizeof(previous));
}

float JoyConInput::NormalizeStick(SHORT value) {
    return (value < 0) ? value / 32768.0f : value / 32767.0f;
}

void JoyConInput::Update() {
    XINPUT_STATE state;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++) {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(i, &state);

        if (result == ERROR_SUCCESS) {
            //JoyConState* jc = (i == 0) ? &left : &right;
            JoyConState* jc = &joyCon1; // << since im using one pair of joycons
            // Update buttons
            jc->buttons = state.Gamepad.wButtons;

            // Map sticks
            jc->leftStickX = NormalizeStick(state.Gamepad.sThumbLX);
            jc->leftStickY = NormalizeStick(state.Gamepad.sThumbLY);
            jc->rightStickX = NormalizeStick(state.Gamepad.sThumbRX);
            jc->rightStickY = NormalizeStick(state.Gamepad.sThumbRY);

            previous[i] = state;
        }
    }
}

JoyConState JoyConInput::GetJoycon1() const {
    return joyCon1;
}



bool JoyConInput::IsButtonPressed(int controllerIndex, WORD button) const {
    if (controllerIndex == 0) return (joyCon1.buttons & button) != 0;
    //if (controllerIndex == 1) return (right.buttons & button) != 0;
    return false;
}

