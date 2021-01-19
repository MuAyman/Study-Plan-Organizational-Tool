#include "AcademicYear.h"
#include "../GUI/GUI.h"
#include <iostream>

AcademicYear::AcademicYear()
{
	pCRS = nullptr;
	//TODO: make all necessary initializations
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
void AcademicYear::SetPreIssue(string course,bool state)
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			if (course  == (*it)->getCode())
			{
				 (*it) ->SetPreIssue(state);
			}
		}
	}
}
void AcademicYear::SetCoIssue(string course, bool state)
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			if (course == (*it)->getCode())
			{
				(*it)->SetCoIssue(state);
			}
		}
	}
}
void AcademicYear::DrawLiveMessage(GUI* pGUI, string str) const
{
	pGUI->DrawLiveMessage(str);
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
		//TotalUnivCredits
		if (pC->getType() == "UnivCompulsory" || pC->getType() == "UnivElective")
			TotalUnivCredits += pC->getCredits();
		//TotalTrackCredits
		else if (pC->getType() == "TrackCompulsory" || pC->getType() == "TrackElective")
			TotalTrackCredits += pC->getCredits();
		//TotalMajorCredits
		else if (pC->getType() == "MajorCompulsory" || pC->getType() == "MajorElective")
			TotalMajorCredits += pC->getCredits();
		//not filled yet
		//TotalMinoredits
		else if (pC->getType() == "Minor")
			TotalMinorCredits += pC->getCredits();
		//TotalConcentrationCredits
		else if (pC->getType() == "Concentration")
			TotalConcentrationCredits += pC->getCredits();


		return true;
	}

}

bool AcademicYear::setYearStatus(CourseStatus status)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		for (int x = 0; x < SEM_CNT; x++)
			setSemsterStatus(x, status);
		return true;
	}
	else
		return false;
}


bool AcademicYear::setSemsterStatus(int sem, CourseStatus status)
{

	if (status == Done || status == InProgress || status == Pending)
	{
		for (auto i : YearCourses[sem])
			setCourseStatus(i->getCode(), status);
		return true;
	}
	else
		return false;
}

bool AcademicYear::setCourseStatus(Course_Code coursecode, CourseStatus status)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		for (int sem = 0; sem < 3; sem++)
			for (auto i : YearCourses[sem])
				if (i->getCode() == coursecode)
					i->setCourseStatus(status);
		 return true;
	}
	else
		return false;
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

void AcademicYear::getSemCrd(int SemCourses[])
{
	SemCourses[0] = FALLCredits;
	SemCourses[1] = SPRINGCredits;
	SemCourses[2] = SUMMERCredits;
}

bool AcademicYear::isCourse(Course_Code coursecose)
{
	for (int y = 0; y < YearCourses->size(); y++)
		for (auto i = YearCourses[y].begin(); i != YearCourses[y].end(); i++)
			if (coursecose == (*i)->getCode())
				return true;
			else
				return false;
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
void AcademicYear::DrawConnectLine(GUI* pGUI) const
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			(*it)->DrawConnectLine(pGUI);
		}
	}
}
bool AcademicYear::AddSemester(int x, int y)
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		DummyYearCourses[sem] = YearCourses[sem];
	}
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		YearCourses[sem].clear();
	}
	int sem = getSemester(x, y);
	YearCourses[sem] = DummyYearCourses[sem];
	return true;
}
//bool AcademicYear::AddType(string type)
//{
//	for (int sem = FALL; sem < SEM_CNT; sem++)
//	{
//		DummyYearCourses[sem] = YearCourses[sem];
//	}
//	//cleaaaaaaaaaaaaar YearCourses
//	for (int sem = FALL; sem < SEM_CNT; sem++)
//	{
//		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
//		{
//			if ((*it)->getType() == type)
//				YearCourses[sem].push_back(*it);
//		}
//	}
//}
bool AcademicYear::SemOriginal()
{
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		YearCourses[sem]= DummyYearCourses[sem];
	}
	return true;
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
bool AcademicYear::CreditsCheck(int SemCredits, SEMESTER sem)
{
	if (sem == SUMMER) //semester is summer
	{
		if (SemCredits > 6) //credits in summer is greater than max
		{
			SummerGreater = 1;
			return false;
		}
		else //credits in summer is valid
		{
			SummerGreater = 0;
			return true;
		}
	}
	else //semester is fall or spring
	{
		if (SemCredits > 21) //credits is greater than max
		{
			if (sem == FALL) //fall is greater than max
			{
				FallGreater = 1;
				return false;
			}
			else // spring is greater than max
			{
				SpringGreater = 1;
				return false;
			}
		}
		else if (SemCredits < 12) //credits is less than min
		{
			if (sem == FALL) //fall is less than min
			{
				FallGreater = 0;
				return false;
			}
			else //spring is less than min
			{
				SpringGreater = 0;
				return false;
			}

		}
		else //no semester violation
			return true;
	}

}
void AcademicYear::PlanCourses()
{
	AllCourses.clear();
	for (int sem = FALL; sem < SEM_CNT; sem++)
	{
		for (auto it = YearCourses[sem].begin(); it != YearCourses[sem].end(); ++it)
		{
			AllCourses.push_back(*it);
		}
	}
}
bool AcademicYear::FallCredits()
{
	if (!CreditsCheck(FALLCredits,FALL))
	{
		return false;
	}
	return true;
}
bool AcademicYear::SpringCredits()
{
	if (!CreditsCheck(SPRINGCredits,SPRING))
	{
		return false;
	}
	return true;
}
bool AcademicYear::SummerCredits()
{

	if (!CreditsCheck(SUMMERCredits, SUMMER))
	{
		return false;
	}
	return true;
}
int AcademicYear::getTotalcredits()
{

	return TotalCredits;
}
int AcademicYear::getTotalUnivCredits()
{
	return TotalUnivCredits;
}
int AcademicYear::getTotalMajorCredits()
{
	return TotalMajorCredits;
}
int AcademicYear::getTotalTrackCredits()
{
	return TotalTrackCredits;
}
int AcademicYear::getTotalConcentrationCredits()
{
	return TotalConcentrationCredits;
}
int AcademicYear::getTotalMinorCredits()
{
	return TotalMinorCredits;
}

///////////////////helper functions in update status
bool AcademicYear::setYearStatus(CourseStatus status)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		for (int x = 0; x < SEM_CNT; x++)
			setSemsterStatus(x, status);
		return true;
	}
	else
		return false;
}


bool AcademicYear::setSemsterStatus(int sem, CourseStatus status)
{

	if (status == Done || status == InProgress || status == Pending)
	{
		for (auto i : YearCourses[sem])
			setCourseStatus(i->getCode(), status);
		return true;
	}
	else
		return false;
}


bool AcademicYear::setCourseStatus(Course_Code coursecode, CourseStatus status)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		for (int sem = 0; sem < 3; sem++)
			for (auto i : YearCourses[sem])
				if (i->getCode() == coursecode)
					i->setCourseStatus(status);
		return true;
	}
	else
		return false;
}

void AcademicYear::getSemCrd(int SemCourses[])
{
	SemCourses[0] = FALLCredits;
	SemCourses[1] = SPRINGCredits;
	SemCourses[2] = SUMMERCredits;
}

bool AcademicYear::isCourse(Course_Code coursecose)
{
	for (int y = 0; y < YearCourses->size(); y++)
		for (auto i = YearCourses[y].begin(); i != YearCourses[y].end(); i++)
			if (coursecose == (*i)->getCode())
				return true;
			else
				return false;
}
AcademicYear::~AcademicYear()
{
}
