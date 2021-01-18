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
	}

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

void StudyPlan::AddMinor(char* minorCourses)
{	
	
	
	int TotalCredits = 0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits = 0, TotalMajorCredits = 0,
		TotalTrackCredits = 0, TotalConcentrationCredits = 0,
		TotalMinorCredits = 0;


}


Course* StudyPlan::getCourse(Course_Code code) 
{
	for (int i = 0; i < plan.size(); i++)
	{
		return plan[i]->getCourse(code);
	}

}

void StudyPlan::getYearCrd(int* semcrd[])
{
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->getSemCrd(semcrd[i]);
	}
}

bool StudyPlan::isCourse(char* coursecode)
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
