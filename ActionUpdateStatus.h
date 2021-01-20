#pragma once
#include "Actions/Action.h"
#include "Registrar.h"

class ActionUpdateStatus : public Action
{


public:
	ActionUpdateStatus(Registrar* p);
	bool virtual Execute();
	virtual ~ActionUpdateStatus();

};