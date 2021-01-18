#include "ActionLinks.h"

ActionLinks:: ActionLinks(Registrar* p) : Action(p)
{

}
bool ActionLinks::Execute()
{
	StudyPlan* pSPlan = pReg->getStudyPlay(); 
	GUI* pGUI = pReg->getGUI();
	pSPlan->DrawConnectLine(pGUI);
	return true;
}
ActionLinks:: ~ActionLinks()
{

}