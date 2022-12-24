#pragma once // prevents the file from being included multiple times

#include <memory>

// includes all needed files
#include "functions.hpp"

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
#include "pros/rtos.hpp"

// global

// stores motor port values
// motor 3 on both sides is attached to the PTO
#define RIGHT_DRIVE_MOTOR1_PORT 11
#define RIGHT_DRIVE_MOTOR2_PORT 2
#define RIGHT_DRIVE_MOTOR3_PORT 3
#define RIGHT_DRIVE_MOTOR4_PORT 4

#define LEFT_DRIVE_MOTOR1_PORT 5
#define LEFT_DRIVE_MOTOR2_PORT 6
#define LEFT_DRIVE_MOTOR3_PORT 7
#define LEFT_DRIVE_MOTOR4_PORT 8

extern int RIGHT_DRIVE_MOTOR_PORTS[4];

// stores the gearing of the drivetrain
#define OKAPI_DRIVE_GEARSET                                                    \
  okapi::AbstractMotor::gearset::blue // blue motor RPM (600)
#define OKAPI_DRIVE_TPR                                                        \
  okapi::imev5BlueTPR // gear ticks per rotation in a blue motor cartridge
#define DRIVE_GEARMOTOR                                                        \
  36.0 // gear tooth count on the axle attached to the motor
#define DRIVE_GEARWHEEL                                                        \
  60.0 // gear tooth count on the axle attached to the wheel

// stores the dimensions of the drivetrain
#define CHASSIS_TRACK                                                          \
  14.25_in // distance between the inside edge of wheels on the same axle
#define CHASSIS_WHEELS 3.25_in // diameter of drivetrain wheels

// stores ports of the pistons used for the PTO mech
#define LEFT_DIGITAL_SENSOR_PORT 'A'
#define RIGHT_DIGITAL_SENSOR_PORT 'B'

// stores port of the piston used for catapult
#define CATAPULT_DIGITAL_SENSOR_PORT 'C'

// stores port of the piston used for extension
#define EXTENSION_DIGITAL_SENSOR_PORT 'D'

// stores port of the pullback limit switch
#define PULLLIMIT_DIGITAL_SENSOR_PORT 'E'

// okapilib
extern std::shared_ptr<okapi::Controller>
    okapiController; // okapilib controller
extern std::shared_ptr<okapi::OdomChassisController>
    chassis;                       // okapilib odometry controller
extern okapi::MotorGroup okapiLDM; // drivetrain left motor group
extern okapi::MotorGroup okapiRDM; // drivetrain right motor group

#define OKAPI_DRIVE_MEASURE okapi::AbstractMotor::encoderUnits::degrees

// pros
#define PROS_DRIVE_GEARSET pros::E_MOTOR_GEAR_BLUE // blue motor (600rpm)
#define PROS_DRIVE_MEASURE                                                     \
  pros::E_MOTOR_ENCODER_DEGREES // encoder measures in degrees

// pros object declarations

extern pros::Controller prosController; // pros contorller

// declares pto motors
extern pros::Motor lUFM; // left upper front motor
extern pros::Motor rUFM; // right upper front motor

// declares other motors
extern pros::Motor rUBM; // right upper back motor
extern pros::Motor lUBM; // left upper back motor
extern pros::Motor rLFM; // right lower front motor
extern pros::Motor lLFM; // left lower front motor
extern pros::Motor rLBM; // right lower back motor
extern pros::Motor lLBM; // left lower back motor

// declare motor groups
extern pros::Motor_Group prosLDM; // pros left drive motors
extern pros::Motor_Group prosRDM; // pros right drive motors

// declare pneumatic pistons
extern pros::ADIDigitalOut leftPiston;   // left PTO piston
extern pros::ADIDigitalOut rightPiston;  // right PTO piston
extern pros::ADIDigitalOut catapultLock; // catapult piston
extern pros::ADIDigitalOut jerry;        // extension piston

// makes ptoActivated a global variable
extern bool ptoActivated;
extern bool extensionActivated;
