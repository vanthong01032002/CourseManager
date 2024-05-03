#include "header.h"

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


    int count = 0;
    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề
    while (getline(file, line)) {
        count++;
    }

    int nextId = count + 1;
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

void viewStudentsInClass() {
    system("cls");
    gotoxy(30, 3);
    cout << "Nhap vao classID: ";
    string classID;
    getline(cin, classID);

    ifstream file("student_class.csv");

    if (!file.is_open()) {
        cout << "Unable to open file student_class.csv." << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line

    bool classFound = false;

    gotoxy(30, 5);
    cout << "Danh sach sinh vien trong lop " << classID << ":" << endl;

    // In ra tiêu đề của bảng
    gotoxy(30, 7);

    cout << setw(15) << left << "MSSV" << setw(30) << left << "Ten" << endl;
    gotoxy(30, 7);

    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    int y = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string mssv, className, name;
        getline(ss, mssv, ';');
        getline(ss, className, ';');
        getline(ss, name, ';');

        if (className == classID) {
            classFound = true;
            // In ra từng dòng của bảng
            y += 2;
            gotoxy(30, 7 + y);
            cout << setw(15) << left << mssv << setw(30) << left << name << endl;
        }
    }

    file.close();

    if (!classFound) {
        cout << "Khong tim thay lop " << classID << " trong file student_class.csv." << endl;
    }
    _getch();
}

void viewStudentsInCourse() {
    system("cls");
    gotoxy(30, 3);
    cout << "Nhap vao CourseID: ";
    string courseID;
    getline(cin, courseID);

    ifstream courseFile("Student_course.csv");
    if (!courseFile.is_open()) {
        cout << "Unable to open file course.csv." << endl;
        return;
    }

    ifstream studentFile("studentList.csv");
    if (!studentFile.is_open()) {
        cout << "Unable to open file student.csv." << endl;
        return;
    }

    string courseLine, studentLine;
    getline(courseFile, courseLine); // Skip header line

    bool courseFound = false;

    gotoxy(30, 5);
    cout << "Danh sach sinh vien trong khoa hoc " << courseID << ":" << endl;

    // In ra tiêu đề của bảng
    gotoxy(30, 7);
    cout << setw(15) << left << "StudentID" << setw(30) << left << "StudentName" << endl;
    gotoxy(30, 7);
    cout << setfill('-') << setw(45) << "" << setfill(' ') << endl;
    int y = 0;
    while (getline(courseFile, courseLine)) {
        stringstream ss(courseLine);
        string courseId, studentId;
        getline(ss, courseId, ';');
        getline(ss, studentId, ';');

        if (courseId == courseID) {
            courseFound = true;

            // Đọc thông tin sinh viên từ file "student.csv"
            while (getline(studentFile, studentLine)) {
                stringstream studentSS(studentLine);
                string studentID, studentName;
                getline(studentSS, studentID, ';');
                getline(studentSS, studentName, ';');

                if (studentID == studentId) {
                    // Hiển thị thông tin sinh viên
                    y += 2;
                    gotoxy(30, 7 + y);
                    cout << setw(15) << left << studentID << setw(30) << left << studentName << endl;
                    break; // Dừng việc tìm kiếm khi tìm thấy sinh viên
                }
            }
        }
    }

    courseFile.close();
    studentFile.close();

    if (!courseFound) {
        cout << "Khong tim thay khoa hoc " << courseID << " trong file course.csv." << endl;
    }
    _getch();
}   