#pragma once
#include <vector>
#include "AcademicYear.h"
#include "../GUI/Drawable.h"
//A full study plan for as student
class StudyPlan :public Drawable
{
	int TotalCredits = 0;		//total no. of credit hours for courses registred in this year
	int TotalUnivCredits = 0, TotalMajorCredits = 0,
		TotalTrackCredits = 0, TotalConcentrationCredits = 0,
		TotalMinorCredits = 0;

	vector<AcademicYear*> plan;	//plan is a list of academic years

public:
	StudyPlan();
	bool AddCourse(Course*, int year, SEMESTER);
	bool AddCourse(Course*, int x, int y);
	void virtual DrawMe(GUI*) const;
	Course* select(int x, int y) const;
	void Highlight(int x, int y) const;
	void SaveStudyPlan(string filename);
	bool DeleteCourse(Course*, int x, int y);
	double CalculateGPA();
	bool DeleteImportPlan();
	int getYear(int x, int y);
	SEMESTER getSemester(int x, int y);
	Course* getCourse(Course_Code code);
	void virtual DrawInfo(GUI* pGUI, int x, int y);
	virtual ~StudyPlan();
};
