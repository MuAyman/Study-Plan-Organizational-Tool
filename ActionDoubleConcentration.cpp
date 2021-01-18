#include "ActionDoubleConcentration.h"
#include "Registrar.h"

ActionDoubleConcentration::ActionDoubleConcentration(Registrar* p): Action(p)
{

}
bool ActionDoubleConcentration::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pReg->ExecuteDoubleConcentrations();
	return true;
}
ActionDoubleConcentration::~ActionDoubleConcentration()
{

}