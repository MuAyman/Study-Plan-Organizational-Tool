#include "ActionDoubleConcenteration.h"
#include "Registrar.h"

ActionDoubleConcenteration::ActionDoubleConcenteration(Registrar* p) : Action(p)
{

}
bool ActionDoubleConcenteration::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pReg->ExecuteDoubleConcentration(pGUI);
	return true;
}
ActionDoubleConcenteration::~ActionDoubleConcenteration()
{

}