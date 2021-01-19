#pragma once
#include "Actions/Action.h"
#include "Registrar.h"
#include <string>

class ActionStudentLevel :  public Action
{
	int NoOfCrd;
	string level;

public:
	string showstatus();
	ActionStudentLevel(Registrar* p);
	bool virtual Execute();
	virtual ~ActionStudentLevel();

};

