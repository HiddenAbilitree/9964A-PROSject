#include "pros/adi.h"
#include "pros/misc.h"
#include "robot.hpp"

// toggles the extension piston
void extension() {
    jerry.set_value(!extensionActivated);
    extensionActivated = !extensionActivated;
}

// uses a boolean input to toggle extension
void extension(bool input) {
    if (input) {
        extension();
    }
}

// function to move the drivetrain based on controller input
void update_drivetrain() {
    prosLDM = prosController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    prosRDM = prosController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
}

// function to actuate the roller mech uses up and down arrows to spin the
// roller mech
void roll_roller() {
    rM = 100 * (prosController.get_digital(pros::E_CONTROLLER_DIGITAL_L1) -
                prosController.get_digital(pros::E_CONTROLLER_DIGITAL_L2));
}

// spins the roller a certain distance
void spinRoller(double desiredAngle) {
    move(4_in);
    rMotor.moveRelative(ROLLER_RATIO * desiredAngle, 600);
    move(-1_in);
}

// moves the robot a certain distance.
void move(okapi::QLength distance) { chassis->moveDistance(distance); }
