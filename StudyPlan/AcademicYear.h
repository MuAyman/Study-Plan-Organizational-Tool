#pragma once
#include <list>

#include "..\Courses\Course.h"
#include "../GUI/Drawable.h"
//#include"F:\ZC\2\C++\GitHub\SPOT\ValidityCheck.h"
//Represent one year in the student's study plan
class AcademicYear :public Drawable
{
	int TotalCredits = 0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits = 0, TotalMajorCredits = 0,
		TotalTrackCredits = 0, TotalConcentrationCredits = 0,
		TotalMinorCredits = 0, SUMMERCredits = 0, SPRINGCredits = 0, FALLCredits = 0;

	//Each year is an array of 3 lists of courses. Each list cossrsponds to a semester
	//So YearCourses[FALL] is the list of FALL course in that year
	//So YearCourses[SPRING] is the list of SPRING course in that year
	//So YearCourses[SUMMER] is the list of SUMMER course in that year
	list<Course*> YearCourses[SEM_CNT];
	Course* pCRS;

public:
	AcademicYear();
	virtual ~AcademicYear();
	bool AddCourse(Course*, SEMESTER);
	bool AddCourse(Course*, int x, int y);
	void SaveAcadYear(int year, string filename);
	void DrawInfo(GUI* pGUI, int x, int y);
	void DrawYear(GUI* pGUI, int i) const;
	Course* select(int x, int y) const;
	void Highlight(int x, int y) const;
	bool DeleteCourse(Course*, int x, int y);
	//double CalculateGPA();
	bool DeleteYear();
	SEMESTER getSemester(int x, int y);
	//ValidityCheck checkk;
	Course* getCourse(Course_Code code);
	void virtual DrawMe(GUI*) const;
};