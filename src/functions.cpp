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

void ptoControls()
{
    if (ptoActivated) // when PTO engaged, default to PTO motors to spinning
                      // forwards
    {
        lUFM = 0;
        rUFM = 0;
        if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_UP))
        {
            lUFM = 127;
            rUFM = 127;
        }
        else if (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN))
        {
            lUFM = -127;
            rUFM = -127;
        }
    }
}