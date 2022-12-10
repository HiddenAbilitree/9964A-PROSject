<!-- @format -->

# Odometry

## Program

=== "Variables"

    ``` cpp title="robot.h"

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
    #define DRIVE_GEARSET okapi::AbstractMotor::gearset::blue  // blue motor RPM (600)
    #define DRIVE_TPR okapi::imev5BlueTPR  // gear ticks per rotation in a blue motor cartridge

    // stores the dimensions of the drivetrain
    #define CHASSIS_TRACK 12_in  // distance between the inside edge of wheels on the same axle
    #define CHASSIS_WHEELS 3.25_in  // diameter of drivetrain wheels
    ```
    <br/>

    !!! abstract inline end "Note"
        
        Variables are stored here primarily for readability purposes.
    This file contains the variable definitions used in the odomChassisController constructor
    


=== "main.cpp"

    ``` cpp

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
    #include "pros/misc.h"
    #include "pros/motors.h"
    #include "robot.h"


    // uses variable definitions defined in robot.h
    okapi::MotorGroup left_drive_motors({
		LEFT_DRIVE_MOTOR1_PORT,	    	
		LEFT_DRIVE_MOTOR2_PORT,
        LEFT_DRIVE_MOTOR3_PORT,
        LEFT_DRIVE_MOTOR4_PORT});
	okapi::MotorGroup right_drive_motors({
		RIGHT_DRIVE_MOTOR1_PORT,
		RIGHT_DRIVE_MOTOR2_PORT,
        RIGHT_DRIVE_MOTOR3_PORT,
        RIGHT_DRIVE_MOTOR4_PORT});
    
    // uses variable definitions defined in robot.h
    std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
            .withMotors(
                left_drive_motors,      // left motor ports
                right_drive_motors      // right motor ports
            )
            .withDimensions(
                DRIVE_GEARSET,          // drive gearset
                {
                    {
                        CHASSIS_WHEELS, // wheel size
                        CHASSIS_TRACK   // drivetrain track size (length between wheels on same axis)
                    }, 
                DRIVE_TPR               // drivetrain ticks per rotation
                }
            )
            .withOdometry()
            .buildOdometry();
    ```
=== "User Control"

    ``` cpp

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
    #include "pros/misc.h"
    #include "pros/motors.h"
    #include "robot.h"

    pros::Controller master(pros::E_CONTROLLER_MASTER);
	
	// initializing motors
	pros::Motor lUFM(1,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lUBM(2,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lLFM(3,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor lLBM(4,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rUFM(11,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rUBM(12,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rLFM(13,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor rLBM(14,pros::E_MOTOR_GEAR_GREEN,0,pros::E_MOTOR_ENCODER_DEGREES);
	
	// grouping motors into groups for readability
	pros::Motor_Group leftMotors({lUFM,lUBM,lLFM,lLBM});
	pros::Motor_Group rightMotors({rUFM,rUBM,rLFM,rLBM});
    ```

