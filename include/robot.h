#pragma once    // prevents the file from being included multiple times

#include <memory>  

#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"

// stores motor port values
#define LEFT_DRIVE_MOTOR1_PORT 5
#define LEFT_DRIVE_MOTOR2_PORT 6
#define LEFT_DRIVE_MOTOR3_PORT 7
#define LEFT_DRIVE_MOTOR4_PORT 8

#define RIGHT_DRIVE_MOTOR1_PORT 1
#define RIGHT_DRIVE_MOTOR2_PORT 2
#define RIGHT_DRIVE_MOTOR3_PORT 3
#define RIGHT_DRIVE_MOTOR4_PORT 4

// stores the gearing of the drivetrain
#define DRIVE_GEARSET okapi::AbstractMotor::gearset::blue  // blue motor RPM (600)
#define DRIVE_TPR okapi::imev5BlueTPR  // gear ticks per rotation in a blue motor cartridge
#define DRIVE_GEARMOTOR 36.0  // gear tooth count on the axle attached to the motor
#define DRIVE_GEARWHEEL 36.0  // gear tooth count on the axle attached to the wheel

// stores the dimensions of the drivetrain
#define CHASSIS_TRACK 14.25_in  // distance between the inside edge of wheels on the same axle
#define CHASSIS_WHEELS 2_in  // diameter of drivetrain wheels

// stores ports of the pistons used for the pto mech
#define LEFT_DIGITAL_SENSOR_PORT 'A'
#define RIGHT_DIGITAL_SENSOR_PORT 'B'

// stores port of the piston used for catapult
#define CATAPULT_DIGITAL_SENSOR_PORT 'C'

// stores port of the piston used for extension
#define EXTENSION_DIGITAL_SENSOR_PORT 'D'

// stores port of the pullback limit switch
#define PULLLIMIT_DIGITAL_SENSOR_PORT 'E'

// okapilib object initialization
extern std::shared_ptr<okapi::Controller> controller; // okapilib controller
extern std::shared_ptr<okapi::OdomChassisController> chassis;  // okapilib odometry controller
extern okapi::MotorGroup left_drive_motors;  // drivetrain left motor group 
extern okapi::MotorGroup right_drive_motors;  // drivetrain right motor group

// pros object initialization
extern pros::Controller master;

extern pros::Motor lLFM;
extern pros::Motor lLBM;
extern pros::Motor lUFM;
extern pros::Motor lUBM;
extern pros::Motor rLFM;
extern pros::Motor rLBM;
extern pros::Motor rUFM;
extern pros::Motor rUBM;

// group 6 main drive motors into groups
extern pros::Motor_Group driveLeftMotors;
extern pros::Motor_Group driveRightMotors;
// initialize pneumatic pistons
extern pros::ADIDigitalOut leftPiston;
extern pros::ADIDigitalOut rightPiston;
extern pros::ADIDigitalOut catapultLock;
extern pros::ADIDigitalOut jerry;
// initialize pullback limit sensor
extern pros::ADIDigitalIn pulledBack;