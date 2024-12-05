#include "table_generator.h"
#include "table_db.h"
#include <vector>
#include "course_db.h"
#include <random>

using namespace std;

TableGenerator::TableGenerator(CourseDatabase &courseDB, TableDatabase &tableDB)
    : courseDB(courseDB), tableDB(tableDB), totalGrade(0)
{
}


void TableGenerator::generateTable(Table &table) //query로 처리된 courseDB에 있는 course중 greedyAloghrithm으로 시간표 생성
{
    vector<Course> courses = this->courseDB.query(this->query);
    for (int i = 0; i < 5; i++) // 시간표를 5개 만듦
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(courses.begin(), courses.end(), g); // course의 순서를 섞음

        this->currentGrade = 0; 
        this->existCourse.clear();
        this->time.clear();
        for (Course &course : courses) // course의 수만큼 반복
        {
            if (totalGrade >= currentGrade + course.get_grade()) // 설정한 총 학점 수 보다 현재 학점 + course의 학점이 더 작거나 같을 경우
            {
                if (this->findTime(course) && findCourse(course)) // 시간이 겹치지 않을 경우
                {
                    table.insert_course(course); // 시간표에 강의 추가
                    this->existCourse.push_back(course.get_name());
                    this->currentGrade += course.get_grade(); // 현재 총 학점수를 강의의 학점만큼 증가
                }
            }
        }
    }   
    this->tableDB.insert(table);
}

void TableGenerator::setQuery(CourseQuery query)
{
    this->query = query;
}

void TableGenerator::setTotalGrade(int grade) // 생성할 시간표의 총 학점수 설정
{
    this->totalGrade = grade;
}

bool TableGenerator::findTime(Course course) // 겹치는 시간 있는지 확인
{
    for (const CourseTime availableTime : course.get_times())
    {
        for (const CourseTime existingTime : this->time)
        {
            if (availableTime.weekday == existingTime.weekday && availableTime.time == existingTime.time) // 겹치는 시간이 있는 경우
            {
                return false;
            }
        }
    }

    for (const CourseTime availableTime : course.get_times()) // 시간표에 할당된 시간을 기록
    {
        this->time.push_back(availableTime);
    }

    return true;
}

bool TableGenerator::findCourse(Course course) // 같은 과목 안들어가도록 설정
{
    for (string name : this->existCourse)
    {
        if (name == course.get_name())
        {
            return false;
        }
    }

    return true;
}