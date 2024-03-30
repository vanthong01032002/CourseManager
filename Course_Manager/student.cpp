#include "header.h"

using namespace std;

void viewEnrolledCourses() {
    system("cls");

    ifstream file("Student_course.csv");

    if (!file.is_open()) {
        cout << "Khong mo duoc file." << endl;
        cin.get();
        return;
    }


    gotoxy(10, 6);
    cout << left << setw(10) << "ID" << setw(25) << "Course name" << setw(25) << "Class name" <<
        setw(25) << "Teacher name" << setw(8) << "Credit" << setw(12) << "Day Of Week" << setw(12) << "Session" << setw(10) << "Semester" << setw(10) << "Year" << endl;

    int row = 8;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string studentId, courseId;

        getline(ss, courseId, ';');
        getline(ss, studentId);

        if (studentId == loggedInUserID) {
            ifstream courseFile("Course.csv");

            if (courseFile.is_open()) {
                string courseLine;
                while (getline(courseFile, courseLine)) {
                    stringstream courseSS(courseLine);
                    Course course;

                    getline(courseSS, course.id, ';');
                    getline(courseSS, course.courseName, ';');
                    getline(courseSS, course.className, ';');
                    getline(courseSS, course.teacherName, ';');
                    courseSS >> course.credit;
                    courseSS.ignore();
                    courseSS >> course.maxStudents;
                    courseSS.ignore();
                    getline(courseSS, course.dayOfWeek, ';');
                    getline(courseSS, course.session, ';');
                    getline(courseSS, course.semesterID, ';');
                    getline(courseSS, course.year);

                    if (course.id == courseId) {
                        gotoxy(10, row);
                        cout << left << setw(10) << course.id << setw(25) << course.courseName << setw(25) << course.className <<
                            setw(25) << course.teacherName << setw(8) << course.credit << setw(12) << course.dayOfWeek << setw(12) << course.session << setw(10) << course.semesterID << setw(10) << course.year << endl;

                        row += 2;
                        break;
                    }
                }
                courseFile.close();
            }
            else {
                cout << "Khong mo duoc file." << endl;
                cin.get();
                return;
            }
        }
    }

    file.close();
    cin.get();
}