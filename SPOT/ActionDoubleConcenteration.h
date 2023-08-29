#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
class ActionDoubleConcenteration : public Action
{

public:
	ActionDoubleConcenteration(Registrar*);
	bool virtual Execute();
	virtual ~ActionDoubleConcenteration();
};