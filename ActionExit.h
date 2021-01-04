#pragma once
#include "Actions/Action.h"
//Class responsible for adding note action
class ActionExit :
	public Action
{
public:
	ActionExit(Registrar*);
	bool virtual Execute();
	virtual ~ActionExit();
};
