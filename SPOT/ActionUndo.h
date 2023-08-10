#pragma once
#include "Actions/Action.h"
//Class responsible for undoing action
class ActionUndo : public Action
{
public:
	ActionUndo(Registrar*);
	bool virtual Execute();
	virtual ~ActionUndo();
};