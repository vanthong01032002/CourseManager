#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector>
#include <string>

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

void showLoginScreen(int userType);
void loginScreen();
int authenticateUser(const string& username, const string& password, int& userType);
void RegistrarScreen();
void StudentScreen();
void createYear();
void createClass();

void showProfileInfo(int selectedOption);
void changePassword();
//vector<UserProfile> readBinaryFile(const string& filename);
//void displayUserProfile(const vector<UserProfile>& users, const string& loggedInUserID);

void run();

#endif // HEADER_H