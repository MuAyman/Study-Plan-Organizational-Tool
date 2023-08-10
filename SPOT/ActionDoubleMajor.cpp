#include "ActionDoubleMajor.h"
#include "Registrar.h"
#include <iostream>

ActionDoubleMajor::ActionDoubleMajor(Registrar* p) :Action(p)
{

}
bool ActionDoubleMajor::Execute()
{
	GUI* pGUI = pReg->getGUI();
	pReg->ExecuteDoubleMajor();
	//====================
	pReg->setdoubleMajor(true);
	pGUI->PrintMsg("Now You can add the courses of double majors! Ok?..Enter Ok");
	string x = pGUI->GetSrting();
	return true;
}
ActionDoubleMajor::~ActionDoubleMajor()
{

}