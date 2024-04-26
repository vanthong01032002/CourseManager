#include "header.h"
#include "Score.cpp"

// Đọc thông tin sinh viên từ một tệp CSV
bool readStudentsFromCSV(const string& filename, Student students[], int& count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Không thể mở file." << endl;
        return false;
    }

    string line;
    count = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string temp;

        getline(ss, students[count].mssv, ';');
        getline(ss, students[count].fullName, ';');
        getline(ss, students[count].gender, ';');
        getline(ss, students[count].dateOfBirth, ';');
        getline(ss, students[count].idCard, ';');
        getline(ss, students[count].expires, ';');
        getline(ss, temp, ';');
        students[count].total = stod(temp);
        getline(ss, temp, ';');
        students[count].finalGrade = stod(temp);
        getline(ss, temp, ';');
        students[count].midtermGrade = stod(temp);
        getline(ss, temp, ';');
        students[count].otherGrade = stod(temp);

        count++;
    }
    file.close();
    return true;
}

// Hàm xuất danh sách học sinh của một khóa học sang tệp CSV
void exportEnrolledStudentsToCSV(const Student students[], int count, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Không thể mở hoặc tạo file." << endl;
        return;
    }

    // Ghi tiêu đề vào tệp CSV
    outFile << "Mã số sinh viên, Tên sinh viên, Giới tính, Ngày sinh, Chứng minh nhân dân, Ngày hết hạn" << endl;

    // Ghi thông tin sinh viên vào tệp CSV
    for (int i = 0; i < count; ++i) {
        outFile << students[i].mssv << ", " << students[i].fullName << ", " << students[i].gender << ", " << students[i].dateOfBirth << ", " << students[i].idCard << ", " << students[i].expires << endl;
    }

    outFile.close();
    cout << "Xuất file thành công." << endl;
}

// Hàm để cập nhật kết quả của sinh viên vào tệp CSV
void updateStudentScore(const string& studentID, double newTotal, double newFinal, double newMidterm, double newOther) {
    ifstream inFile("Score.csv");
    if (!inFile.is_open()) {
        cout << "Không thể mở file." << endl;
        return;
    }

    ofstream outFile("Score_temp.csv");
    if (!outFile.is_open()) {
        cout << "Không thể tạo file." << endl;
        inFile.close();
        return;
    }

    string line;
    bool updated = false;
    while (getline(inFile, line)) {
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
            outFile << id << ";" << mssv << ";" << courseId << ";" << newTotal << ";" << newFinal << ";" << newMidterm << ";" << newOther << endl;
            updated = true;
        } else {
            outFile << id << ";" << mssv << ";" << courseId << ";" << total << ";" << final << ";" << midterm << ";" << other << endl;
        }
    }

    inFile.close();
    outFile.close();

    if (remove("Score.csv") != 0) {
        cout << "Không thể xóa file." << endl;
        return;
    }

    if (rename("Score_temp.csv", "Score.csv") != 0) {
        cout << "Không thể đổi tên file." << endl;
        return;
    }

    if (!updated) {
        cout << "Không tìm thấy sinh viên có MSSV: " << studentID << endl;
    } else {
        cout << "Cập nhật điểm thành công." << endl;
    }
}

// Xem bảng điểm của một lớp, bao gồm các điểm cuối cùng của tất cả các khóa học trong học kỳ. 
void showClassScores(const string& className, const string& semester) {
    ifstream file("Score.csv");
    if (!file.is_open()) {
        cout << "Khong mo duoc file Score.csv." << endl;
        return;
    }

    // Bỏ qua dòng đầu tiên (tiêu đề)
    string line;
    getline(file, line);

    cout << "Bảng điểm của lớp " << className << " trong học kỳ " << semester << ":" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << left << setw(15) << "MSSV" << setw(20) << "Tên sinh viên" << setw(10) << "Total" << setw(10) << "Final" << setw(10) << "Midterm" << setw(10) << "Other" << endl;
    cout << "--------------------------------------------------------------" << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        Score score;

        getline(ss, score.id, ';');
        getline(ss, score.mssv, ';');
        getline(ss, score.courseId, ';');
        ss >> score.total;
        ss.ignore();
        ss >> score.final;
        ss.ignore();
        ss >> score.midterm;
        ss.ignore();
        ss >> score.other;

        // Kiểm tra xem sinh viên thuộc lớp và học kỳ đã cho hay không
        // Đồng thời kiểm tra học kỳ của khóa học trong Score.csv
        ifstream courseFile("Course.csv");
        if (courseFile.is_open()) {
            string courseLine;
            bool found = false;
            while (getline(courseFile, courseLine)) {
                stringstream courseSS(courseLine);
                string courseId, courseClass, courseSemester;

                getline(courseSS, courseId, ';');
                getline(courseSS, courseClass, ';');
                getline(courseSS, courseSemester, ';');

                if (score.courseId == courseId && className == courseClass && semester == courseSemester) {
                    found = true;
                    break;
                }
            }
            courseFile.close();

            if (found) {
                // Lấy tên sinh viên từ file danh sách sinh viên
                ifstream studentFile("Student_class.csv");
                if (studentFile.is_open()) {
                    string studentLine;
                    while (getline(studentFile, studentLine)) {
                        stringstream studentSS(studentLine);
                        string studentId, studentClass, studentName;

                        getline(studentSS, studentId, ';');
                        getline(studentSS, studentClass, ';');
                        getline(studentSS, studentName, ';');

                        if (studentId == score.mssv) {
                            cout << left << setw(15) << score.mssv << setw(20) << studentName << setw(10) << score.total << setw(10) << score.final << setw(10) << score.midterm << setw(10) << score.other << endl;
                            break;
                        }
                    }
                    studentFile.close();
                }
                else {
                    cout << "Khong mo duoc file Student_class.csv." << endl;
                    return;
                }
            }
        }
        else {
            cout << "Khong mo duoc file Course.csv." << endl;
            return;
        }
    }

    file.close();
}

// Tính GPA cho mỗi sinh viên
void calculateGPA(Student students[], int count) {
    for (int i = 0; i < count; ++i) {
        students[i].semesterGPA = (students[i].total + students[i].finalGrade + students[i].midtermGrade + students[i].otherGrade) / 4.0;
    }
}

// Tính GPA tổng thể của một lớp
double calculateOverallGPA(const Student students[], int count) {
    double totalGPA = 0;
    for (int i = 0; i < count; ++i) {
        totalGPA += students[i].semesterGPA;
    }
    return totalGPA / count;
}

void displayClassReport(const Student students[], int count) {
    cout << "Báo cáo lớp học:" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "Student ID\tMSSV\t\tGPA Học Kỳ" << endl;
    cout << "-------------------------------------------------" << endl;
    for (int i = 0; i < count; ++i) {
        cout << students[i].mssv << "\t\t" << students[i].fullName << "\t\t" << fixed << setprecision(2) << students[i].semesterGPA << endl;
    }
    cout << "-------------------------------------------------" << endl;
    cout << "Tổng quát GPA của lớp: " << fixed << setprecision(2) << calculateOverallGPA(students, count) << endl;
}




