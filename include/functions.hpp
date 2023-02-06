#pragma once // explanation under robot.h

// functions in functions.cpp
#include "okapi/api/units/QLength.hpp"
void extension();
void extension(bool input);
void update_drivetrain();
void update_controller();
void roll_roller();
void move(okapi::QLength distance);
void spinRoller();
