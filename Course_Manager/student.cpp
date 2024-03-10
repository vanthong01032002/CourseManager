#include "header.h"

using namespace std;

void showListStudent() {
    system("cls");
    gotoxy(36, 4);
    cout << "Danh sach sinh vien" << endl;

    ifstream file("user.csv");

    if (!file.is_open()) {
        gotoxy(34, 12);
        cout << "Khong mo duoc file.";
        cin.get();
        return;
    }

    // Đọc dòng đầu tiên và bỏ qua
    string header;
    getline(file, header);

    // Hiển thị tiêu đề của bảng
    gotoxy(14, 6);
    cout << left << setw(10) << "MSSV" << setw(25) << "Full Name" << setw(10) << "Gender" << setw(15) << "Date of Birth"
        << setw(15) << "ID Card" << setw(15) << "Expires" << endl;

    int row = 8;

    // Đọc và hiển thị thông tin từ file
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        getline(ss, student.mssv, ';');
        getline(ss, student.fullName, ';');
        getline(ss, student.gender, ';');
        getline(ss, student.dateOfBirth, ';');
        getline(ss, student.idCard, ';');
        getline(ss, student.expires, ';');

        // Hiển thị thông tin sinh viên
        gotoxy(14, row);
        cout << left << setw(10) << student.mssv << setw(25) << student.fullName << setw(10) << student.gender
            << setw(15) << student.dateOfBirth << setw(15) << student.idCard << setw(15) << student.expires << endl;

        row += 2; // Di chuyển xuống để hiển thị thông tin sinh viên tiếp theo
    }

    file.close();

    cin.get();
}

void addStudentToClass() {
    system("cls");
    gotoxy(36, 4);
    cout << "Them sinh vien vao lop hoc" << endl;




    cin.get();
}