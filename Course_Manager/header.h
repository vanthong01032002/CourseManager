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
};

struct Student {
    string mssv;
    string fullName;
    string gender;
    string dateOfBirth;
    string idCard;
    string expires;
};

struct Score {
    string id;
    string mssv;
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
void loginScreen();
void showLoginScreen(int userType);
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
void showListCourse();
void updateCourseInfo();

void ShowListScore();
void addScore();

void run();

#endif // HEADER_H