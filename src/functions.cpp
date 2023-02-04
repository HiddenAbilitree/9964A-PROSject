#include "pros/adi.h"
#include "robot.hpp"

void extension() {
  if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    jerry.set_value(!extensionActivated);
    extensionActivated = !extensionActivated;
  }
}

// function to actuate drivetrain. uses 6 vs 8 motors depending on status of
// pto.
void update_drivetrain() {
  prosLDM = prosController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  prosRDM = prosController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
}

// function to actuate the roller mech. uses up and down arrows to spin the
// roller mech
void roll_roller() {
  rM = 100 * (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_UP) -
              prosController.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN));
}