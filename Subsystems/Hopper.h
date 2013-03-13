#ifndef HOPPER_H
#define HOPPER_H

#include "Commands/Subsystem.h"

class Hopper : Subsystem
{
public:
	Hopper();
	~Hopper();
	
	void InitDefaultCommand();
	
private:
	// We don't know what's going on the hopper just yet.
};

#endif
