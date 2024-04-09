#include "header.h"

using namespace std;

void viewEnrolledCourses() {
    system("cls"); // Xóa màn hình console
    string semester;
    cout << "Nhap vao hoc ky muon xem : ";
    cin >> semester;
    cin.ignore();
    ifstream file("Student_course.csv"); // Mở file chứa thông tin đăng ký khóa học của sinh viên

    if (!file.is_open()) { // Kiểm tra xem file có mở thành công không
        cout << "Khong mo duoc file." << endl;
        cin.get();
        return;
    }

    // Hiển thị tiêu đề của bảng
    gotoxy(10, 6);
    cout << left << setw(10) << "ID" << setw(25) << "Course name" << setw(25) << "Class name" <<
        setw(25) << "Teacher name" << setw(8) << "Credit" << setw(12) << "Day Of Week" << setw(12) << "Session" << setw(10) << "Semester" << setw(10) << "Year" << endl;

    int row = 8; // Dòng bắt đầu để hiển thị thông tin khóa học

    string line;
    while (getline(file, line)) { // Đọc từng dòng trong file
        stringstream ss(line);
        string studentId, courseId;

        getline(ss, courseId, ';'); // Đọc mã số sinh viên
        getline(ss, studentId); // Đọc mã khóa học

        if (studentId == loggedInUserID) { // Kiểm tra xem khóa học này có phải của sinh viên đã đăng nhập không
            // Nếu là khóa học của sinh viên, thì hiển thị thông tin khóa học
            ifstream courseFile("Course.csv"); // Mở file chứa thông tin của các khóa học

            if (courseFile.is_open()) {
                string courseLine;
                while (getline(courseFile, courseLine)) {
                    stringstream courseSS(courseLine);
                    Course course;

                    getline(courseSS, course.id, ';');
                    getline(courseSS, course.courseName, ';');
                    getline(courseSS, course.className, ';');
                    getline(courseSS, course.teacherName, ';');
                    courseSS >> course.credit;
                    courseSS.ignore();
                    courseSS >> course.maxStudents;
                    courseSS.ignore();
                    getline(courseSS, course.dayOfWeek, ';');
                    getline(courseSS, course.session, ';');
                    getline(courseSS, course.semesterID, ';');
                    getline(courseSS, course.year);

                    if (course.id == courseId) {
                        if (course.semesterID == semester) {// Nếu mã khóa học trùng với mã khóa học trong file đăng ký
                            // Hiển thị thông tin khóa học
                            gotoxy(10, row);
                            cout << left << setw(10) << course.id << setw(25) << course.courseName << setw(25) << course.className <<
                                setw(25) << course.teacherName << setw(8) << course.credit << setw(12) << course.dayOfWeek << setw(12) << course.session << setw(10) << course.semesterID << setw(10) << course.year << endl;

                            row += 2; // Di chuyển xuống dòng tiếp theo để hiển thị thông tin khóa học tiếp theo
                            break; // Thoát khỏi vòng lặp vì đã tìm được thông tin của khóa học
                        }
                    }
                }
                courseFile.close();
            }
            else {
                cout << "Khong mo duoc file." << endl;
                cin.get();
                return;
            }
        }
    }

    file.close(); // Đóng file
    cin.get(); // Dừng màn hình để người dùng có thời gian đọc thông tin
}

Score getScoreByMSSV() {
    ifstream file("Score.csv");

    if (file.is_open()) {
        string line;

        // Bỏ qua dòng đầu tiên
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string id, mssvFromFile, courseId, totalStr, finalStr, midtermStr, otherStr;

            getline(ss, id, ';');
            getline(ss, mssvFromFile, ';');
            getline(ss, courseId, ';');
            getline(ss, totalStr, ';');
            getline(ss, finalStr, ';');
            getline(ss, midtermStr, ';');
            getline(ss, otherStr, ';');

            if (mssvFromFile == loggedInUserID) {
                // Chuyển đổi các trường điểm từ string sang double
                Score score;
                score.id = id;
                score.mssv = mssvFromFile;
                score.courseId = courseId;
                score.total = stod(totalStr);
                score.final = stod(finalStr);
                score.midterm = stod(midtermStr);
                score.other = stod(otherStr);

                file.close();
                return score;
            }
        }
        file.close();
    }

    // Trả về thông tin điểm mặc định nếu không tìm thấy
    return Score{ "", "", "", 0.0, 0.0, 0.0, 0.0 };
}

void showScore(const Score& score) {
    system("cls");
    gotoxy(40, 3);
    cout << "===== THONG TIN DIEM =====" << endl;
    if (score.mssv.empty()) {
        cout << "Khong co thong tin diem cho sinh vien" << endl;
    }
    else {
        gotoxy(14, 6);
        cout << left << setw(15) << "ID";
        cout << left << setw(30) << "Course Name";
        cout << left << setw(10) << "Total";
        cout << left << setw(10) << "Final";
        cout << left << setw(10) << "Midterm";
        cout << left << setw(10) << "Other" << endl;

        ifstream file("Score.csv");
        if (!file.is_open()) {
            cout << "Khong mo duoc file Score.csv." << endl;
            return;
        }

        string line;
        getline(file, line); // Skip header line

        int row = 8;
        while (getline(file, line)) {
            stringstream ss(line);
            Score currentScore;

            getline(ss, currentScore.id, ';');
            getline(ss, currentScore.mssv, ';');
            getline(ss, currentScore.courseId, ';');
            ss >> currentScore.total;
            ss.ignore(); // Ignore the tab
            ss >> currentScore.final;
            ss.ignore(); // Ignore the tab
            ss >> currentScore.midterm;
            ss.ignore(); // Ignore the tab
            ss >> currentScore.other;

            if (currentScore.mssv == score.mssv) {
                string courseName = getCourseNameByID(currentScore.courseId);
                gotoxy(14, row);
                cout << left << setw(15) << currentScore.id;
                cout << left << setw(30) << courseName;
                cout << left << setw(10) << currentScore.total;
                cout << left << setw(10) << currentScore.final;
                cout << left << setw(10) << currentScore.midterm;
                cout << left << setw(10) << currentScore.other << endl;
                row += 2;
            }
        }

        file.close();
    }
    cin.get();
}

// Hàm để xem danh sách học sinh trong một khóa học (Câu 18 - Tuyên)
void viewEnrolledStudentsInCourse(const Course& course) {
    cout << "Danh sach hoc sinh trong khoa hoc " << course.courseName << ":" << endl;
    cout << "------------------------------------------" << endl;
    cout << "Ma sinh vien\tTen sinh vien" << endl;
    cout << "------------------------------------------" << endl;
    for (const Student& student : course.enrolledStudents) {
        cout << student.mssv << "\t\t" << student.fullName << endl;
    }
    cout << "------------------------------------------" << endl;
}

// Hàm để xem danh sách các khóa học mà sinh viên đã đăng ký
void viewEnrolledCourses2() {
    system("cls"); // Xóa màn hình console
    string semester;
    cout << "Nhap vao hoc ky muon xem : ";
    cin >> semester;
    cin.ignore();
    ifstream file("Student_course.csv"); // Mở file chứa thông tin đăng ký khóa học của sinh viên

    if (!file.is_open()) { // Kiểm tra xem file có mở thành công không
        cout << "Khong mo duoc file." << endl;
        cin.get();
        return;
    }

    // Hiển thị tiêu đề của bảng
    gotoxy(10, 6);
    cout << left << setw(10) << "ID" << setw(25) << "Course name" << setw(25) << "Class name" <<
        setw(25) << "Teacher name" << setw(8) << "Credit" << setw(12) << "Day Of Week" << setw(12) << "Session" << setw(10) << "Semester" << setw(10) << "Year" << endl;

    int row = 8; // Dòng bắt đầu để hiển thị thông tin khóa học

    string line;
    while (getline(file, line)) { // Đọc từng dòng trong file
        stringstream ss(line);
        string studentId, id;

        getline(ss, id, ';'); // Đọc mã số sinh viên
        getline(ss, studentId); // Đọc mã khóa học

        if (studentId == loggedInUserID) { // Kiểm tra xem khóa học này có phải của sinh viên đã đăng nhập không
            // Nếu là khóa học của sinh viên, thì hiển thị thông tin khóa học
            ifstream courseFile("Course.csv"); // Mở file chứa thông tin của các khóa học

            if (courseFile.is_open()) {
                string courseLine;
                while (getline(courseFile, courseLine)) {
                    stringstream courseSS(courseLine);
                    Course course;

                    getline(courseSS, course.id, ';');
                    getline(courseSS, course.courseName, ';');
                    getline(courseSS, course.className, ';');
                    getline(courseSS, course.teacherName, ';');
                    courseSS >> course.credit;
                    courseSS.ignore();
                    courseSS >> course.maxStudents;
                    courseSS.ignore();
                    getline(courseSS, course.dayOfWeek, ';');
                    getline(courseSS, course.session, ';');
                    getline(courseSS, course.semesterID, ';');
                    getline(courseSS, course.year);

                    if (course.id == id) {
                        if (course.semesterID == semester) {// Nếu mã khóa học trùng với mã khóa học trong file đăng ký
                            // Hiển thị thông tin khóa học
                            viewEnrolledStudentsInCourse(course);
                            break; // Thoát khỏi vòng lặp vì đã hiển thị thông tin của khóa học
                        }
                    }
                }
                courseFile.close();
            }
            else {
                cout << "Không mở được file" << endl;
                cin.get();
                return;
            }
        }
    }

    file.close(); // Đóng file
    cin.get(); // Dừng màn hình để người dùng có thời gian đọc thông tin
}

