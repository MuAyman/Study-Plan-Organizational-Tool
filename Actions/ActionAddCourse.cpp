#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"
#include <string>
#include <iostream>


ActionAddCourse::ActionAddCourse(Registrar* p) :Action(p)
{
}

bool ActionAddCourse::Execute()
{
	GUI* pGUI = pReg->getGUI();
	bool check = false;
	Course_Code code;
	string Title = "Test101";
	int crd = 0;

	while (!check)
	{
		pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202): ");
		Course_Code coursecode = pGUI->GetSrting();
		for (int i = 0; i < coursecode.length(); i++)
			coursecode[i] = toupper(coursecode[i]);

		for (auto it = pReg->RegRules.CourseCatalog.begin(); it != pReg->RegRules.CourseCatalog.end(); it++)
		{
			if (it->Code == coursecode) //course found in course catalouge
			{
				code = it->Code;
				Title = it->Title;
				crd = it->Credits;
				Course* pC = new Course(code, Title, crd);
				if (pReg->getStudyPlan()->CheckRepeatance(pC) == true)
					//Check whether the course is already entered before or not
				{
					pC->setCoReq(it->CoReqList);
					pC->setPreReq(it->PreReqList);
					pReg->checkType(pC); //new
					check = true;
					ActionData actData = pGUI->GetUserAction("Select a year to add coures to");
					//TODO: add input validation
					int x, y;
					if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
					{
						//get coord where user clicked
						x = actData.x;
						y = actData.y;

						graphicsInfo gInfo{ x, y };
						StudyPlan* pS = pReg->getStudyPlan();
						Rules pR = pReg->RegRules;
						int year = pS->getYear(x, y);
						SEMESTER sem = pS->getSemester(x, y);
						if (pS->AddCourse(pC, x, y) == true)
						{

							// This is a offering_time validation check for the course
							for (int i = 0; i < pR.OffringsList[0].Offerings[sem].size(); i++)
							{
								if (pC->getCode() == pR.OffringsList[0].Offerings[sem][i])
								{
									// set the course as valid
									pC->SetOfferingsValid(true);
									if (pReg->RegRules.Minor)
									{
										pReg->RegRules.MinorCompulsory.push_back(coursecode);		// Adding the course to the minor compulsory courses vector
										pReg->RegRules.TotalCredits += pC->getCredits();		// Adding the minor course crd to hte total
									}
									pReg->getStudyPlan()->setStatus((year+10), FALL , pC->getCode(), Done);		// Setting course status as done (default value)
								}
								else
								{
									//set the course as in valid
									pC->SetOfferingsValid(false);
								}
							}
						}
						else
						{
							return false;
						}
					}
				}

				break;
			}
		}
	}
	return true;
}

ActionAddCourse::~ActionAddCourse()
{
}
