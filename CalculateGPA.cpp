//#include "CalculateGPA.h"
//#include "Registrar.h"
//#include "Courses/UnivCourse.h"
//#include <iostream>
//
//CalculateGPA::CalculateGPA(Registrar* p) :Action(p)
//{
//
//}
//
//bool CalculateGPA::Execute()
//{
//	GUI* pGUI = pReg->getGUI();
//	ActionData actData = pGUI->GetUserAction("Click on the course you want to add the grada to...");
//	int x, y;
//	x = actData.x;
//	y = actData.y;
//	StudyPlan* pS = pReg->getStudyPlan();
//	pGUI->PrintMsg("Add the letter grade: ");
//	CourseGradeLetter gradeLetter = pGUI->GetSrting();
//	//Course* pC = new Course();
//	//Course* CRS = pS->select(x, y);
//	//pS->Add2GPA(CRS);
//	return true;
//}
//
//CalculateGPA::~CalculateGPA()
//{
//
//}