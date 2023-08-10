#include "ActionAddMinor.h"
#include "Registrar.h"
#include "Actions/ActionAddCourse.h"


ActionAddMinor::ActionAddMinor(Registrar* p) : Action(p)
{
};

bool ActionAddMinor::Execute()
{
	GUI* pGUI = pReg->getGUI();

	pGUI->PrintMsg("Do you want to add minor courses (5 courses)? y/n ");
	string minor1 = pGUI->GetSrting();
	if (minor1 == "y")
	{
		Rules RegRules = pReg->getRules();
		pReg->setMinorbool(true);
		RequiredAction = new ActionAddCourse(pReg);
		for (int x = 0; x < 5; x++)
			pReg->ExecuteAction(RequiredAction);						//drawing the minor course
		pReg->setMinorbool(false);
	}
	return true;
}


ActionAddMinor::~ActionAddMinor()
{
	delete RequiredAction;
}