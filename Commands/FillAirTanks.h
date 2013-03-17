#ifndef FILLAIRTANKS_H
#define FILLAIRTANKS_H

#include "../CommandBase.h"
#include "Relay.h"
#include "DigitalInput.h"

/*
 * This command handles turning the compressor on and off 
 * depending on whether or not the air tanks are full.
 */

class FillAirTanks : public CommandBase 
{
public:
	FillAirTanks();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	Relay *Compressor;
	DigitalInput *Pressure_SW;
};

#endif
