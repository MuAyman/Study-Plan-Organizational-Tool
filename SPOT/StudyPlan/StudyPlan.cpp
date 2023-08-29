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
//adds a course to the study plan in certain year, semester
//year idetifies year number to add course to 1=first, 2 = 2nd,....
bool StudyPlan::AddCourse(Course* pC, int year, SEMESTER sem)
{
	//TODO: add all requried checks to add the course 
	plan[year - 1]->AddCourse(pC, sem);

	return true;
}

//adds a course to the study plan in certain year, semester
//Certain x and Y is declared and use another functions to know year and semester
bool StudyPlan::AddCourse(Course* pC, int x, int y)
{
	int year = getYear(x, y);
	if (year == 0)
	{
		return false;
	}
	//recuired checks is added in actions
	plan[year - 1]->AddCourse(pC, x, y);

	return true;
}

//function to delete existing course by loabing into the plan using the x & y of the course
bool StudyPlan::DeleteCourse(Course* pC, int x, int y)
{
	int year = getYear(x, y);
	plan[year - 1]->DeleteCourse(pC, x, y);

	return true;
}

/////////////////////////////Functions help in Display filter/////////////////////////////
//Put the courses of the plan into a dummy one that isn't displayed and leave the plan of the years 
//that  and y specify to filter display
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

//Put the courses of the specific semester of each year into a dummy one to help in action display semester
bool StudyPlan::AddSemester(int x, int y)
{
	
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->AddSemester(x,y);
	}
	return true;
}

// Function to help diplay filter major
//bool StudyPlan::AddType(string type)
//{
//	for (int i = 0; i < plan.size(); i++)
//	{
//		DummyPaln[i] = plan[i];
//	}
//	plan.clear();
//	for (int i = 0; i < DummyPaln.size(); i++)
//	{
//		//plan[i]->AddCourse(type);
//	}
//}

//Return every thing as it was after add Year 
bool StudyPlan::original()
{
	for (int i = 0; i < DummyPaln.size(); i++)
	{
		plan[i] = DummyPaln[i];
	}
	return true;
}

//return every thing as it was after add semester
bool StudyPlan::SemOriginal()
{
	for (int i = 0; i < DummyPaln.size(); i++)
	{
		plan[i] ->SemOriginal();
	}
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


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

///////////////////////////////////////////////////////////////////////////////////////////////////
/// ///////////////////functions help in the check validity end error wanings////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

//function to help in the live message and the Course drawn 
void StudyPlan::SetPreCoIssue()
{
	//pre & co validity addition
	for (auto j = 0; j < CoursePreString.size(); j++)
	{
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->SetPreIssue(CoursePreString[j],Pre[j]);  // set the course list pre requisite true or false
		}
	}
	for (auto j = 0; j < CourseCoString.size(); j++)
	{
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->SetCoIssue(CourseCoString[j],Co[j]); // set the co requisite list true or fase 
		}
	}

}

void StudyPlan::WarningReport()
{
	remove("WarningReport.txt");
	fstream Warnings;
	Warnings.open("WarningReport.txt", ios::app);
	//check the total credits
	if (Total_credits_Check == 0)
	{
		Warnings << "Critical Issue: \n";
		Warnings << "Error in Total credits\n"; 
	}
	//university
	if (unversity_credits_Check == 0)
	{
		Warnings << "Critical Issue: \n";
		Warnings << "Error in unversity credits\n";
		Warnings << "The problem in Courses :\n";
		if (!UnivMissedCourses.empty())
		{
			for (int i = 0; i < UnivMissedCourses.size(); i++)
			{
				Warnings << UnivMissedCourses[i] << ",";
			}
			Warnings << endl;
		}
	}
	//Major
	if (Major_credits_Check == 0)
	{
		Warnings << "Critical Issue: \n";
		Warnings << "Error in major credits\n";
		Warnings << "The problem in Courses :\n";
		if (!MajorMissedCourses.empty())
		{
			for (int i = 0; i < MajorMissedCourses.size(); i++)
			{
				Warnings << MajorMissedCourses[i] << ",";
			}
			Warnings << endl;
		}
	}
	//Track 
	if (Track_credits_Check == 0)
	{
		Warnings << "Critical Issue: \n";
		Warnings << "Error in track credits\n";
		Warnings << "The problem in Courses :\n";
		if (!TrackMissedCourses.empty())
		{
			for (int i = 0; i < TrackMissedCourses.size(); i++)
			{
				Warnings << TrackMissedCourses[i] << ",";
			}
			Warnings << endl;
		}
	}
	//Course Pre requisite check 
	if (!CoursePreString.empty())
	{
		Warnings << "Critical Issue: \n";
		int j = 0;
		for (auto i = 0; i < CoursePreString.size(); i++)
		{
			if (Pre[i] == 0)
			{
				Warnings << "Course: " << CoursePreString[i] << " can not be taken without its correquisite " << CoursePreStringh[j]  << ".\n";
				j++;
			}
		}
	}
	//course co requisite check 
	if (!CourseCoString.empty())
	{
		Warnings << "Critical Issue: \n";
		int j = 0;
		for (auto i = 0; i < CourseCoString.size(); i++)
		{
			if (Co[i] == 0)
			{
				Warnings << "Course: " << CourseCoString[i] << " can not be taken without its correquisite " << CourseCoStringh[j] << "\n";
				j++;
			}
		}

	}
	//check upload and under load
	if (OverUnderLoad_Check == 0)
	{
		/*if (== 1)
		{
			Warnings << "Over load \n"
		}
		else
		{
			Warnings << "under load \n"
		}*/
	}
	//Check the credits per semester
	for (int i = 0; i < plan.size(); i++)
	{
		//Fall
		if (plan[i]->FallCredits() == false)
		{
			Warnings << "Moderate Issue: \n";
			if (plan[i]->FallGreater == 1)
			{
				Warnings << "Credits of Fall semester in year " << i + 1 << " is greater than max \n";
			}
			else
			{
				Warnings << "Credits of Fall semester in year " << i + 1 << " is less than min \n";
			}
		}

		//Spring
		if (plan[i]->SpringCredits() == false)
		{
			Warnings << "Moderate Issue: \n";
			if (plan[i]->SpringGreater == 1)
			{
				Warnings << "Credits of Spring semester in year " << i + 1 << " is greater than max \n";
			}
			else
			{
				Warnings << "Credits of Spring semester in year " << i + 1 << " is less than min \n";
			}
		}

		if (plan[i]->SummerCredits() == false)
		{
			Warnings << "Moderate Issue: \n";
			if (plan[i]->SummerGreater == 1)
			{
				Warnings << "Credits of Summer semester in year " << i + 1 << " is greater than max \n";
			}
			else
			{
				Warnings << "Credits of Summer semester in year " << i + 1 << " is less than min \n";
			}
		}

	}
	
	//check offerings for each course
	for (auto i = 0; i < plan.size(); i++)
	{
		//loop to all the study plan to get the courses with offerings invalid
		for (auto j = plan[i]->AllCourses.begin(); j != plan[i]->AllCourses.end(); j++)
		{
			if ((*j)->IsOfferingsValid() == false)
			{
				Warnings << "Moderate Issue: \n";
				Warnings << "Offering Problem in the Course: " << (*j)->getCode() << "\n";
				Warnings << "Ask the registrar to add the course to solve the problem\n";
			}

		}
	}
	
}

//This function is used to know the missed courses in some vectors from the study plan
void StudyPlan::CheckList(vector<Course_Code> val, string type)
{
	bool found = false;
	for (auto code = val.begin(); code != val.end(); code++)
	{
		found == false;
		for (int i = 0; i < plan.size(); i++)
		{
			plan[i]->PlanCourses();
			for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
			{
				if ((*it)->getCode() == *code)
				{
					found = true;
					break;
				}
			}
			if (found == true)
				break;
		}
		//course is not found in the study plan
		if (found == false)
		{
			if (type == "University Compulsory" || type == "University Elective")
				UnivMissedCourses.push_back(*code);
			else if (type == "Major Compulsory" || type == "Major Elective")
				MajorMissedCourses.push_back(*code);
			else if (type == "Track Compulsory")
				TrackMissedCourses.push_back(*code);
		}
	}

}

//program requirements data filling
bool StudyPlan::check()
{
	ResetIntegers();
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->PlanCourses(); //filling AllCourses list
		TotalCredits += plan[i]->getTotalcredits();
		TotalUnivCredits += plan[i]->getTotalUnivCredits();
		TotalMajorCredits += plan[i]->getTotalMajorCredits();
		TotalTrackCredits += plan[i]->getTotalTrackCredits();
		TotalConcentrationCredits += plan[i]->getTotalConcentrationCredits();
		TotalMinorCredits += plan[i]->getTotalMinorCredits();
	}
	//preReq, coReq courses check
	int course_year;
	SEMESTER course_sem;
	for (int i = 0; i < plan.size(); i++)
	{
		for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
		{
			course_year = i;
			course_sem = plan[i]->getSemester((*it)->getGfxInfo().x, (*it)->getGfxInfo().y);
			PreReq_CoReq(*it, course_year, course_sem);
		}
	}
	return true;
}

//course type to get its GfxInfo for year and semester decleration
bool StudyPlan::PreReq_CoReq(Course* pC, int year, SEMESTER sem)
{
	Course* prerequisite = nullptr;
	Course* corequisite = nullptr;
	//bool variables to check if the preReq, and the coReq courses are in the study plan or not
	bool preFound, coFound;
	//preReq course details
	SEMESTER preReq_sem;
	int preReq_year;
	//coReq course details
	SEMESTER coReq_sem;
	int coReq_year;
	//preReq courses check
	if (!pC->PreReq.empty())
	{
		//for (auto pre = pC->PreReq.begin(); pre != pC->PreReq.end(); pre++)
		for (auto pre = pC->PreReq.begin(); pre != pC->PreReq.end(); pre++)
		{
			preFound = false;
			//check wheteher prerequisite course is in study plan or not
			for (int i = 0; i < plan.size(); i++)
			{
				for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
				{
					if (*pre == (*it)->getCode()) //found
					{
						prerequisite = getCourse(*pre);
						preReq_sem = plan[i]->getSemester(prerequisite->getGfxInfo().x, prerequisite->getGfxInfo().y);
						preReq_year = i;
						preFound = true;
						break;
					}
				}
				if (preFound == true)
					break;
			}
			if (preFound == true)
			{
				//preRequisite course is in the study plan but not before the course
				if (preReq_year > year || (preReq_year == year && preReq_sem > sem))
				{
					Pre.push_back(0);
					CoursePreString.push_back(pC->getCode());
					CoursePreStringh.push_back(*pre);
				}
				else
				{
					Pre.push_back(1); // no error
					CoursePreString.push_back(pC->getCode());
				}
			//	delete prerequisite;
			}
			else //preRequisite is not in the study plan
			{
				Pre.push_back(0); //0 for prerequisite error
				CoursePreString.push_back(pC->getCode());
				CoursePreStringh.push_back(*pre);
			}
		}
	}
	if (!pC->CoReq.empty())
	{
		//coReq courses check
		for (auto cor = pC->CoReq.begin(); cor != pC->CoReq.end(); cor++)
		{
			coFound = false;
			//check wheteher corequisite course is in study plan or not
			for (int i = 0; i < plan.size(); i++)
			{
				for (auto it = plan[i]->AllCourses.begin(); it != plan[i]->AllCourses.end(); it++)
				{
					if (*cor == (*it)->getCode()) //found
					{
						corequisite = getCourse(*cor);
						coReq_sem = plan[i]->getSemester(corequisite->getGfxInfo().x, corequisite->getGfxInfo().y);
						coReq_year = i;
						coFound = true;
						break;
					}
				}
				if (coFound == true)
					break;
			}
			if (coFound == true)
			{
				//corequisite course is in the study plan but not with the course
				if (coReq_year != year || coReq_sem != sem)
				{
					Co.push_back(0);
					CourseCoString.push_back(pC->getCode());
					CourseCoStringh.push_back(*cor);
				}
				else
				{
					Co.push_back(1); // no error
					CourseCoString.push_back(pC->getCode());
				}
				//delete corequisite;
			}
			else   //corequisite is not found in the study plan
			{
				Co.push_back(0); //1 for corequisite error
				CourseCoString.push_back(pC->getCode());
				CourseCoStringh.push_back(*cor);
			}
		}
	}
	
	return true;
}

//to check if the course is already added before or not
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

//make all the integres equal 0 to start again
void StudyPlan::ResetIntegers()
{
	TotalCredits = 0;
	TotalUnivCredits = 0;
	TotalMajorCredits = 0;
	TotalTrackCredits = 0;
	TotalConcentrationCredits = 0;
	TotalMinorCredits = 0;
}

/////////////////////////////////////geters and seters to help in the checks//////////
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

////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////Draw functions/////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void StudyPlan::DrawMe(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawMe(pGUI);
		plan[i]->DrawYear(pGUI, i);

	}
}
void StudyPlan::DrawConnectLine(GUI* pGUI) const
{
	//Plan draws all year inside it.
	for (int i = 0; i < plan.size(); i++)
	{
		plan[i]->DrawConnectLine(pGUI);
	}
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
void StudyPlan::DrawLiveMessage(GUI* pGUI) const
{
	for (int i = 0; i < plan.size(); i++)
	{
		if (plan[i]->FallCredits() == false || plan[i]->SpringCredits() == false || plan[i]->SummerCredits() == false)
			plan[i]->DrawLiveMessage(pGUI, "Moderate");

		if (!CoursePreString.empty() || !CourseCoString.empty())
		{
			plan[i]->DrawLiveMessage(pGUI, "Critical");
		}
		if (Total_credits_Check == 0 || unversity_credits_Check == 0 || Major_credits_Check == 0 || Track_credits_Check == 0 || Concentratioin_Check == 0)
			plan[i]->DrawLiveMessage(pGUI, "Critical");
		
		for (auto j = plan[i]->AllCourses.begin(); j != plan[i]->AllCourses.end(); j++)
		{
			if ((*j)->IsOfferingsValid() == false)
			{
				plan[i]->DrawLiveMessage(pGUI, "Moderate");
			}

		}
	}
}


///////////////////////////////functions to return course///////////////////////////////

//get year credits 
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
//function to return course using its x and y
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

//function to return a course using its cours code
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
	return NULL;
}

//function return all courses in the plan
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
/////////////////////////////////helper functions in the dimensions to avoid repeatance////////////
//return the year using the x and y of the click and it is helpful while entering in valid dimensions
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

//return the semester using the x and y of the click and it is helpful while entering invalid dimensions
SEMESTER StudyPlan::getSemester(int x, int y)
{
	int year = getYear(x, y);
	SEMESTER sem = plan[year - 1]->getSemester(x, y);
	return sem;
}
/////////////////////////////helper functions in update status //////////////
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
StudyPlan::~StudyPlan()
{
}