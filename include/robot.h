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

#define DRIVE_GEARSET okapi::AbstractMotor::gearset::blue
#define DRIVE_TPR okapi::imev5RedTPR

#define CHASSIS_TRACK 12_in
#define CHASSIS_WHEELS 3.25_in



