#include "header.h"
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

string loggedInUserID = "";

// ========== xu ly giao dien
void sleepFor(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// ==========


// read file account
int authenticateUser(const string& username, const string& password, int& userType) {
    ifstream file("account.csv");

    if (file.is_open()) {
        string line;
        // Bỏ qua dòng đầu tiên
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string userId, storedUsername, storedPassword, userTypeStr;

            getline(ss, userId, ';');
            getline(ss, storedUsername, ';');
            getline(ss, storedPassword, ';');
            getline(ss, userTypeStr, ';');

            // check username, password
            if (!userId.empty() && username == storedUsername && password == storedPassword) {
                loggedInUserID = userId;
                userType = stoi(userTypeStr);
                file.close();
                return 1;  // Xác thực thành công
            }
        }
        file.close();
    }
    else {
        cout << "Khong mo duoc file";
    }

    return -1;  // Người dùng không tồn tại
}

//find id account
UserInfo getUserInfoById(const string& userId) {
    ifstream file("account.csv");

    if (file.is_open()) {
        string line;

        // Bỏ qua dòng đầu tiên
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string storedUserId, storedUsername, storedPassword, userTypeStr;

            getline(ss, storedUserId, ';');
            getline(ss, storedUsername, ';');
            getline(ss, storedPassword, ';');
            getline(ss, userTypeStr, ';');

            if (userId == storedUserId) {
                UserInfo currentUser;
                currentUser.userId = storedUserId;
                currentUser.username = storedUsername;
                currentUser.password = storedPassword;
                currentUser.userType = stoi(userTypeStr);
                file.close();
                return currentUser;
            }
        }
        file.close();
    }

    // Return a default user if not found (you may want to handle this differently)
    return UserInfo{ "", "", "", 0 };
}

void loginScreen() {
    string username, password;
    int userType;

    while (true) {
        system("cls");
        gotoxy(30, 10);
        cout << "===== DANG NHAP =====" << endl;

        gotoxy(30, 12);
        cout << "Username: ";
        getline(cin, username);

        gotoxy(30, 13);
        cout << "Password: ";
        getline(cin, password);

        int authResult = authenticateUser(username, password, userType);

        if (authResult == 1) {
            showLoginScreen(userType);
            break;
        }
        else if (authResult == 0) {
            gotoxy(30, 15);
            cout << "Tai khoan khong hop le! Vui long thu lai." << endl;
            cin.get();  // Dừng màn hình để người dùng đọc thông báo
        }
        else {
            gotoxy(30, 15);
            cout << "Tai khoan khong hop le! Vui long thu lai." << endl;
            cin.get();  // Dừng màn hình để người dùng đọc thông báo
        }
    }
}


void showLoginScreen(int userType) {
    system("cls");
    gotoxy(30, 10);

    if (userType == 1) {
        gotoxy(30, 14);
        RegistrarScreen();
    }
    else if (userType == 2) {
        gotoxy(30, 18);
        StudentScreen();
    }
}

void StudentScreen() {

    cout << "Dang nhap thanh cong boi Sinh vien!" << endl;
}


void drawMenuRegistrar(int selectedOption) {
    system("cls");
    gotoxy(34, 10);
    cout << "===== GIAO VU SCREEN =====" << endl;
    gotoxy(34, 12);
    cout << (selectedOption == 0 ? "> " : "  ") << "Tao nam hoc moi" << endl;
    gotoxy(34, 14);
    cout << (selectedOption == 1 ? "> " : "  ") << "Quan ly tai khoan" << endl;
    gotoxy(34, 16);
    cout << (selectedOption == 2 ? "> " : "  ") << "Dang xuat" << endl;
    gotoxy(34, 18);
    cout << (selectedOption == 3 ? "> " : "  ") << "Thoat" << endl;
}

void RegistrarScreen() {
    int selectedOption = 0;
    bool returnToMainMenu = false;

    do {
        system("cls");  // Xóa màn hình console
        int windowHeight = GetSystemMetrics(SM_CYSCREEN);
        int windowWidth = GetSystemMetrics(SM_CXSCREEN);

        int centerX = windowWidth / 2;
        int centerY = windowHeight / 2;

        gotoxy(centerX - 15, centerY - 2);

        drawMenuRegistrar(selectedOption);

        switch (_getch()) {
        case KEY_UP:
            selectedOption = (selectedOption - 1 + 4) % 4;
            break;
        case KEY_DOWN:
            selectedOption = (selectedOption + 1) % 4;
            break;
        case KEY_ENTER:
            if (selectedOption == 0) {
                
            }
            else if (selectedOption == 1) {
                int selectedOption_account = 0;
                do {
                    system("cls");  // Xóa màn hình console
                    int windowHeighta = GetSystemMetrics(SM_CYSCREEN);
                    int windowWidtha = GetSystemMetrics(SM_CXSCREEN);

                    int centerXa = windowWidtha / 2;
                    int centerYa = windowHeighta / 2;

                    gotoxy(centerXa - 15, centerYa - 2);
                    showProfileInfo(selectedOption_account);

                    switch (_getch()) {
                        case KEY_UP:
                            selectedOption_account = (selectedOption_account - 1 + 4) % 4;
                            break;
                        case KEY_DOWN:
                            selectedOption_account = (selectedOption_account + 1) % 4;
                            break;
                        case KEY_ENTER:
                            if (selectedOption_account == 0) {
                                changePassword();
                            }
                            else if (selectedOption_account == 1){
                                returnToMainMenu = true;
                            }
                            break;
                    }
                } while (!returnToMainMenu);
               
            }
            else if (selectedOption == 2) {
                // logout
                loggedInUserID = "";
                loginScreen();
            }
            else if (selectedOption == 3) {
                exit(0);
            }
            break;
        }
    } while (true);
}

void writePasswordToFile(const string& targetUserId, const string& newPassword) {
    string filename = "account.csv";
    ifstream infile(filename);
    ofstream outfile("temp.csv");

    if (infile.is_open() && outfile.is_open()) {
        string line;

        // Đọc dòng đầu tiên và ghi lại vào file temp.csv
        getline(infile, line);
        outfile << line << endl;

        while (getline(infile, line)) {
            stringstream ss(line);
            string userId, username, password, userTypeStr;

            getline(ss, userId, ';');
            getline(ss, username, ';');
            getline(ss, password, ';');
            getline(ss, userTypeStr, ';');

            if (userId == targetUserId) {
                // Nếu đúng UserId, thay đổi mật khẩu và ghi vào file temp.csv
                outfile << userId << ';' << username << ';' << newPassword << ';' << userTypeStr << ';' << endl;
            }
            else {
                // Nếu không phải UserId cần thay đổi, ghi lại dòng đó vào file temp.csv
                outfile << line << endl;
            }
        }

        infile.close();
        outfile.close();

        // Đóng tệp gốc
        infile.open(filename, ios::out | ios::trunc);
        infile.close();

        // xóa file gốc
        remove(filename.c_str());

        // Mở tệp temp và đổi tên thành tên của tệp gốc
        rename("temp.csv", filename.c_str());
    }
    else {
        cout << "Khong mo duoc file" << endl;
    }
}

void changePassword() {
    system("cls");

    string oldPassword, newPassword, confirmNewPassword;
    UserInfo currentUser = getUserInfoById(loggedInUserID);

    do {
        gotoxy(34, 10);
        cout << "Nhap mat khau cu: ";
        cin >> oldPassword;
       

        // Kiểm tra mật khẩu cũ (Đây chỉ là ví dụ, bạn có thể thay thế bằng hàm xác nhận từ database)
        if (oldPassword != currentUser.password) {
            gotoxy(34, 11);
            cout << "Mat khau cu khong dung. Vui long nhap lai.";
            sleepFor(500); // Dừng chương trình trong 2 giây
            gotoxy(34, 11);
            cout << "                                                        ";

        }
    } while (oldPassword != currentUser.password);

    do {
        gotoxy(34, 12);
        cout << "Nhap mat khau moi: ";
        cin >> newPassword;

        gotoxy(34, 14);
        cout << "Xac nhan mat khau moi: ";
        cin >> confirmNewPassword;

        // Kiểm tra xác nhận mật khẩu mới
        if (newPassword != confirmNewPassword) {
            gotoxy(34, 15);
            cout << "Mat khau moi va xac nhan khong khop. Vui long nhap lai.";
            sleepFor(500); // Dừng chương trình trong 2 giây
            gotoxy(34, 15);
            cout << "                                                           "; // Xóa thông báo lỗi
        }
    } while (newPassword != confirmNewPassword);

    writePasswordToFile(loggedInUserID, confirmNewPassword);

    gotoxy(32, 16);
    cout << "=> Thay doi mat khau thanh cong." << endl;
    
    _getch();
}

void showProfileInfo(int selectedOption) {
    UserInfo currentUser = getUserInfoById(loggedInUserID);
    system("cls");
    gotoxy(30, 10);
    cout << "===== THONG TIN TAI KHOAN =====" << endl;

    gotoxy(34, 12);
    cout << "Username: " << currentUser.username << endl;

    gotoxy(34, 14);
    cout << "Password: " << currentUser.password << endl;

    gotoxy(34, 16);
    cout << "Chuc vu: " << (currentUser.userType == 1 ? "Giao vu" : "Hoc sinh") << endl;

    gotoxy(34, 18);
    cout << (selectedOption == 0 ? "> " : "  ") << "Thay doi mat khau" << endl;

    gotoxy(34, 20);
    cout << (selectedOption == 1 ? "> " : "  ") << "Quay lai" << endl;

    _getch();
}

void run() {
    loginScreen();
}
