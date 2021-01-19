#include "CalculateGPA.h"
#include "Courses/UnivCourse.h"
#include "Actions/Action.h"
#include "Registrar.h"
#include <iostream>
#include <string>

CalculateGPA::CalculateGPA(Registrar* p) :Action(p)
{

}

bool CalculateGPA::Execute()
{
    GUI* pGUI = pReg->getGUI();
    StudyPlan* pS = pReg->getStudyPlay();
    list<Course*> CRS = pS->PlanCoursesNeeded();
    string x, y, z;
    double GPA = 0;
    double TotalQP = 0;
    int TotalCredits = 0;
    for (auto it = CRS.begin(); it != CRS.end(); it++)
    {
        x = "Add the letter grade for " + (*it)->getCode() + ": ";
        pGUI->PrintMsg(x);
        CourseGradeLetter gradeLetter = pGUI->GetSrting();
        for (int i = 0; i < gradeLetter.size(); i++)
        {
            gradeLetter[i] = toupper(gradeLetter[i]);
        }
        while (gradeLetter != "A" && gradeLetter != "A-" && gradeLetter != "B+" && gradeLetter != "B"
            && gradeLetter != "B-" && gradeLetter != "C+" && gradeLetter != "C" && gradeLetter != "C-"
            && gradeLetter != "F" && gradeLetter != "P" && gradeLetter != "I" && gradeLetter != "W"
            && gradeLetter != "WP" && gradeLetter != "WF" && gradeLetter != "IP")
        {
            x = "Add the valid letter grade for " + (*it)->getCode() + ": ";
            pGUI->PrintMsg(x);
            CourseGradeLetter gradeLetter = pGUI->GetSrting();
        }
        if (gradeLetter == "A" || gradeLetter == "A-" || gradeLetter == "B+" || gradeLetter == "B"
            || gradeLetter == "B-" || gradeLetter == "C+" || gradeLetter == "C" || gradeLetter == "C-"
            || gradeLetter == "F")
        {
            (*it)->setGradeLetter(gradeLetter);
            (*it)->setGradePoints();
            (*it)->setQp();
            TotalQP = TotalQP + (*it)->getQP();
            TotalCredits = TotalCredits + (*it)->getCredits();
            GPA = TotalQP / TotalCredits;
        }
    }
    y = to_string(GPA);
    z = "Total GPA: " + y;
    pGUI->setGPA(z);
    return true;
}

CalculateGPA::~CalculateGPA()
{

}
