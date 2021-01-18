#pragma once
#include "Actions/Action.h"


class ActionAddMinor :  public Action
{

public:
	ActionAddMinor();
	bool virtual Execute();
	virtual ~ActionAddMinor();
};

