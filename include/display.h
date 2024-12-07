#ifndef DISPLAY_H
#define DISPLAY_H

#include "course.h"
#include "course_db.h"
#include "table.h"
#include "table_db.h"
#include "table_generator.h"
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

struct Schedule;

struct User
{
    string name;
    int year;
    int student_id;
    string department;
};

extern User currentUser;
extern vector<Schedule *> schedules;       // ����� �ð�ǥ ���
extern vector<string> selectedProfessors;  // ����� ���� ���� ���
extern bool isEnglishA;                    // ����� ���� A ���� ����
extern int maxCredits;                     // ����� �ִ� ����
extern unordered_set<string> selectedDays; // ����� ���� ���� ���

class Display
{
  private:
    // ������ ����
    CourseDatabase courseDatabase;
    TableDatabase tableDatabase;
    TableGenerator tableGenerator;
    User user;

    public:
    Display(CourseDatabase &courseDatabase, TableDatabase &tableDatabase, TableGenerator &tableGenerator);
    void addCourse(const string &course);
    void addDay(const string &day);
    void removeCourse(int index);
    void removeDay(int index);
    void display(Table& table) const;
    void createSchedule();
    void searchAndModifySchedule();
    void setupUser();
    void mainMenu();
};


#endif
