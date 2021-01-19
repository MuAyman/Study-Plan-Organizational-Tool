#include "StudyPlan.h"
#include <iostream>
#include <fstream>

StudyPlan::StudyPlan()
{
	//By default, the study plan starts with 5 years
	//More year can be added

	for (int i = 0; i < 5; i++)
	{
		AcademicYear* newyear = new AcademicYear;
		int ix = 200;
		int iy = 520 - ((SEM_CNT * PLAN_SEMESTER_HEIGHT) + 10) * i;
		graphicsInfo gInfo{ ix ,iy };
		newyear->setGfxInfo(gInfo);
		plan.push_back(newyear);
		DummyPaln.push_back(newyear);
	}

}


bool StudyPlan::setStatus(int year, SEMESTER sem, Course_Code code, CourseStatus status)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		if (year == 5)		// seting the whole plan to status
		{
			for (int i = 0; i < plan.size(); i++)
				plan[i]->setYearStatus(status);
			return true;
		}
		else if (year < 5)		// setting that year to status
		{
			plan[year]->setYearStatus(status);
			return true;
		}
		else if (year > 20)		// setting that sem to status
		{
			plan[year - 20]->setSemsterStatus(sem, status);
			return true;
		}
		else if (year > 9)		// setting that course to status
		{
			plan[year - 10]->setCourseStatus(code, status);
			return true;
		}
	}
	else
		return false;
}


//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course
	plan[year - 1]->AddCourse(pC, sem);

	return true;
}
bool StudyPlan::AddCourse(Course* pC, int x, int y)
{
	int year = getYear(x, y);
	if (year == 0)
	{
		return false;
	}
	//TODO: add all requried checks to add the course
	plan[year - 1]->AddCourse(pC, x, y);

	return true;
}

bool StudyPlan::AddYear(int x, int y)
{
	for (int i = 0; i < plan.size(); i++)
	{
		DummyPaln[i] = plan[i];
	}
	int year = getYear(x, y);
	if (year == 0)
	{
		return false;
	}
	plan.clear();
	cout << plan.size() << endl;
	for (int i = 0; i < 5; i++)
	{
		AcademicYear* newyear = new AcademicYear;
		int ix = 200;
		int iy = 520 - ((SEM_CNT * PLAN_SEMESTER_HEIGHT) + 10) * i;
		graphicsInfo gInfo{ ix ,iy };
		newyear->setGfxInfo(gInfo);
		plan.push_back(newyear);


	}
	plan[year - 1] = DummyPaln[year - 1];
	cout << plan.size() << endl;
	cout << DummyPaln.size() << endl;

}

bool StudyPlan::AddSemester(int x, int y)
{

	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->AddSemester(x,y);
	}
	return true;
}

bool StudyPlan::original()
{
	for (int i = 0; i < DummyPaln.size(); i++)
	{
		plan[i] = DummyPaln[i];
	}
	return true;
}
bool StudyPlan::SemOriginal()
{
	for (int i = 0; i < DummyPaln.size(); i++)
	{
		plan[i] ->SemOriginal();
	}
	return true;
}
bool StudyPlan::DeleteImportPlan()
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DeleteYear();
	}
	return true;
}
void StudyPlan::SaveStudyPlan(string filename)
{
	ofstream StudyPlan;
	for (int i = 0; i < 5; i++)
	{
		plan[i]->SaveAcadYear(i, filename);
	}
}

void StudyPlan::SetPreCoIssue()
{
	for (auto j = 0; j < CoursePreString.size(); j++)
	{
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->SetPreIssue(CoursePreString[j]);
		}
	}
	for (auto j = 0; j < CourseCoString.size(); j++)
	{
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->SetCoIssue(CourseCoString[j]);
		}
	}

}
void StudyPlan::WarningReport()
{
	fstream Warnings;
	Warnings.open("WarningReport.txt", ios::app);

	if(Total_credits_Check == 0)
		Warnings << "Error in Total credits\n";
	if(unversity_credits_Check == 0)
		Warnings << "Error in unversity credits\n";
	if (Major_credits_Check == 0)
		Warnings << "Error in major credits\n";
	if (Track_credits_Check == 0)
		Warnings << "Error in track credits\n";
	if (!CoursePreString.empty())
	{
		for (auto i = 0; i < CoursePreString.size(); i++)
		{
			if(Pre[i] == 1)
			Warnings << "Course: " << CoursePreString[i] << " can not be taken without its correquisite " << CourseCoString[i]  << "\n";
			if(Co[i] == 1)
			Warnings << "Course: " << CourseCoString[i] << " can not be taken before its Prerequisite " << CoursePreString[i] << "\n";
		}
	}
	for (int i = 0; i < plan.size(); i++)
	{
		if(plan[i]->FallCredits() == false)
			Warnings << "Credits of Fall semester in year " << i << "is greater than Max credits \n";

		if(plan[i]->SpringCredits() == false)
			Warnings << "Credits of Spring semester in year " << i << "is greater than Max credits \n";

		if(plan[i]->SummerCredits() == false)
			Warnings << "Credits of Summer semester in year " << i << "is greater than Max credits \n";

	}

}

Course* StudyPlan::getCourse(Course_Code code)
{
	for (int i = 0; i < plan.size(); i++)
	{
		for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
		{
			if (code == (*it)->getCode())
				return *it;
		}
	}
}

void StudyPlan::getYearCrd(int* semcrd[])
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->getSemCrd(semcrd[i]);
	}
}

bool StudyPlan::isCourse(Course_Code coursecode)
{
	for (int i = 0; i < plan.size(); i++)
		return plan[i]->isCourse(coursecode);
}

void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawMe(pGUI);
		plan[i]->DrawYear(pGUI, i);

	}
}
Course* StudyPlan::select(int x, int y) const
{
	for (int i = 0; i < plan.size(); i++)
	{
		Course* Crs = plan[i]->select(x, y);
		if (Crs != NULL)
		{
			return Crs;
		}
	}
	return NULL;
}

void StudyPlan::Highlight(int x, int y) const
{

	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->Highlight(x, y);
	}

}
void StudyPlan::DrawInfo(GUI* pGUI, int x, int y)
{
	int year = getYear(x, y);
	plan[year - 1]->DrawInfo(pGUI, x, y);
}
bool StudyPlan::DeleteCourse(Course* pC, int x, int y)
{
	int year = getYear(x, y);
	plan[year - 1]->DeleteCourse(pC, x, y);

	return true;
}


int StudyPlan::getYear(int x, int y)
{
	int year = 10;
	int iy = 520;
	if (y > iy && y < iy + (SEM_CNT * PLAN_SEMESTER_HEIGHT))
		year = 1;
	else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 1) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 1) + PLAN_SEMESTER_HEIGHT * SEM_CNT)
		year = 2;
	else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 2) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
		year = 3;
	else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 3) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
		year = 4;
	else if (y > (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4) && y < (iy - (3 * PLAN_SEMESTER_HEIGHT + 10) * 4) + (PLAN_SEMESTER_HEIGHT * SEM_CNT))
		year = 5;
	else
	{
		year = 0;
	}
	return year;
}
SEMESTER StudyPlan::getSemester(int x, int y)
{
	int year = getYear(x, y);
	SEMESTER sem = plan[year - 1]->getSemester(x, y);
	return sem;
}
StudyPlan::~StudyPlan()
{
}

list<Course*> StudyPlan::PlanCoursesNeeded()
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->PlanCourses();
		for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
		{
			AllCoursesNeeded.push_back(*it);
		}
	}
	return AllCoursesNeeded;
}


bool StudyPlan::PreReqError(bool valid)
{
	//Critical Issue
	return valid;
}
bool StudyPlan::CoReqError(bool valid)
{
	//Critical Issue
	return valid;
}
bool StudyPlan::PreReq_CoReq(Course* pC)
{
	int x_sem = pC->getGfxInfo().x;
	int y_sem = pC->getGfxInfo().y;
	Course* prerequisite = nullptr; //course type to get its GfxInfo
	Course* corequisite = nullptr;
	bool preFound;
	bool coFound;
	list<Course_Code> PreReq = pC->getPreReq();	//list of prerequisites
	list<Course_Code> CoReq = pC->getCoreReq();	//list of coerequisites
	for (auto pre = PreReq.begin(); pre != PreReq.end(); pre++)
	{
		preFound = false;
		delete prerequisite;
		//check wheteher prerequisite course is in study plan or not
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->PlanCourses();
			for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
			{
				if (*pre == (*it)->getCode()) //found
				{
					preFound = true;
					prerequisite = getCourse(*pre);
					if (y_sem > prerequisite->getGfxInfo().y)
					{
						//PreORCo.push_back(0);
						CourseCoString.push_back(pC->getCode());
						CoursePreString.push_back(*pre);
						cout << "Course: " << pC->getCode() << " can not be taken before its prerequisite " << *pre << endl;
						PreReqError(false);
					}
					else
						PreReqError(true);
					break;
				}

				if (preFound == true)
					break;
			}
		}
		if (preFound == false)
			PreReqError(false);
		else
			PreReqError(true);
	}

	for (auto cor = CoReq.begin(); cor != CoReq.end(); cor++)
	{
		coFound = false;
		delete corequisite;
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->PlanCourses();
			for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
			{
				if (*cor == (*it)->getCode())
				{
					coFound = true;
					corequisite = getCourse(*cor);
					if (y_sem != corequisite->getGfxInfo().y && x_sem != corequisite->getGfxInfo().x)
					{
						/*PreORCo.push_back(1);
						CoursePreString.push_back(pC->getCode());*/
						CourseCoString.push_back(*cor);

						cout << "Course: " << pC->getCode() << " can not be taken without its correquisite " << *cor << endl;
						CoReqError(false);
					}
					else
						CoReqError(true);
					break;
				}
				if (coFound == true)
					break;
			}
		}
		if (coFound == false)
			PreReqError(false);
		else
			PreReqError(true);
	}
	return true;
}

bool StudyPlan::check()
{
	ResetIntegers();
	for (int i = 0; i < plan.size(); i++)
	{
		TotalCredits += plan[i]->getTotalcredits();
		TotalUnivCredits += plan[i]->getTotalUnivCredits();
		TotalMajorCredits += plan[i]->getTotalMajorCredits();
		TotalTrackCredits += plan[i]->getTotalTrackCredits();
		TotalConcentrationCredits += plan[i]->getTotalConcentrationCredits();
		TotalMinorCredits += plan[i]->getTotalMinorCredits();
		for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
		{
			PreReq_CoReq(*it);
		}
	}

	return true;
}
int StudyPlan::getTotalcredits()
{
	return TotalCredits;
}
int StudyPlan::getTotalUnivCredits()
{
	return TotalUnivCredits;
}
int StudyPlan::getTotalMajorCredits()
{
	return TotalMajorCredits;
}
int StudyPlan::getTotalTrackCredits()
{
	return TotalTrackCredits;
}
int StudyPlan::getTotalConcentrationCredits()
{
	return TotalConcentrationCredits;
}
int StudyPlan::getTotalMinorCredits()
{
	return TotalMinorCredits;
}
void StudyPlan::Set_Total_credits_Check(bool Check)
{
	Total_credits_Check = Check;
}

void StudyPlan::Concentratioin_Check_Check(bool Check)
{
	Concentratioin_Check = Check;
}
void StudyPlan::OverUnderLoad_Check_Check(bool Check)
{
	OverUnderLoad_Check = Check;
}
void StudyPlan::OverUnderLoad_up_down_Check(bool Check)
{
	OverUnderLoad_up_Check = Check;
}


void StudyPlan::Set_unversity_credits_Check(bool Check)
{
	unversity_credits_Check = Check;
}
void StudyPlan::Set_Major_credits_Check(bool Check)
{
	Major_credits_Check = Check;
}
void StudyPlan::Set_Track_credits_Check(bool Check)
{
	Track_credits_Check = Check;
}
bool StudyPlan::CheckRepeatance(Course* pC)
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->PlanCourses();
		for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
		{

			if ((*it)->getCode() == pC->getCode())
				return false;
		}
	}
	return true;
}
void StudyPlan::ResetIntegers()
{
	TotalCredits = 0;
	TotalUnivCredits = 0;
	TotalMajorCredits = 0;
	TotalTrackCredits = 0;
	TotalConcentrationCredits = 0;
	TotalMinorCredits = 0;
}
