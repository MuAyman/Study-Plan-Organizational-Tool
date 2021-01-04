#pragma once
#include "Actions/Action.h"
//Class responsible for adding note action
class ActionAddNotes :
	public Action
{
public:
	ActionAddNotes(Registrar*);
	bool virtual Execute();
	virtual ~ActionAddNotes();
};



