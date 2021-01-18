#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
//Class responsible for drawing links between co and pre requisite courses
class ActionLinks : public Action
{

public:
	ActionLinks(Registrar*);
	bool virtual Execute();
	virtual ~ActionLinks();
};

