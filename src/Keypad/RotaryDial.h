#ifndef KEYPAD_ROTARYDIAL_H
#define KEYPAD_ROTARYDIAL_H

namespace Keypad
{
namespace RotaryDial
{

    enum RotaryDialMovement
    {
        ROTARY_DIAL_MOVEMENT_NONE = 0,
        ROTARY_DIAL_MOVEMENT_CLOCKWISE,
        ROTARY_DIAL_MOVEMENT_COUNTERCLOCKWISE,
    };
    /**
     * @brief Initialize the Rotary Dial System
     * 
     * This function sets up the GPIO pins and interrupts for the rotary dial.
     */
void InitRotaryDialSystem();
}
}

#endif // KEYPAD_ROTARYDIAL_H
