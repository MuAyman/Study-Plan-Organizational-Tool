#include "Drag_DropAction.h"
#include <iostream>
using namespace std;
Drag_DropAction::Drag_DropAction(Registrar* pReg, int newx, int newy) : Action(pReg)
{
	x = newx;
	y = newy;
}

bool Drag_DropAction::Execute()
{
	GUI* pGUI = pReg->getGUI();
	StudyPlan* pS = pReg->getStudyPlan();
	window* pWind = pGUI->getWindow();
	const button butt = RIGHT_BUTTON;
	buttonstate buttstate;
	int x1, y1;
	course = pS->select(x, y);
	if (course == NULL)
	{
		return false;
	}
	graphicsInfo gInfo = course->getGfxInfo();
	pReg->UpdateInterface();
	buttstate = pWind->GetButtonState(butt, x1, y1);
	while (buttstate == BUTTON_DOWN)
	{
		graphicsInfo gInfo2;
		gInfo2.x = x1;
		gInfo2.y = y1;
		course->setGfxInfo(gInfo2);
		pGUI->DrawCourse(course);
		pReg->UpdateInterface();
		buttstate = pWind->GetButtonState(butt, x1, y1);
		////////////////
		if (buttstate == BUTTON_UP)
		{
			bool isCourse = pS->AddCourse(course, x1, y1);
			if (isCourse == true)
			{
				pS->DeleteCourse(course, gInfo.x, gInfo.y);
				return true;
			}
			else
			{
				return false;
			}

		}
	}

	return false;
}
Drag_DropAction::~Drag_DropAction()
{
}