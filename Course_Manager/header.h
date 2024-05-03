#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>
#include <iomanip>

using namespace std;

extern string loggedInUserID;

struct UserInfo {
    string userId;
    string username;
    string password;
    int userType; // 1: Giáo vụ, 2: Học sinh
};

struct UserProfile {
    string userID;
    string name;
    string birthDate;
    string birthPlace;
    string phoneNumber;
    string email;
};

struct YearInfo {
    string id;
    string year;
};
struct Date {
    int day;
    int month;
    int year;
};

struct Semester
{
    string id;
    int semesterNumber;
    string academicYear;
    Date start_date;
    Date end_date;
};

struct Student {
    string mssv;
    string fullName;
    string gender;
    string dateOfBirth;
    string idCard;
    string expires;
    double total;
    double finalGrade;
    double midtermGrade;
    double otherGrade;
    double semesterGPA;

};

struct Course {
    string id;
    string semesterID;
    string courseName;
    string className;
    string teacherName;
    int credit;
    int maxStudents;
    string dayOfWeek; // For example: MON / TUE / WED / THU / FRI / SAT
    string session; // For example: S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30))
    string year;
    vector<double> finalGrades; // Final grades of all students
    vector<Student> enrolledStudents;
};

struct Score {
    string id;
    string mssv;
    string courseId;
    double total;
    double final;
    double midterm;
    double other;
};


void sleepFor(int milliseconds);
void gotoxy(int x, int y);
void RegistrarScreen();
void drawMenuRegistrar(int selectedOption);
void drawMenuClass(int selectedOption);
void drawMenuStudent(int selectedOption);
void drawMenuCourse(int selectedOption);

void showLoginScreen(int userType);
void loginScreen();
int authenticateUser(const string& username, const string& password, int& userType);
UserInfo getUserInfoById(const string& userId);
void showLoginScreen(int userType);
void drawMenuStudentScreen(int selectedOption);
void showProfileInfo(int selectedOption);
void StudentScreen();;
void changePassword();
void writePasswordToFile(const string& targetUserId, const string& newPassword);

string formatId_year(int id);
bool yearExists(const string& yearToCheck);
bool isValidYearFormat(const string& year);
void createYear();

bool isValidSemester(int semesterNumber);
string formatId_semester(int id);
bool isSemesterExists(const int& semester, const string& academicYear);
void createSemester();

string formatId_class(int id);
void createClass();
void showListClass();

void showListStudent();
void addStudentToClass();

string formatId_course(int id);
bool isValidDayOfWeek(const string& dayOfWeek);
bool isValidSession(const string& session);
void createCourse();
void uploadStudentList(const Course& course);
void showListCourse();
void updateCourseInfo();
void addStudentToCourse();
void removeStudentFromCourse();
void removeCourse();

void ShowListScore();
void addScore();
void viewEnrolledCourses();

Score getScoreByMSSV();
void showScore(const Score& score);
string getCourseNameByID(const string& courseId);

//Giáo vụ (giaovu.cpp)
bool readStudentsFromCSV(const string& filename, Student students[], int& count);
void exportEnrolledStudentsToCSV(const Student students[], int count, const string& filename);
void updateStudentScore(const string& studentID, double newTotal, double newFinal, double newMidterm, double newOther);
void showClassScores(const string& className, const string& semester);
void calculateGPA(Student students[], int count);
double calculateOverallGPA(const Student students[], int count);
void displayClassReport(const Student students[], int count);
void viewStudentsInClass();
void viewStudentsInCourse();

void run();

#endif // HEADER_H
