#pragma once

#include <memory>

#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"

#define LEFT_DRIVE_MOTOR1_PORT 1
#define LEFT_DRIVE_MOTOR2_PORT 2
#define LEFT_DRIVE_MOTOR3_PORT 3
#define LEFT_DRIVE_MOTOR4_PORT 4

#define RIGHT_DRIVE_MOTOR1_PORT 11
#define RIGHT_DRIVE_MOTOR2_PORT 12
#define RIGHT_DRIVE_MOTOR3_PORT 13
#define RIGHT_DRIVE_MOTOR4_PORT 14

#define DRIVE_GEARSET okapi::AbstractMotor::gearset::blue   // blue motor RPM (600)
#define DRIVE_TPR okapi::imev5BlueTPR    // gear ticks per rotation in a blue motor cartridge
#define DRIVE_GEARMOTOR 36.0  // gear tooth count on the axle attached to the motor
#define DRIVE_GEARWHEEL 36.0  // gear tooth count on the axle attached to the wheel

#define CHASSIS_TRACK 12_in
#define CHASSIS_WHEELS 3.25_in

extern std::shared_ptr<okapi::Controller> controller;
extern std::shared_ptr<okapi::ChassisController> chassis;
extern okapi::MotorGroup left_drive_motors;
extern okapi::MotorGroup right_drive_motors;