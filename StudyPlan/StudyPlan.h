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
	vector<string> CourseCoString;		// list to get the co requisits
	vector<string> CourseCoStringh;		//list to get the corequisits that makes the error with the upper
	vector<string> CoursePreString;		// list to get the pr requisits
	vector<string> CoursePreStringh;	//list to get the prereuisite that makes the error with the upper
	vector<bool> Pre;					//the state of each course in CoursePreString
	vector<bool> Co;					//the state of each course in CourseCoString
public:

	StudyPlan();
	list<Course*> PlanCoursesNeeded();
	bool setStatus(int year, SEMESTER sem, Course_Code code, CourseStatus status);
	bool AddCourse(Course*, int year, SEMESTER);
	bool AddCourse(Course*, int x, int y);
	bool DeleteCourse(Course*, int x, int y);
	void SaveStudyPlan(string filename);
	bool DeleteImportPlan();
	////////////display filter helper functions
	bool AddYear(int x, int y);
	bool AddSemester(int x, int y);
	bool AddType(string type);
	bool original();
	bool SemOriginal();
	///////////////////////////////////////////////

	//functions that return course
	Course* select(int x, int y) const;
	Course* getCourse(Course_Code code);
	void getYearCrd(int* semcrd[]);
	bool isCourse(Course_Code coursecode);
	/// //////////////////////////////////////////Calculate GPA helper function
	list<Course*> AllCoursesNeeded;
	list<Course*> PlanCoursesNeeded();
	//////////////helper functions to avoid repeatance
	int getYear(int x, int y);
	void getYearCrd(int* semcrd[]);
	SEMESTER getSemester(int x, int y);
	/////////////////////helper function in update status
	bool setStatus(int year, SEMESTER sem, Course_Code code, CourseStatus status);
	////////////////////////////draw fuctions
	void virtual DrawMe(GUI*) const;
	void virtual DrawInfo(GUI* pGUI, int x, int y);
	void virtual DrawConnectLine(GUI* pGUI) const;
	void DrawLiveMessage(GUI* pGUI) const;
	void Highlight(int x, int y) const;
	/////////////////////////check functions
	void SetPreCoIssue();
	bool PreReq_CoReq(Course* pC, int year, SEMESTER sem);
	void CheckList(vector<Course_Code> val, string type);
	void WarningReport();
	bool CheckRepeatance(Course* pC);
	void ResetIntegers();
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
	void Concentratioin_Check_Check(bool Check);
	void OverUnderLoad_Check_Check(bool Check);
	void OverUnderLoad_up_down_Check(bool check);
	vector<Course_Code> UnivMissedCourses;
	vector<Course_Code> MajorMissedCourses;
	vector<Course_Code> TrackMissedCourses;



	virtual ~StudyPlan();
};
