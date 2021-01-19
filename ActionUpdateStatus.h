#pragma once
#include "Actions/Action.h"
#include "Registrar.h"

class ActionUpdateStatus : public Action
{
protected:
	int x;
	int y;

public:
	ActionUpdateStatus(Registrar* p, int newx, int newy);
	bool virtual Execute();
	virtual ~ActionUpdateStatus();

};
