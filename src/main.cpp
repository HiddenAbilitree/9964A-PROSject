#include "robot.h"

pros::Controller prosController(pros::E_CONTROLLER_MASTER);
// initializing motors


// initialize pneumatic pistons
pros::ADIDigitalOut leftPiston(LEFT_DIGITAL_SENSOR_PORT);
pros::ADIDigitalOut rightPiston(RIGHT_DIGITAL_SENSOR_PORT);
pros::ADIDigitalOut catapultLock(CATAPULT_DIGITAL_SENSOR_PORT);
pros::ADIDigitalOut jerry(EXTENSION_DIGITAL_SENSOR_PORT);

pros::Motor lUFM(LEFT_DRIVE_MOTOR3_PORT,PROS_DRIVE_GEARSET,0,PROS_DRIVE_MEASURE);
pros::Motor rUFM(RIGHT_DRIVE_MOTOR3_PORT,PROS_DRIVE_GEARSET,1,PROS_DRIVE_MEASURE);

pros::Motor_Group prosLDM({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT, LEFT_DRIVE_MOTOR3_PORT, LEFT_DRIVE_MOTOR4_PORT});
pros::Motor_Group prosRDM({RIGHT_DRIVE_MOTOR1_PORT, RIGHT_DRIVE_MOTOR2_PORT, RIGHT_DRIVE_MOTOR3_PORT, RIGHT_DRIVE_MOTOR4_PORT});

okapi::MotorGroup okapiLDM({LEFT_DRIVE_MOTOR1_PORT, LEFT_DRIVE_MOTOR2_PORT, LEFT_DRIVE_MOTOR3_PORT, LEFT_DRIVE_MOTOR4_PORT});
okapi::MotorGroup okapiRDM({RIGHT_DRIVE_MOTOR1_PORT, RIGHT_DRIVE_MOTOR2_PORT, RIGHT_DRIVE_MOTOR3_PORT, RIGHT_DRIVE_MOTOR4_PORT});

std::shared_ptr<okapi::OdomChassisController> chassis =
okapi::ChassisControllerBuilder()
  .withMotors(
    okapiLDM, // left motors
    okapiRDM // right motors
  )
  .withDimensions(
    {
      OKAPI_DRIVE_GEARSET, // drive gearset stored in robot.h
      (DRIVE_GEARMOTOR/DRIVE_GEARWHEEL)  // drivetrain gearing
    },
    {
      {
        CHASSIS_WHEELS, // wheel size stored in robot.h
        CHASSIS_TRACK   // drivetrain track size (length between
                // wheels on same axis) stored in robot.h
      },
      OKAPI_DRIVE_TPR // drivetrain ticks per rotation stored in robot.h
    })
  .withOdometry()
  .buildOdometry();



bool ptoActivated = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // creates buttons on the cortex lcd display
  pros::lcd::initialize();
  prosRDM.set_reversed(true);
  prosLDM.set_gearing(PROS_DRIVE_GEARSET);
  prosRDM.set_gearing(PROS_DRIVE_GEARSET);
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
void autonomous() {
  chassis->setState({0_in,0_in});
}

void catapultMech()
{
  if(ptoActivated)
  {
    // (intake on)
    lUFM = 127;
    rUFM = 127;
    if (prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
      catapultLock.set_value(false); // release the catapult to shoot
      pros::delay(250);
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
}

void drivetrain()
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
  // stores controller analog stick positions into an int variable
  // ranges -127 to 127
  int left = prosController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int right = prosController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  while (true) {  
    prosRDM.set_reversed(true);
    prosLDM.set_gearing(PROS_DRIVE_GEARSET);
    prosRDM.set_gearing(PROS_DRIVE_GEARSET);
    prosLDM = left;
    prosRDM = right;
    // PTO motor control
    if(ptoActivated) // when PTO engaged, default to PTO motors to spinning forwards
    {
      pros::Task task(catapultMech);
    }
    if(prosController.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      rightPiston.set_value(!ptoActivated);
      leftPiston.set_value(!ptoActivated);
      ptoActivated = !ptoActivated;
    }
    // final delay
    pros::delay(2);
  }
  // main while loop


  
}
