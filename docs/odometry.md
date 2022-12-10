<!-- @format -->

# Odometry

## Program

### robot.h

```cpp
#pragma once    // prevents the file from being included multiple times

#include <memory>

#include "main.h"
#include "okapi/api/device/motor/abstractMotor.hpp"

// stores motor port values
#define LEFT_DRIVE_MOTOR1_PORT 1
#define LEFT_DRIVE_MOTOR2_PORT 2
#define LEFT_DRIVE_MOTOR3_PORT 3
#define LEFT_DRIVE_MOTOR4_PORT 4

#define RIGHT_DRIVE_MOTOR1_PORT 11
#define RIGHT_DRIVE_MOTOR2_PORT 12
#define RIGHT_DRIVE_MOTOR3_PORT 13
#define RIGHT_DRIVE_MOTOR4_PORT 14

// stores the gearing of the drivetrain
#define DRIVE_GEARSET okapi::AbstractMotor::gearset::blue
#define DRIVE_TPR okapi::imev5RedTPR

// stores the dimensions of the drivetrain
#define CHASSIS_TRACK 12_in
#define CHASSIS_WHEELS 3.25_in
```

### main.cpp

```cpp
std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
        .withMotors(
            left_drive_motors,      // left motors
            right_drive_motors      // right motors
        )
        .withDimensions(
            DRIVE_GEARSET,          // drive gearset stored in robot.h
            {
                {
                    CHASSIS_WHEELS, // wheel size stored in robot.h
                    CHASSIS_TRACK   // drivetrain track size (length between wheels on same axis) stored in robot.h
                },
            DRIVE_TPR               // drivetrain ticks per rotation stored in robot.h
            }
        )
        .withOdometry()
        .buildOdometry();
```
