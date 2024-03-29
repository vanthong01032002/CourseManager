﻿#include "header.h"

using namespace std;

// Tạo lớp học
string formatId_class(int id) {
    // Định dạng ID thành Yxxx
    string formattedId = "C";
    if (id < 10) {
        formattedId += "00";
    }
    else if (id < 100) {
        formattedId += "0";
    }
    formattedId += to_string(id);
    return formattedId;
}

void createClass() {
    system("cls");
    gotoxy(30, 10);
    cout << "Nhap lop hoc: ";

    string newClass;
    getline(cin, newClass);

    ifstream file("Class.csv");
    if (!file.is_open()) {
        gotoxy(30, 12);
        cout << "Khong mo duoc file. Tao nam hoc that bai.";
        cin.get();
        return;
    }

    // Đọc dòng đầu tiên và bỏ qua
    string header;
    getline(file, header);

    // Đọc dòng thứ hai (nếu có)
    string secondLine;
    getline(file, secondLine);

    file.close();

    int lastId = 0;

    // Nếu file chứa dữ liệu, lấy ID của dòng cuối cùng
    if (!secondLine.empty()) {
        stringstream ss(secondLine);
        string id;
        getline(ss, id, ';');
        lastId = stoi(id.substr(1)); // Lấy số cuối cùng từ mã ID và chuyển thành số nguyên
    }

    int nextId = lastId + 1;
    string newId = formatId_class(nextId); // Định dạng ID mới

    // Mở file để ghi nội dung mới, nhưng trong chế độ thêm vào cuối
    ofstream outFile("Class.csv", ios::app);

    if (!outFile.is_open()) {
        gotoxy(30, 12);
        cout << "Khong mo duoc file. Tao nam hoc that bai.";
        cin.get();
        return;
    }

    // Ghi dòng dữ liệu mới vào cuối file
    outFile << newId << ';' << newClass << '\n';
    outFile.close();

    gotoxy(30, 12);
    cout << "Lop hoc da duoc tao " << newClass << " voi ID " << newId;
    cin.get();
}

// Hiển thị danh sách lớp học
void showListClass() {
    system("cls");
    gotoxy(36, 4);
    cout << "Danh sach lop hoc" << endl;

    ifstream file("Class.csv");

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
    cout << left << setw(10) << "ID" << setw(25) << "Name class" << endl;

    int row = 8;

    // Đọc và hiển thị thông tin từ file
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string classID, className;

        // Trích xuất thông tin của lớp học từ dòng CSV
        getline(ss, classID, ';');
        getline(ss, className, ';');

        // Hiển thị thông tin sinh viên
        gotoxy(14, row);
        cout << left << setw(10) << classID << setw(25) << className << setw(10) << endl;

        row += 2; // Di chuyển xuống để hiển thị thông tin sinh viên tiếp theo
    }

    file.close();

    cin.get();
}