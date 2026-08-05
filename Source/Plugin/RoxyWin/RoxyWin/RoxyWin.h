#pragma once

#include <RoxySTD/RoxySTD.h>

ROXY_DISABLE_WARNINGS()
#include <RGFW.h>
ROXY_RESTORE_WARNINGS()

namespace Roxy::Input
{

enum class EKey : U8
{
    /* Keyboard */
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    Delete, Insert, Pause, Break, Home, End,
    Up,Down,Left,Right,
    TAB,CAPS,Space,Enter,Back,Escape,
    LShift,LCtrl,LAlt,RShift,RCtrl,RAlt,
    /* Mouse */
    Mouse_Left,
    Mouse_Right,
    Mouse_Wheel,
    Mouse_Extra_0,
    Mouse_Extra_1,
    Mouse_Extra_2,
    Mouse_Extra_3,
    Mouse_Extra_4,
    Mouse_Extra_5,
    Mouse_Extra_6,
    Mouse_Extra_7,
    Mouse_Extra_8,
    Mouse_Extra_9,
    /* Gamepad */
    Gamepad_Button_U,
    Gamepad_Button_D,
    Gamepad_Button_L,
    Gamepad_Button_R,
    Gamepad_Button_A,
    Gamepad_Button_B,
    Gamepad_Button_X,
    Gamepad_Button_Y,
    Gamepad_Button_Menu,
    Gamepad_Button_Map,
    Gamepad_Trigger_L1,
    Gamepad_Trigger_L2,
    Gamepad_Trigger_R1,
    Gamepad_Trigger_R2,
    Gamepad_Stick_L,
    Gamepad_Stick_R,
    Gamepad_Back_L1,
    Gamepad_Back_L2,
    Gamepad_Back_R1,
    Gamepad_Back_R2,
    Gamepad_Extra_0,
    Gamepad_Extra_1,
    Gamepad_Extra_2,
    Gamepad_Extra_3,
    Gamepad_Extra_4,
    Gamepad_Extra_5,
    Gamepad_Extra_6,
    Gamepad_Extra_7,
    Gamepad_Extra_8,
    Gamepad_Extra_9,
};

class Input
{
public:
    EKey  Key {};
    float X   {};
    float Y   {};
    float Z   {}; /* Input Amount [0, 1] */
};

}
