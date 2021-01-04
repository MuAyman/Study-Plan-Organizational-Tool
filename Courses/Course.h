#pragma once
#include <string>
#include <list>
#include <vector>
using namespace std;
#include "..\DEFs.h"

#include "../GUI/Drawable.h"

//Base class for all types of courses
class Course : public Drawable
{
	const Course_Code code;	//course code: e.g. "CIE202". This is the course ID
	CourseGradeLetter gradeLetter;
	double gradePoints;
	double QP;
	const string Title;		//course title: e.g. "Fundamentals of Computer Programming"
	int credits;	//no. of course credits
	string type;	//Univ, track, or major.....etc.
	bool Done;		//Done or not yet?
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course_Code> CoReq;	//list of prerequisites
	bool OffValid;
public:
	Course(Course_Code r_code,string r_title, int crd);
	Course(Course_Code r_code, string r_title, int crd, string Type); // Added to make the programer able to set the type
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	string getType() const;
	void setGradePoints();
	void setQp();
	void setGradeLetter(CourseGradeLetter x);
	void DrawMe(GUI*) const;
	void DrawInfo(GUI* pG) const;
	bool select(int x, int y);
	bool IsOfferingsValid() const;
	bool SetOfferingsValid(bool valid);
	bool ModerateIssue() const;
	bool CriticalIssue() const;

	void setPreReq(vector<Course_Code> Pre);
	void setCoReq(vector<Course_Code> Cor);
	list<Course_Code> getCoreReq();
	list<Course_Code> getPreReq();

	virtual ~Course();




































































};
