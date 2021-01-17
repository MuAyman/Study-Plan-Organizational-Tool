#include "AcademicYear.h"
#include "../GUI/GUI.h"
//#include "Courses/Course.h"
#include <iostream>
//using namespace std;

AcademicYear::AcademicYear()
{
	//TODO: make all necessary initializations
}


AcademicYear::~AcademicYear()
{
}

Course* AcademicYear::getCourse(Course_Code code) //youssef
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			if (code == (*it)->getCode())
			{
				return *it;
			}
		}
	}
}



//Adds a course to this year in the spesified semester
bool AcademicYear::AddCourse(Course* pC, SEMESTER sem)
{
	YearCourses[sem].push_back(pC);
	//youssef
	if (sem == FALL)
	{
		FALLCredits += pC->getCredits();
		//checkk.CreditsCheck(FALLCredits);
		//checkk.petition(FALLCredits);
	}
	else if (sem == SPRING)
	{
		SPRINGCredits += pC->getCredits();

		//checkk.CreditsCheck(SPRINGCredits);
		//checkk.petition(SPRINGCredits);

	}
	else if (sem == SUMMER)
	{
		SUMMERCredits += pC->getCredits();
		//checkk.CreditsCheck(SUMMERCredits); //find the correct place
		//checkk.petition(SUMMERCredits);
	}
	// check
	TotalCredits += pC->getCredits();

	//TODO: acording to course type incremenet corrsponding toatl hours for that year
	return true;
}
bool AcademicYear::AddCourse(Course* pC, int x, int y)
{
	SEMESTER sem = getSemester(x, y);
	if (sem == SEM_CNT)
	{
		return false;
	}
	else
	{
		AddCourse(pC, sem);
		return true;
	}
	
}
void AcademicYear::SaveAcadYear(int year, string filename)
{
	fstream StudyPlan;
	StudyPlan.open(filename, ios::app);

	StudyPlan << "Year " << year + 1 << ",";
	StudyPlan << "Fall" << ",";
	for (auto i = YearCourses[0].begin(); i != YearCourses[0].end(); i++)
		StudyPlan << (*i)->getCode() << ",";

	StudyPlan << "\nYear " << year + 1 << ",";
	StudyPlan << "Spring" << ",";
	for (auto i = YearCourses[1].begin(); i != YearCourses[1].end(); i++)
		StudyPlan << (*i)->getCode() << ",";

	StudyPlan << "\nYear " << year + 1 << ",";
	StudyPlan << "Summer" << ",";
	for (auto i = YearCourses[2].begin(); i != YearCourses[2].end(); i++)
		StudyPlan << (*i)->getCode() << ",";

	StudyPlan << endl;
	StudyPlan.close();

}

bool AcademicYear::DeleteYear()
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		YearCourses[sem].clear();
	}
	TotalCredits = 0;
	return true;
}
void AcademicYear::DrawYear(GUI* pGUI, int i) const
{
	pGUI->DrawYearBlock(i);
}
void AcademicYear::DrawMe(GUI* pGUI) const
{
	pGUI->DrawAcademicYear(this);
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		int CRS_NUM = 0;
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			graphicsInfo gInfo = this->getGfxInfo();
			int x = gInfo.x + 50 + (CRS_WIDTH + 2.0) * CRS_NUM;
			int y = gInfo.y + 69 - (PLAN_SEMESTER_HEIGHT * sem);
			graphicsInfo newgInfo{ x, y };
			(*it)->setGfxInfo(newgInfo);
			(*it)->DrawMe(pGUI);	//call DrawMe for each course in this semester
			CRS_NUM++;
		}
	}
}
Course* AcademicYear::select(int x, int y) const
{
	//Draw all semesters inside this year by iterating on each semester list
	//to get courses and draw each course
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			if ((*it)->select(x, y))
				return (*it);
		}
	}
	return NULL;
}
void AcademicYear::Highlight(int x, int y) const
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			bool isCourse = (*it)->select(x, y);
			bool selected = (*it)->isSelected();
			if (isCourse == 1)
			{
				(*it)->setSelected(1);
			}
			else  if (isCourse == 0)
			{
				if (selected == 1)
				{
					(*it)->setSelected(0);
				}
			}
		}
	}
}
bool AcademicYear::DeleteCourse(Course* pC, int x, int y)
{
	SEMESTER sem = getSemester(x, y);
	//TODO:
	//This function still needs many checks to be compelete
	for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
	{

		if (pC == *it)
		{
			YearCourses[sem].erase(it);
			break;
		}

	}

	TotalCredits -= pC->getCredits();



	//TODO: acording to course type incremenet corrsponding toatl hours for that year


	return true;
}

//double AcademicYear::CalculateGPA(Course* pC)
//{
//
//}

// double AcademicYear::CalculateGPA()
//{
//	////SEMESTER sem = getSemester(x, y);
//	// pGUI->PrintMsg("Add the letter grade: ");
//	 GUI* pGUI;
//	 CourseGradeLetter gradeLetter;
//	 for (int i = 0; i < gradeLetter.length(); i++)
//		 gradeLetter[i] = toupper(gradeLetter[i]);
//	 for (int i = 0; i < SEM_CNT; i++)
//	 {
//		 for (auto it = YearCourses[i].begin(); it != YearCourses[i].end(); ++it)
//		 {
//			 //pGUI->PrintMsg("Add the letter grade: ");
//			 /*gradeLetter = pGUI->GetSrting();
//			 for (int i = 0; i < gradeLetter.length(); i++)
//				 gradeLetter[i] = toupper(gradeLetter[i]);*/
//			 //setGradePoints();
//			//(*it)->
//		 }
//	 }
//	
//
//	//TotalCredits -= pC->getCredits();
//	 return 1;
//}

SEMESTER AcademicYear::getSemester(int x, int y)
{

	SEMESTER sem = SEM_CNT;
	int iy = 520;
	if (/*Year1*/(y >= iy + PLAN_SEMESTER_HEIGHT * 2) && y < (iy + PLAN_SEMESTER_HEIGHT * 3) ||
		/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 3 ||
		/*Year 3*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 3 ||
		/*Year4*/(y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 3 ||
		/*Year5*/((y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 2) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 3))

	{
		sem = FALL;
	}
	else if (/*Year1*/(y >= iy + PLAN_SEMESTER_HEIGHT) && y < (iy + PLAN_SEMESTER_HEIGHT * 2) ||
		/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT * 2 ||
		/*Year 3*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 + PLAN_SEMESTER_HEIGHT * 2 ||
		/*Year4*/(y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 + PLAN_SEMESTER_HEIGHT * 2 ||
		/*Year5*/((y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 + PLAN_SEMESTER_HEIGHT * 2))
	{
		sem = SPRING;
	}
	else if ((/*Year1*/(y >= iy && y < iy + PLAN_SEMESTER_HEIGHT)) ||
		/*Year2*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) && y < iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) + PLAN_SEMESTER_HEIGHT) ||
		/*Year3*/ (y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 2) + PLAN_SEMESTER_HEIGHT) ||
		/*Year4*/(y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 3) + PLAN_SEMESTER_HEIGHT) ||
		/*Year5*/(y >= iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4 && y < (iy - (SEM_CNT * PLAN_SEMESTER_HEIGHT + 10) * 4) + PLAN_SEMESTER_HEIGHT))
	{
		sem = SUMMER;
	}
	else
		sem = SEM_CNT;
	return sem;
}
void AcademicYear::DrawInfo(GUI* pGUI, int x, int y)
{
	SEMESTER sem = getSemester(x, y);
	//	//TODO:
	//	//This function still needs many checks to be compelete
	for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
	{
		Course* course = select(x, y);
		if (course == *it)
		{
			(*it)->DrawInfo(pGUI);
		}

	}

}