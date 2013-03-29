#ifndef ARCADEDRIVE_H
#define ARCADEDRIVE_H

#include "../CommandBase.h"
#include "../Util/TeleopHelper.h"

/* Description */

class ArcadeDrive : public CommandBase 
{
public:
	ArcadeDrive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool is_finished;
};

#endif
