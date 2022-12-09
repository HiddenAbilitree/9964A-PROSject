# Team 9964A Description

## Program
```cpp
std::shared_ptr<okapi::OdomChassisController> chassis = okapi::ChassisControllerBuilder()
		.withMotors(
			left_drive_motors,					// left motors
			right_drive_motors					// right motors
		)
		.withDimensions(
			DRIVE_GEARSET,						// drive gearset stored in robot.h
			{	
				{
					CHASSIS_WHEELS,				// wheel size stored in robot.h
					CHASSIS_TRACK				// drivetrain track size (length between wheels on same axis) stored in robot.h
				}, 
				DRIVE_TPR						// drivetrain ticks per rotation stored in robot.h
			}
		)
		.withOdometry()	
		.buildOdometry();
```
## Project layout

    mkdocs.yml    # The configuration file.
    docs/
        index.md  # The documentation homepage.
        ...       # Other markdown pages, images and other files.

    We decided to use PROS and the supporting library, OkapiLib due to various reasons. While researching about important aspects of a robot, one key feature that was common in most high-level teams was the implementaion of Odometry. This is the practice where rotation encoders are utilized to calculate the actual movement of the robot. When researching how to implement Odometry, we came across PROS, specifically OkapiLib. We found that this was one of the easiest ways to implement odometry that could be customized for uses in many different scenarios. Another feature was the ease of implementation of a PID controller, something that is desperately needed to effectively calibrate our robot's aged motors. Another key feature that led to the decision was the reinstatement of certain C++ features that were removed in the implementation of VEXcode.
