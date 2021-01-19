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
	list<Course*> DummyYearCourses[SEM_CNT];
	Course* pCRS;
	CourseStatus coursestatus;


public:

	AcademicYear();
	virtual ~AcademicYear();
	void PlanCourses();
	bool AddCourse(Course*, SEMESTER);
	bool AddCourse(Course*, int x, int y);
	bool setCourseStatus(Course_Code coursecode, CourseStatus status);
	bool setSemsterStatus(int sem, CourseStatus status);
	bool setYearStatus(CourseStatus status);
	void SaveAcadYear(int year, string filename);
	void DrawInfo(GUI* pGUI, int x, int y);
	void DrawYear(GUI* pGUI, int i) const;
	Course* select(int x, int y) const;
	void Highlight(int x, int y) const;
	bool DeleteCourse(Course*, int x, int y);
	bool DeleteYear();
	void getSemCrd(int SemCourses[]);
	bool isCourse(Course_Code coursecose);
	SEMESTER getSemester(int x, int y);
	bool AddSemester(int x, int y);
	bool SemOriginal();
	bool AddType(string type);
	//ValidityCheck check;
	Course* getCourse(Course_Code code);
	void virtual DrawMe(GUI*) const;

	bool CreditsCheck(int SemCredits);
	bool SummerCredits(int credits);
	void SetPreIssue(string course);
	void SetCoIssue(string course);
	int getTotalcredits();
	int getTotalUnivCredits();
	int getTotalMajorCredits();
	int getTotalTrackCredits();
	int getTotalConcentrationCredits();
	int getTotalMinorCredits();
	list<Course*> AllCourses;
	//helmy added
	bool FallCredits();
	bool SpringCredits();
	bool SummerCredits();
	
};