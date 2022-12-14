#include "robot.h"

void togglePTO()
{
    if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1))
    {
        rightPiston.set_value(!ptoActivated);
        leftPiston.set_value(!ptoActivated);
        ptoActivated = !ptoActivated;
    }
}
void setPtoSpeed(int speed)
{
    lUFM = speed;
    rUFM = speed;
}
void ptoControls()
{
    if (ptoActivated) // when PTO engaged, default to PTO motors to spinning
    // forwards
    {
        if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
            setPtoSpeed(127);
        else if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
            setPtoSpeed(-127);
        else
            setPtoSpeed(0);
    }
}