#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionDoubleConcenteration : public Action
{
	Action* RequiredAction = nullptr;
public:
	ActionDoubleConcenteration(Registrar*);
	bool virtual Execute();
	virtual ~ActionDoubleConcenteration();
};