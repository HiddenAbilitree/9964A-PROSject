#include "main.h"
#include "okapi/api/chassis/controller/chassisControllerIntegrated.hpp"
#include "okapi/api/chassis/controller/odomChassisController.hpp"
#include "okapi/api/chassis/model/chassisModel.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include "okapi/api/units/QLength.hpp"
#include "okapi/api/units/RQuantity.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/api/util/mathUtil.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "robot.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // creates buttons on the cortex lcd display
  pros::lcd::initialize();
  
  pros::Controller master(pros::E_CONTROLLER_MASTER);
   // initializing motors
  pros::Motor lLFM(LEFT_DRIVE_MOTOR1_PORT , pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor lLBM(LEFT_DRIVE_MOTOR2_PORT , pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor lUFM(LEFT_DRIVE_MOTOR3_PORT , pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor lUBM(LEFT_DRIVE_MOTOR4_PORT , pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor rLFM(RIGHT_DRIVE_MOTOR1_PORT, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor rLBM(RIGHT_DRIVE_MOTOR2_PORT, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor rUFM(RIGHT_DRIVE_MOTOR3_PORT, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor rUBM(RIGHT_DRIVE_MOTOR4_PORT, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_DEGREES);

  // grouping motors into groups for readability
  pros::Motor_Group leftMotors({lUFM, lUBM, lLFM, lLBM});
  pros::Motor_Group rightMotors({rUFM, rUBM, rLFM, rLBM});

  // group 6 main drive motors into groups
  pros::Motor_Group driveLeftMotors({lLFM, lUBM, lLBM});
  pros::Motor_Group driveRightMotors({rLFM, rUBM, rLBM});
  // initialize pneumatic pistons
  pros::ADIDigitalOut leftPiston(LEFT_DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut rightPiston(RIGHT_DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut catapultLock(CATAPULT_DIGITAL_SENSOR_PORT);
  pros::ADIDigitalOut jerry(EXTENSION_DIGITAL_SENSOR_PORT);
  // initialize pullback limit sensor
  pros::ADIDigitalIn pulledBack(PULLLIMIT_DIGITAL_SENSOR_PORT);



 

  okapi::MotorGroup left_drive_motors({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT, LEFT_DRIVE_MOTOR3_PORT, LEFT_DRIVE_MOTOR4_PORT});
  okapi::MotorGroup right_drive_motors({RIGHT_DRIVE_MOTOR1_PORT, RIGHT_DRIVE_MOTOR2_PORT, RIGHT_DRIVE_MOTOR3_PORT, RIGHT_DRIVE_MOTOR4_PORT});

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

void pullback()
{

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {

  // initalizing controller

  right_drive_motors.setReversed(true);
  left_drive_motors.setGearing(DRIVE_GEARSET);
  right_drive_motors.setGearing(DRIVE_GEARSET);
  // creating the chassis using okapilib ChassisController
  std::shared_ptr<okapi::OdomChassisController> chassis =
      okapi::ChassisControllerBuilder()
          .withMotors(left_drive_motors, // left motors
                      right_drive_motors // right motors
                      )
          .withDimensions(
              DRIVE_GEARSET, // drive gearset stored in robot.h
              {
                  {
                      CHASSIS_WHEELS, // wheel size stored in robot.h
                      CHASSIS_TRACK   // drivetrain track size (length between
                                      // wheels on same axis) stored in robot.h
                  },
                  DRIVE_TPR // drivetrain ticks per rotation stored in robot.h
              })
          .withOdometry()
          .buildOdometry();

  // resets the state of the robot
  // chassis->setState({0_in, 0_in, 0_deg});

  // moves the robot 1 foot forward to the right
  // orientation should be 45 degrees.
  // chassis->driveToPoint({12_in,0_in});
  // chassis->turnAngle(90_deg);
  // chassis->driveToPoint({12_in,6_in});
  // chassis->turnAngle(0_deg);

  // main while loop
  bool ptoActivated = false;

  while (true) {
    // stores controller analog stick positions into an int variable
    // ranges -127 to 127
    int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    // sets motor movement equal to the controller analog input
    driveLeftMotors = left;   // all left side motors aside from PTO motors
    driveRightMotors = right; // all right side motors aside from PTO motors

    // PTO motor control
    if (!ptoActivated) // when PTO not engaged, treat PTO motors as drivetrain
    {
      lUFM = left;
      rUFM = right;
    } else // when PTO engaged, default to PTO motors to spinning forwards
           // (intake on)
    {
      lUFM = 127;
      rUFM = 127;
      if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
        catapultLock.set_value(false); // release the catapult to shoot
        pros::delay(250);
        while (!pulledBack.get_value()) {
          lUFM = -127;
          rUFM = -127;
        }
        lUFM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        rUFM.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		lUFM.brake();
		rUFM.brake();
		catapultLock.set_value(true);
		pros::delay(250);
		lUFM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
		rUFM.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
      }
    }
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      rightPiston.set_value(!ptoActivated);
      leftPiston.set_value(!ptoActivated);
      ptoActivated = !ptoActivated;
    }
    // final delay
    pros::delay(2);
  }
}
