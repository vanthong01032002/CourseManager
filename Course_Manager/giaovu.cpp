#include "header.h"
#include "Score.cpp"

// Đọc thông tin sinh viên từ một tệp CSV
vector<Student> readStudentsFromCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        string temp;
        getline(ss, temp, ';');
        student.mssv = stoi(temp);
        getline(ss, student.MSSV, ';');
        getline(ss, temp, ';');
        student.total = stod(temp);
        getline(ss, temp, ';');
        student.finalGrade = stod(temp);
        getline(ss, temp, ';');
        student.midtermGrade = stod(temp);
        getline(ss, temp, ';');
        student.otherGrade = stod(temp);
        students.push_back(student);
    }
    file.close();
    return students;
}

// Tính GPA cho mỗi sinh viên
void calculateGPA(vector<Student>& students) {
    for (Student& student : students) {
        student.semesterGPA = (student.total + student.finalGrade + student.midtermGrade + student.otherGrade) / 4.0;
    }
}

// Tính GPA tổng thể của một lớp
double calculateOverallGPA(const vector<Student>& students) {
    double totalGPA = 0;
    for (const Student& student : students) {
        totalGPA += student.semesterGPA;
    }
    return totalGPA / students.size();
}

// Hiển thị báo cáo của lớp
void displayClassReport(const vector<Student>& students) {
    cout << "Class Report:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Student ID\tMSSV\t\tSemester GPA" << endl;
    cout << "-------------------------------------------------" << endl;
    for (const Student& student : students) {
        cout << student.studentID << "\t\t" << student.MSSV << "\t\t" << fixed << setprecision(2) << student.semesterGPA << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Overall GPA of the class: " << fixed << setprecision(2) << calculateOverallGPA(students) << endl;
}