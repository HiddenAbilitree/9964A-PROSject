
#include "functions.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include "robot.hpp"

// defining the controller
pros::Controller prosController(pros::E_CONTROLLER_MASTER);

// initialize pneumatic pistons
pros::ADIDigitalOut jerry(EXTENSION_DIGITAL_SENSOR_PORT);

// initialize limit switch for catapult windback

// defining the PTO motors
pros::Motor rM(ROLLER_MOTOR_PORT, PROS_DRIVE_GEARSET, 1, PROS_DRIVE_MEASURE);

// defining the rest of the motors
pros::Motor lUBM(LEFT_DRIVE_MOTOR3_PORT, PROS_DRIVE_GEARSET, 0,
                 PROS_DRIVE_MEASURE);
pros::Motor rUBM(RIGHT_DRIVE_MOTOR3_PORT, PROS_DRIVE_GEARSET, 1,
                 PROS_DRIVE_MEASURE);
pros::Motor lLFM(LEFT_DRIVE_MOTOR1_PORT, PROS_DRIVE_GEARSET, 0,
                 PROS_DRIVE_MEASURE);
pros::Motor rLFM(RIGHT_DRIVE_MOTOR1_PORT, PROS_DRIVE_GEARSET, 1,
                 PROS_DRIVE_MEASURE);
pros::Motor lLBM(LEFT_DRIVE_MOTOR2_PORT, PROS_DRIVE_GEARSET, 0,
                 PROS_DRIVE_MEASURE);
pros::Motor rLBM(RIGHT_DRIVE_MOTOR2_PORT, PROS_DRIVE_GEARSET, 1,
                 PROS_DRIVE_MEASURE);

// defining the drivetrain motors
pros::Motor_Group prosLDM({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT,
                           LEFT_DRIVE_MOTOR3_PORT});
pros::Motor_Group prosRDM({RIGHT_DRIVE_MOTOR1_PORT, RIGHT_DRIVE_MOTOR2_PORT,
                           RIGHT_DRIVE_MOTOR3_PORT});
// motors not included: LEFT_DRIVE_MOTOR3_PORT, RIGHT_DRIVE_MOTOR3_PORT

// defining the drivetrain motors for odometry
// PTO motors are omitted for simplicity
okapi::MotorGroup okapiLDM({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT,
                            LEFT_DRIVE_MOTOR3_PORT});
okapi::MotorGroup okapiRDM({RIGHT_DRIVE_MOTOR1_PORT, RIGHT_DRIVE_MOTOR2_PORT,
                            RIGHT_DRIVE_MOTOR3_PORT});

okapi::Motor rMotor(ROLLER_MOTOR_PORT, true,
                    okapi::AbstractMotor::gearset::green, OKAPI_DRIVE_MEASURE);

std::shared_ptr<okapi::OdomChassisController> chassis =
    okapi::ChassisControllerBuilder()
        .withMotors(okapiLDM, // left motors
                    okapiRDM  // right motors
                    )
        .withDimensions(
            {
                OKAPI_DRIVE_GEARSET, // drive gearset stored in robot.h
                (DRIVE_GEARWHEEL / DRIVE_GEARMOTOR) // drivetrain gearing
            },
            {
                {
                    CHASSIS_WHEELS, // wheel size stored in robot.h
                    CHASSIS_TRACK   // drivetrain track size (length between
                                    // wheels on same axis) stored in robot.h
                },
                OKAPI_DRIVE_TPR // drivetrain ticks per rotation stored in
                                // robot.h
            })
        .withOdometry()
        .buildOdometry();

/*
std::shared_ptr<okapi::ChassisController> driveController =
    okapi::ChassisControllerBuilder()
        .withMotors(okapiLDM, // left motors
                    okapiRDM  // right motors
                    )
        .withDimensions(
            {
                OKAPI_DRIVE_GEARSET, // drive gearset stored in robot.h
                (DRIVE_GEARWHEEL / DRIVE_GEARMOTOR) // drivetrain gearing
            },
            {
                {
                    CHASSIS_WHEELS, // wheel size stored in robot.h
                    CHASSIS_TRACK   // drivetrain track size (length between
                                    // wheels on same axis) stored in robot.h
                },
                OKAPI_DRIVE_TPR // drivetrain ticks per rotation stored in
                                // robot.h
            })
        .withOdometry()
        .buildOdometry();

std::shared_ptr<okapi::AsyncPositionController<double, double>> cataController =
    okapi::AsyncPosControllerBuilder()
        .withMotor({lMotor, rMotor})
        .withGains({0.001, 0.0001, 0.0001})
        .build();*/

bool extensionActivated = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // creates buttons on the cortex lcd display
  // pros::lcd::initialize();
  prosRDM.set_reversed(true);
  prosLDM.set_gearing(PROS_DRIVE_GEARSET);
  prosRDM.set_gearing(PROS_DRIVE_GEARSET);
  okapiRDM.setReversed(true);
  okapiLDM.setReversed(true);
  jerry.set_value(extensionActivated);
  autonomous();
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

void spinRoller() {
  rMotor.moveVoltage(12000);
  pros::delay(1000);
  rMotor.moveVelocity(0);
}

void move(okapi::QLength distance) { chassis->moveDistance(-distance); }
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
void autonomous() {

  //
  //    angles are considered similar to a graph (0 degrees means facing
  //    "right")
  //
  //    positive direction is towards the roller mech side.
  //

  // setting the default values for the odometry
  chassis->setState({0_in, 0_in, 0_deg});
  // halving movement speed
  chassis->setMaxVelocity(300);
  // moving first roller
  spinRoller();
  // reversing
  move(-24_in);
  // turning to second roller
  chassis->turnAngle(90_deg);
  // moving to second roller
  move(24_in);
  // moving second roller
  spinRoller();
  // turning to other two rollers
  chassis->turnAngle(135_deg);
  // moving to other two rollers
  move(96_in);
  // turning to third roller
  chassis->turnAngle(-45_deg);
  // moving to third roller
  move(24_in);
  // moving third roller
  spinRoller();
  // reversing
  move(-24_in);
  // turning to fourth roller
  chassis->turnAngle(90_deg);
  // moving to fourth roller
  move(24_in);
  // moving fourth roller
  spinRoller();
  // reversing
  move(-12_in);
  // turning to aim extension
  chassis->turnAngle(45_deg);
  // launching extension
  extension();
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

  // main while loop
  while (true) {
    // sets the speed of the drivetrain motors according to the controller
    // joystick positions ranges -127 to 127
    update_drivetrain();
    // extension
    extension(
        prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A));
    // roller mech
    roll_roller();
    pros::delay(20);
  }
}
