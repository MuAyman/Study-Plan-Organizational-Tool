#include "ActionFilter.h"

#include "Registrar.h"
ActionFilter::ActionFilter(Registrar* p) : Action(p)
{

}
bool ActionFilter::Execute()
{
	GUI* pGUI = pReg->getGUI();
	ActionData actData = pGUI->GetUserAction("Click on the item you want to display filter with");
	int x, y;
	x = actData.x;
	y = actData.y;
	StudyPlan* pS = pReg->getStudyPlay();
	//Course* CRs = pS->select(x, y);
	/*if (CRs != NULL)
	{
		CRs->getType();

	}
	else 
	{*/
		//display year
		/*pS->AddYear(x, y);
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->original();*/
		
		//display semester
		pS->AddSemester(x, y);
		pReg->UpdateInterface();
		ActionData actData1 = pGUI->GetUserAction("Click again to end the display filter");
		pS->SemOriginal();



	//	pS->AddSemester(x, y);
	/*}
	pS->AddYear(x, y);
	ActionData actData1 = pGUI->GetUserAction("Click on any place to cancel the display");
	pS->original();*/
	return true;
}
ActionFilter::~ActionFilter()
{

}
