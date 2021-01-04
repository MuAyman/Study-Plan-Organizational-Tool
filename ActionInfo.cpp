#include "ActionInfo.h"
ActionInfo::ActionInfo(Registrar* p, int newx, int newy) : Action(p)
{
	x = newx;
	y = newy;
}
bool ActionInfo::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlay();
	pS->DrawInfo(pGUI, x, y);
	pS->Highlight(x, y);
	return true;
}
ActionInfo::~ActionInfo()
{

}