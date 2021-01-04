
#include "ActionExit.h"
#include "Registrar.h"
#include <fstream>

#include <iostream>
ActionExit::ActionExit(Registrar* p) :Action(p)
{
}

bool ActionExit::Execute()
{
	GUI* pGUI = pReg->getGUI();

	exit(0);

	return true;
}


ActionExit::~ActionExit()
{
}
