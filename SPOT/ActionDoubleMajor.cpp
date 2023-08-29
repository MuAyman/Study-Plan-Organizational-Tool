#include "ActionDoubleMajor.h"
#include "Registrar.h"
#include <iostream>

ActionDoubleMajor::ActionDoubleMajor(Registrar* p) :Action(p)
{

}
bool ActionDoubleMajor::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pReg->ExecuteDoubleMajor(pGUI);
	return true;
}
ActionDoubleMajor::~ActionDoubleMajor()
{

}