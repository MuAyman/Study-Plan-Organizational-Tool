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
string Course::getType() const
{
	return type;
}
void Course::DrawMe(GUI* pG) const
{
	pG->DrawCourse(this);
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

void Course::setCoReq(vector<Course_Code> Cor)
{
	{
		for (auto it = Cor.begin(); it != Cor.end(); it++)
		{
			CoReq.push_back(*it);
		}
	}

}
list<Course_Code> Course::getPreReq()
{
	return PreReq;
}

list<Course_Code> Course::getCoreReq()
{
	return CoReq;
}

Course::~Course()
{
}




bool Course::IsOfferingsValid() const
{
	return OffValid;
}
bool Course::SetOfferingsValid(bool valid)
{
	OffValid = valid;
	return true;
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
void Course::DrawInfo(GUI* pG) const
{
	pG->DrawCourseInfo(this);
}
