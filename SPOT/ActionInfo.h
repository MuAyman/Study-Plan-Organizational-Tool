#pragma once
#include "Actions/Action.h"
#include "registrar.h"
class ActionInfo : public Action
{
protected:
	int x;
	int y;

public:
	ActionInfo(Registrar* p, int x, int y);
	bool virtual Execute();
	~ActionInfo();
};