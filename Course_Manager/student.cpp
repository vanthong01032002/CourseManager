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