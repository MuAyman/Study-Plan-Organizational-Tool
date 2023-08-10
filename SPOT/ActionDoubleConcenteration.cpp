#include "ActionDoubleConcenteration.h"
#include "Registrar.h"

ActionDoubleConcenteration::ActionDoubleConcenteration(Registrar* p) : Action(p)
{

}
bool ActionDoubleConcenteration::Execute()
{
	GUI* pGUI = pReg->getGUI();
	Rules R = pReg->getRules();
	if (R.NumOfConcent == 0)
	{
		pGUI->PrintMsg("Your major don't have this option! ok?..Enter ok");
		string x = pGUI->GetSrting();
	}
	else
	{
		pGUI->PrintMsg("The first course you should add must not be repeated in other concentration! then,Ok?..Enter Ok");
		string x = pGUI->GetSrting();
		pReg->setConcentbool(true);
	}
	return true;
	////////////////////////////////////////////////////////////////////////////

}
ActionDoubleConcenteration::~ActionDoubleConcenteration()
{

}