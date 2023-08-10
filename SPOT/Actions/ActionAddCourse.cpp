#include "ActionAddCourse.h"
#include "..\Registrar.h"
#include "../Courses/UnivCourse.h"

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
	Rules RegRules = pReg->getRules();
	while (!check)
	{
		pGUI->PrintMsg("Add Course to plan: Enter course Code(e.g. CIE202):");
		string coursecode = pGUI->GetSrting();
		//capitalizing course code letters
		for (int i = 0; i < coursecode.length(); i++)
		{
			coursecode[i] = toupper(coursecode[i]);
		}
		//searching for it in the course catalouge
		for (auto it = RegRules.CourseCatalog.begin(); it != RegRules.CourseCatalog.end(); it++)
		{
				
			if ((*it)->Code == coursecode) //course found in course catalouge
			{
				code = (*it)->Code;
				Title = (*it)->Title;
				crd = (*it)->Credits;
				
				Course* pC = new Course(code, Title, crd);
				if (pReg->getStudyPlay()->CheckRepeatance(pC) == true)
					//Check whether the course is already entered before or not 
				{
					//concentration indecation
					if (pReg->getConcentbool() == 1)
					{
						if (pReg->getdoubleConcint() == -1)
						{
							for (int i = 0; i < RegRules.NumOfConcent; i++)
							{
								for (auto comb = RegRules.ConcRequirements[i].CompulsoryCourses.begin(); comb != RegRules.ConcRequirements[i].CompulsoryCourses.end(); comb++)
								{
									if (coursecode == (*comb))
									{
										pReg->setdoubleConcint(i);
										RegRules.TotalCredits += RegRules.ConcRequirements[i].comp_credits;
										RegRules.TotalCredits += RegRules.ConcRequirements[i].elective_credits;
										break;
									}
								}
								if (pReg->getdoubleConcint() == -1)
								{
									for (auto elective = RegRules.ConcRequirements[i].ElectiveCourses.begin(); elective != RegRules.ConcRequirements[i].ElectiveCourses.end(); elective++)
									{
										if (coursecode == (*elective))
										{
											pReg->setdoubleConcint(i);
											RegRules.TotalCredits += RegRules.ConcRequirements[i].comp_credits;
											RegRules.TotalCredits += RegRules.ConcRequirements[i].elective_credits;
											break;
										}
									}
								}
							}
						}
					}
					pC->setCoReqC((*it)->CoReqC);
					pC->setPreReqC((*it)->PreReqC);
					pC->setCoReq((*it)->CoReqList);
					pC->setPreReq((*it)->PreReqList);
					pReg->checkType(pC); //new
					check = true;
					ActionData actData = pGUI->GetUserAction("Select a year to add coures to");

					int x, y;
					if (actData.actType == DRAW_AREA)	//user clicked inside drawing area
					{
						//get coord where user clicked
						x = actData.x;
						y = actData.y;
						graphicsInfo gInfo{ x, y };
						StudyPlan* pS = pReg->getStudyPlay();
						int year = pS->getYear(x, y);
						SEMESTER sem = pS->getSemester(x, y);
						if (pS->AddCourse(pC, x, y) == true)
						{

							// This is a offering_time validation check for the course
							for (int i = 0; i < RegRules.OffringsList[0].Offerings[sem].size(); i++)
							{
								if (code == RegRules.OffringsList[0].Offerings[sem][i])
								{
									// set the course as valid
									pC->SetOfferingsValid(true);
									if (pReg->getMinorbool())
									{
										RegRules.MinorCompulsory.push_back(coursecode);		// Adding the course to the minor compulsory courses vector
										RegRules.TotalCredits += pC->getCredits();		// Adding the minor course crd to hte total
									}
									pReg->getStudyPlay()->setStatus((year + 10), FALL, pC->getCode(), Done);		// Setting course status as done (default value)
									break;
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
