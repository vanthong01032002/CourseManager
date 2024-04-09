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
        getline(ss, student.mssv, ';');
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

// Hàm xuất danh sách học sinh của một khóa học sang tệp CSV (Câu 19 - Tuyên)
void exportEnrolledStudentsToCSV(const Course& course) {
    ofstream outFile("Enrolled_Students_" + course.id + ".csv");
    if (!outFile.is_open()) {
        cout << "Không thể mở hoặc tạo file" << endl;
        return;
    }

    // Ghi tiêu đề vào tệp CSV
    outFile << "Mã số sinh viên, Tên sinh viên" << endl;

    // Ghi thông tin sinh viên vào tệp CSV
    for (const auto& student : course.enrolledStudents) {
        outFile << student.mssv << ", " << student.fullName << endl;
    }

    outFile.close();
    cout << "Xuat file thanh cong." << endl;
}

// Hàm để cập nhật kết quả của sinh viên vào tệp CSV (câu 22 - Tuyên)
// Thực hiện cập nhật điểm cho sinh viên có MSSV là "SV001"
// updateStudentScore("SV001", 8.5, 9.0, 7.5, 8.0);
void updateStudentScore(const string& studentID, double newTotal, double newFinal, double newMidterm, double newOther) {
    // Mở file CSV chứa thông tin điểm
    ifstream inFile("Score.csv");
    if (!inFile.is_open()) {
        cout << "Khong mo duoc file Score.csv." << endl;
        return;
    }

    // Tạo một vector để lưu trữ các dòng của tệp CSV
    vector<string> lines;
    string line;
    getline(inFile, line); // Bỏ qua tiêu đề

    // Đọc từng dòng và lưu vào vector
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Mở file CSV để ghi lại
    ofstream outFile("Score.csv");
    if (!outFile.is_open()) {
        cout << "Khong tao duoc file Score.csv." << endl;
        return;
    }

    // Ghi tiêu đề vào tệp CSV
    outFile << "ID;MSSV;CourseID;Total;Final;Midterm;Other" << endl;

    // Cập nhật điểm cho sinh viên cụ thể
    bool updated = false;
    for (const auto& line : lines) {
        stringstream ss(line);
        string id, mssv, courseId;
        double total, final, midterm, other;

        getline(ss, id, ';');
        getline(ss, mssv, ';');
        getline(ss, courseId, ';');
        ss >> total;
        ss.ignore();
        ss >> final;
        ss.ignore();
        ss >> midterm;
        ss.ignore();
        ss >> other;

        if (mssv == studentID) {
            // Nếu tìm thấy sinh viên cần cập nhật, ghi thông tin mới vào tệp CSV
            outFile << id << ";" << mssv << ";" << courseId << ";" << newTotal << ";" << newFinal << ";" << newMidterm << ";" << newOther << endl;
            updated = true;
        } else {
            // Nếu không phải sinh viên cần cập nhật, ghi lại thông tin cũ vào tệp CSV
            outFile << id << ";" << mssv << ";" << courseId << ";" << total << ";" << final << ";" << midterm << ";" << other << endl;
        }
    }

    // Nếu không tìm thấy sinh viên cần cập nhật
    if (!updated) {
        cout << "Khong tim thay sinh vien co MSSV: " << studentID << endl;
    }

    outFile.close();
    cout << "Cap nhat diem thanh cong." << endl;
}



// Tính GPA cho mỗi sinh viên
void calculateGPA(vector<Student>& students) {
    for (Student& student : students) {
        student.semesterGPA = (student.total + student.finalGrade + student.midtermGrade + student.otherGrade) / 4.0;
    }
}

// Tính GPA tổng thể của một lớp (Câu 23 - Tuyên)
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
        cout << student.mssv << "\t\t" << student.mssv << "\t\t" << fixed << setprecision(2) << student.semesterGPA << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Overall GPA of the class: " << fixed << setprecision(2) << calculateOverallGPA(students) << endl;
}