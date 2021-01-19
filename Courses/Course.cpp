#include "Course.h"
#include "../GUI/GUI.h"
#include <iostream>

Course::Course(Course_Code r_code, string r_title, int crd):code(r_code),Title(r_title)
{
	credits = crd;
}
Course::Course(Course_Code r_code, string r_title, int crd, string Type) : code(r_code), Title(r_title)
{
	credits = crd;
	type = Type;
}

bool Course::setCourseStatus(CourseStatus newstatus)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		status = newstatus;
		return true;
	}
	else
		return false;
}


string Course::getType()const
{
	return type;
}
void Course::setType(string t)
{
	type = t;
}

Course_Code Course::getCode() const
{
	return code;
}

string Course::getTitle() const
{
	return Title;
}

//return course credits
int Course::getCredits() const
{
	return credits;
}

void Course::setGradeLetter(CourseGradeLetter letter)
{
	gradeLetter = letter;
}

void Course::setGradePoints()
{
	if (gradeLetter == "A")
		gradePoints = 4;
	if (gradeLetter == "A-")
		gradePoints = 3.67;
	if (gradeLetter == "B+")
		gradePoints = 3.33;
	if (gradeLetter == "B")
		gradePoints = 3;
	if (gradeLetter == "B-")
		gradePoints = 2.67;
	if (gradeLetter == "C+")
		gradePoints = 2.33;
	if (gradeLetter == "C")
		gradePoints = 2;
	if (gradeLetter == "C-")
		gradePoints = 1.67;
	if (gradeLetter == "F")
		gradePoints = 0;
}

void Course::setQp()
{
	QP = credits * gradePoints;
}

void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
}
void Course::DrawConnectLine(GUI* pG) const
{
	pG->DrawConnectLine(this);
}
bool Course::select(int x, int  y) 
{

	if (x >= this->getGfxInfo().x && x <= this->getGfxInfo().x + CRS_WIDTH && y >= this->getGfxInfo().y && y <= this->getGfxInfo().y + CRS_HEIGHT)
	{
		return true;
	}
	else 
	{
		return false;
	}
}


void Course::setPreReq(vector<Course_Code> Pre)
{
	for (auto it = Pre.begin(); it != Pre.end(); it++)
	{
		PreReq.push_back(*it);
	}
}
void Course::setPreReqC(vector<Course*> Pre)
{
	for (auto it = Pre.begin(); it != Pre.end(); it++)
	{
		PreReqC.push_back(*it);
	}
}

void Course::setCoReq(vector<Course_Code> Cor)
{
	{
		for (auto it = Cor.begin(); it != Cor.end(); it++)
		{
			CoReq.push_back(*it);
		}
	}

}
void Course::setCoReqC(vector<Course*> Cor)
{
	{
		for (auto it = Cor.begin(); it != Cor.end(); it++)
		{
			//cout << (*it)->getGfxInfo().x;
			CoReqC.push_back((*it));
		}
	}

}
//list<Course_Code> Course::getPreReq()
//{
//	return PreReq;
//}
//
//list<Course_Code> Course::getCoreReq()
//{
//	return CoReq;
//}

Course::~Course()
{
}




bool Course::IsOfferingsValid() const
{
	return OffValid;
}
bool Course::IsPreValid() const
{
	return PreIssue;
}
bool Course::IsCoValid() const
{
	return CoIssue;
}
void Course::SetOfferingsValid(bool valid)
{
	OffValid = valid;
}
void Course::SetPreIssue(bool state)
{
	PreIssue = state;
}
void Course::SetCoIssue(bool state)
{
	CoIssue = state;
}
bool Course::ModerateIssue() const// Moderate Issues Total
{
	if (this->IsOfferingsValid())
	{
		return true;
	}
	return false;
}
bool Course::CriticalIssue()  const// Critical Issue total 
{
	// check the statments;
	return true;
}
double Course::getQP()
{
	return QP;
}
//helper function in update status
bool Course::setCourseStatus(CourseStatus newstatus)
{
	if (status == Done || status == InProgress || status == Pending)
	{
		status = newstatus;
		return true;
	}
	else
		return false;
}
void Course::DrawInfo(GUI* pG) const
{
	pG->DrawCourseInfo(this);
}
