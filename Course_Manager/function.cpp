﻿#include "header.h"

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13

string userIdLogin = "";

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

void drawMenuRegistrar(int selectedOption) {
    system("cls");
    gotoxy(34, 10);
    cout << "===== GIAO VU SCREEN =====" << endl;
    gotoxy(34, 12);
    cout << (selectedOption == 0 ? "> " : "  ") << "Tao nam hoc moi" << endl;
    gotoxy(34, 14);
    cout << (selectedOption == 1 ? "> " : "  ") << "Tao hoc ki moi" << endl;
    gotoxy(34, 16);
    cout << (selectedOption == 2 ? "> " : "  ") << "Quan ly khoa hoc" << endl;
    gotoxy(34, 18);
    cout << (selectedOption == 3 ? "> " : "  ") << "Quan ly lop hoc" << endl;
    gotoxy(34, 20);
    cout << (selectedOption == 4 ? "> " : "  ") << "Quan ly sinh vien" << endl;
    gotoxy(34, 22);
    cout << (selectedOption == 5 ? "> " : "  ") << "Quan ly tai khoan" << endl;
    gotoxy(34, 24);
    cout << (selectedOption == 6 ? "> " : "  ") << "Dang xuat" << endl;
    gotoxy(34, 26);
    cout << (selectedOption == 7 ? "> " : "  ") << "Thoat" << endl;
}

void drawMenuClass(int selectedOption) {
    system("cls");
    gotoxy(34, 10);
    cout << "===== QUAN LY LOP HOC =====" << endl;
    gotoxy(34, 12);
    cout << (selectedOption == 0 ? "> " : "  ") << "Tao lop hoc" << endl;
    gotoxy(34, 14);
    cout << (selectedOption == 1 ? "> " : "  ") << "Xem danh sach lop hoc" << endl;
    gotoxy(34, 16);
    cout << (selectedOption == 2 ? "> " : "  ") << "Thoat" << endl;
}

void drawMenuStudent(int selectedOption){
    system("cls");
    gotoxy(34, 10);
    cout << "===== QUAN LY SINH VIEN =====" << endl;
    gotoxy(34, 12);
    cout << (selectedOption == 0 ? "> " : "  ") << "Xem danh sach sinh vien" << endl;
    gotoxy(34, 14);
    cout << (selectedOption == 1 ? "> " : "  ") << "Them sinh vien vao lop hoc" << endl;
    gotoxy(34, 16);
    cout << (selectedOption == 2 ? "> " : "  ") << "Thoat" << endl;
}

void drawMenuCourse(int selectedOption) {
    system("cls");
    gotoxy(34, 10);
    cout << "===== QUAN LY KHOA HOC =====" << endl;
    gotoxy(34, 12);
    cout << (selectedOption == 0 ? "> " : "  ") << "Tao khoa hoc" << endl;
    gotoxy(34, 14);
    cout << (selectedOption == 1 ? "> " : "  ") << "Xem danh sach khoa hoc" << endl;
    gotoxy(34, 16);
    cout << (selectedOption == 2 ? "> " : "  ") << "Cap nhat khoa hoc" << endl;
    gotoxy(34, 18);
    cout << (selectedOption == 3 ? "> " : "  ") << "Xoa khoa hoc" << endl;
    gotoxy(34, 20);
    cout << (selectedOption == 4 ? "> " : "  ") << "Them sinh vien vao khoa hoc" << endl;
    gotoxy(34, 22);
    cout << (selectedOption == 5 ? "> " : "  ") << "Xoa sinh vien vao khoa hoc" << endl;
    gotoxy(34, 24);
    cout << (selectedOption == 6 ? "> " : "  ") << "Thoat" << endl;
}

void RegistrarScreen() {
    int selectedOption = 0;
    bool returnToMainMenu = false;

    do {
        system("cls");  // Clear console screen
        int windowHeight = GetSystemMetrics(SM_CYSCREEN);
        int windowWidth = GetSystemMetrics(SM_CXSCREEN);

        int centerX = windowWidth / 2;
        int centerY = windowHeight / 2;

        gotoxy(centerX - 15, centerY - 2);
        drawMenuRegistrar(selectedOption);

        switch (_getch()) {
        case KEY_UP:
            selectedOption = (selectedOption - 1 + 8) % 8;
            break;
        case KEY_DOWN:
            selectedOption = (selectedOption + 1) % 8;
            break;
        case KEY_ENTER:
            if (selectedOption == 0) {
                createYear();
            }
            else if (selectedOption == 1) {
                createSemester();
            }
            else if (selectedOption == 2) {
                int selectedOption_course = 0;
                do {
                    system("cls");  // Clear console screen
                    int windowHeighta = GetSystemMetrics(SM_CYSCREEN);
                    int windowWidtha = GetSystemMetrics(SM_CXSCREEN);

                    int centerXa = windowWidtha / 2;
                    int centerYa = windowHeighta / 2;

                    gotoxy(centerXa - 15, centerYa - 2);
                    drawMenuCourse(selectedOption_course);

                    switch (_getch()) {
                    case KEY_UP:
                        selectedOption_course = (selectedOption_course - 1 + 7) % 7;
                        break;
                    case KEY_DOWN:
                        selectedOption_course = (selectedOption_course + 1) % 7;
                        break;
                    case KEY_ENTER:
                        if (selectedOption_course == 0) {
                            createCourse();
                        }
                        else if (selectedOption_course == 1) {
                            
                        }
                        else if (selectedOption_course == 6) {
                            returnToMainMenu = true;
                        }
                        break;
                    }
                } while (!returnToMainMenu);

                // Reset returnToMainMenu for the main loop
                returnToMainMenu = false;
            }

            else if (selectedOption == 3) {
                int selectedOption_class = 0;
                do {
                    system("cls");  // Clear console screen
                    int windowHeighta = GetSystemMetrics(SM_CYSCREEN);
                    int windowWidtha = GetSystemMetrics(SM_CXSCREEN);

                    int centerXa = windowWidtha / 2;
                    int centerYa = windowHeighta / 2;

                    gotoxy(centerXa - 15, centerYa - 2);
                    drawMenuClass(selectedOption_class);

                    switch (_getch()) {
                    case KEY_UP:
                        selectedOption_class = (selectedOption_class - 1 + 3) % 3;
                        break;
                    case KEY_DOWN:
                        selectedOption_class = (selectedOption_class + 1) % 3;
                        break;
                    case KEY_ENTER:
                        if (selectedOption_class == 0) {
                            createClass();
                        }
                        else if (selectedOption_class == 1) {
                            showListClass();
                        }
                        else if (selectedOption_class == 2) {
                            returnToMainMenu = true;
                        }
                        break;
                    }
                } while (!returnToMainMenu);

                // Reset returnToMainMenu for the main loop
                returnToMainMenu = false;
            }
            else if (selectedOption == 4) {
                int selectedOption_student = 0;
                do {
                    system("cls");  // Clear console screen
                    int windowHeighta = GetSystemMetrics(SM_CYSCREEN);
                    int windowWidtha = GetSystemMetrics(SM_CXSCREEN);

                    int centerXa = windowWidtha / 2;
                    int centerYa = windowHeighta / 2;

                    gotoxy(centerXa - 15, centerYa - 2);
                    drawMenuStudent(selectedOption_student);

                    switch (_getch()) {
                    case KEY_UP:
                        selectedOption_student = (selectedOption_student - 1 + 3) % 3;
                        break;
                    case KEY_DOWN:
                        selectedOption_student = (selectedOption_student + 1) % 3;
                        break;
                    case KEY_ENTER:
                        if (selectedOption_student == 0) {
                            showListStudent();
                        }
                        else if (selectedOption_student == 1) {
                            // Action for option 1
                        }
                        else if (selectedOption_student == 2) {
                            returnToMainMenu = true;
                        }
                        break;
                    }
                } while (!returnToMainMenu);

                // Reset returnToMainMenu for the main loop
                returnToMainMenu = false;
            }
            else if (selectedOption == 5) {
                int selectedOption_account = 0;
                do {
                    system("cls");  // Clear console screen
                    int windowHeighta = GetSystemMetrics(SM_CYSCREEN);
                    int windowWidtha = GetSystemMetrics(SM_CXSCREEN);

                    int centerXa = windowWidtha / 2;
                    int centerYa = windowHeighta / 2;

                    gotoxy(centerXa - 15, centerYa - 2);
                    showProfileInfo(selectedOption_account);

                    switch (_getch()) {
                    case KEY_UP:
                        selectedOption_account = (selectedOption_account - 1 + 2) % 2;
                        break;
                    case KEY_DOWN:
                        selectedOption_account = (selectedOption_account + 1) % 2;
                        break;
                    case KEY_ENTER:
                        if (selectedOption_account == 0) {
                            changePassword();
                        }
                        else if (selectedOption_account == 1) {
                            returnToMainMenu = true;
                        }
                        break;
                    }
                } while (!returnToMainMenu);

                // Reset returnToMainMenu for the main loop
                returnToMainMenu = false;
            }
            else if (selectedOption == 6) {
                // logout
                userIdLogin = "";
                loginScreen();
            }
            else if (selectedOption == 7) {
                exit(0);
            }
            break;
        }
    } while (true);
}

void run() {
    loginScreen();
}
