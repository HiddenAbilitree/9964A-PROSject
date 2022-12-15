#include "robot.h"

// toggles the PTO mechanism
void togglePTO()
{
    // if controller's front right bumper is pressed, toggles the PTO mechanism
    if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        rightPiston.set_value(!ptoActivated);
        leftPiston.set_value(!ptoActivated);
        ptoActivated = !ptoActivated;
    }
}

// utility function to shorten code
void setPtoSpeed(int speed)
{
    lUFM = speed;
    rUFM = speed;
}

// the set of controls used when the PTO is activated
void ptoControls()
{
    // if the PTO is activated, check for a controller input to move the motors
    // attached to the PTO, otherwise, don't move motors
    if (ptoActivated)
    {
        if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            setPtoSpeed(127);
        else if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
            setPtoSpeed(-127);
        else
            setPtoSpeed(0);
    }
}