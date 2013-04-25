#include "RobotState.h"

bool RobotState::shooter_wheels_spinning = false;
bool RobotState::load_piston_locked = false;
bool RobotState::auto_loading = false;
bool RobotState::hooksExtended = true;
bool RobotState::raised = true;

bool RobotState::target_found = false;
double RobotState::azimuth = 0.0;
double RobotState::range = 0.0;
