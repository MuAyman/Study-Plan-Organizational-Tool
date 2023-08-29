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
	
	bool OffValid = true;
	bool PreIssue = true;
	bool CoIssue = true;
public:
	CourseStatus status;
	list<Course_Code> PreReq;	//list of prerequisites
	list<Course*> PreReqC;	//list of prerequisites
	list<Course_Code> CoReq;	//list of Corequisites
	list<Course*> CoReqC;	//list of Corequisites
	Course(Course_Code r_code,string r_title, int crd);
	Course(Course_Code r_code, string r_title, int crd, string Type); // Added to make the programer able to set the type
	void setType(string t);
	string getTitle() const;
	string getCode() const;
	int getCredits() const;
	string getType() const;
	void setGradePoints();
	void setQp();
	void setGradeLetter(CourseGradeLetter x);
	void DrawMe(GUI*) const;
	void DrawConnectLine(GUI* pG) const;
	void DrawInfo(GUI* pG) const;
	bool select(int x, int y);
	bool IsOfferingsValid() const;
	bool IsPreValid() const;
	bool IsCoValid() const;
	void SetOfferingsValid(bool valid);
	void SetPreIssue(bool state);
	void SetCoIssue(bool state);
	bool ModerateIssue() const;
	bool CriticalIssue() const;
	void setCoReqC(vector<Course*> Cor);
	void setPreReqC(vector<Course*> Cor);
	void setPreReq(vector<Course_Code> Pre);
	void setCoReq(vector<Course_Code> Cor);
	double getQP();
	bool setCourseStatus(CourseStatus status);
	virtual ~Course();




































































};
