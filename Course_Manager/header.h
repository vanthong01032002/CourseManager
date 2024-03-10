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
};

void sleepFor(int milliseconds);
void gotoxy(int x, int y);
void RegistrarScreen();
void drawMenuRegistrar(int selectedOption);
void drawMenuClass(int selectedOption);
void drawMenuStudent(int selectedOption);

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

//vector<UserProfile> readBinaryFile(const string& filename);
//void displayUserProfile(const vector<UserProfile>& users, const string& loggedInUserID);

void run();

#endif // HEADER_H