#include "pros/adi.h"
#include "pros/misc.h"
#include "robot.hpp"

// toggles the extension piston
void extension() {
    jerry.set_value(!extended);
    extended = !extended;
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
}

// moves the robot a certain distance.
void move(okapi::QLength distance) { chassis->moveDistance(distance); }
/*
 Sets the state of the miscellaneous motors.
 1: Intaking
 2: Winding Back
 3: Idle
*/
void intake(int state) {
    switch (state) {
    case 1:
        rM = 127;
        lM = 127;
        break;
    case 2:
        rM = -127;
        lM = -127;
        break;
    case 3:
        rM = 0;
        lM = 0;
        break;
    }
}
/*
 Sets the state of the miscellaneous motors.
 1: Intaking
 2: Winding Back
 3: Idle
*/
void intake(int state, bool input) {
    if (input) {
        intake(state);
    }
}
void windBack() {
    if (!locked && !limitSwitch.get_value()) {
        intake(2);
    }
    if (limitSwitch.get_new_press()) {
        lock.set_value(true);
        locked = true;
    }
}
void shoot() {
    if (locked) {
        lock.set_value(false);
        locked = false;
        miscMotors.move_relative(3918.85714286, 200);
        pros::delay(2000);
        windBack();
    } else {
        windBack();
    }
}
void shoot(bool input) {
    if (input) {
        shoot();
    }
}