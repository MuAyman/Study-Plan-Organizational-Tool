#pragma once
#include "Actions/Action.h"
class ActionCheckReport : public  Action
{
public:
	ActionCheckReport(Registrar*);
	bool virtual Execute();
	virtual ~ActionCheckReport();
};


