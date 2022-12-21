#pragma once // explanation under robot.h
#include "robot.hpp"

// functions in functions.cpp
void setPTOSpeed(int speed = 0);

// inline functions

// toggles the PTO mechanism when the front right bumper is pressed
inline void togglePTO()
{
    // if controller's front right bumper is pressed, toggles the PTO mechanism
    if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        rightPiston.set_value(!ptoActivated);
        leftPiston.set_value(!ptoActivated);
        ptoActivated = !ptoActivated;
    }
};

// the set of controls used when the PTO is activated
inline void ptoControls()
{
    // if the PTO is activated, check for a controller input to move the motors
    // attached to the PTO, otherwise, don't move motors
    if (ptoActivated)
    {
        if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            setPTOSpeed(127);
        else if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
            setPTOSpeed(-127);
        else
            setPTOSpeed();
    }
};

// toggles the pneumatic piston state used for the extension mechanism
inline void extension()
{
    if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
    {
        jerry.set_value(!extensionActivated);
        extensionActivated = !extensionActivated;
    }
};