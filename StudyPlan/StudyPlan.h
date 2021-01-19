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
	bool Total_credits_Check = 1;
	bool unversity_credits_Check = 1;
	bool Major_credits_Check = 1;
	bool Track_credits_Check = 1;
	bool Concentratioin_Check = 1;
	bool OverUnderLoad_Check = 1;
	bool OverUnderLoad_up_Check = 1;

	vector<AcademicYear*> plan;	//plan is a list of academic years
	vector<AcademicYear*> DummyPaln;	//Dummy plan is a list of academic years
	vector<string> CourseCoString;
	vector<string> CoursePreString;
	vector<bool> Pre;
	vector<bool> Co;
	list<Course*> AllCoursesNeeded;
public:

	StudyPlan();
	list<Course*> PlanCoursesNeeded();
	bool setStatus(int year, SEMESTER sem, Course_Code code, CourseStatus status);
	bool AddCourse(Course*, int year, SEMESTER);
	bool AddCourse(Course*, int x, int y);
	bool AddYear(int x, int y);
	bool AddSemester(int x, int y);
	bool original();
	bool SemOriginal();
	void OverUnderLoad_Check_Check(bool Check);
	void OverUnderLoad_up_down_Check(bool Check);
	void Concentratioin_Check_Check(bool Check);
	void virtual DrawMe(GUI*) const;
	Course* select(int x, int y) const;
	void Highlight(int x, int y) const;
	void SaveStudyPlan(string filename);
	void WarningReport();
	bool DeleteCourse(Course*, int x, int y);
	bool isCourse(Course_Code coursecode);
	bool DeleteImportPlan();
	int getYear(int x, int y);
	void getYearCrd(int* semcrd[]);
	SEMESTER getSemester(int x, int y);
	Course* getCourse(Course_Code code);
	void virtual DrawInfo(GUI* pGUI, int x, int y);
	void SetPreCoIssue(); // helmy added
	bool StudyPlan::PreReqError(bool valid);
	bool CoReqError(bool valid);
	bool PreReq_CoReq(Course* pC);
	bool check();
	int getTotalcredits();
	int getTotalUnivCredits();
	int getTotalMajorCredits();
	int getTotalTrackCredits();
	int getTotalConcentrationCredits();
	int getTotalMinorCredits();

	void Set_Total_credits_Check(bool);
	void Set_unversity_credits_Check(bool);
	void Set_Major_credits_Check(bool);
	void Set_Track_credits_Check(bool);

	bool CheckRepeatance(Course* pC);
	void ResetIntegers();
	virtual ~StudyPlan();
};
