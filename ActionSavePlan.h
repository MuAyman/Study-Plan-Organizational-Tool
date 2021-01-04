#pragma once
#include "Actions/Action.h"

class ActionSavePlan :
    public Action
{
public:
	ActionSavePlan(Registrar*);
	bool virtual Execute();
	virtual ~ActionSavePlan();

};

