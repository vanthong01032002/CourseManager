#include "header.h"

using namespace std;

//Tạo học kì
bool isValidSemester(int semesterNumber) {
    return (semesterNumber >= 1 && semesterNumber <= 3);
}

string formatId_semester(int id) {
    // Định dạng ID thành Sxxx
    string formattedId = "S";
    if (id < 10) {
        formattedId += "00";
    }
    else if (id < 100) {
        formattedId += "0";
    }
    formattedId += to_string(id);
    return formattedId;
}

// Kiểm tra xem học kỳ mới tạo của năm học đã tồn tại chưa
bool isSemesterExists(const int& semester, const string& academicYear) {
    ifstream file("Semester.csv");
    if (!file.is_open()) {
        cerr << "Khong mo duoc file Semester.csv.\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string semesterId, semesterNumber, year;

        getline(ss, semesterId, ';');
        getline(ss, semesterNumber, ';');
        getline(ss, year, ';');

        if (semesterNumber == to_string(semester) && year == academicYear) {
            file.close();
            return true; // Năm học đã tồn tại
        }
    }

    file.close();
    return false; // Không tìm thấy năm học trong danh sách học kỳ
}

void createSemester() {
    system("cls");
    gotoxy(30, 10);

    int semesterNumber;
    string academicYear;
    Date startDate, endDate;
    string startInput, endInput;

    cout << "Nhap hoc ki: ";
    cin >> semesterNumber;

    cin.ignore();

    gotoxy(30, 12);
    cout << "Nhap nam hoc: ";
    getline(cin, academicYear);

    gotoxy(30, 14);
    cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
    getline(cin, startInput);

    gotoxy(30, 16);
    cout << "Nhap ngay ket thuc (dd/mm/yyyy): ";
    getline(cin, endInput);

    // Phân tích chuỗi nhập vào để lấy ngày, tháng và năm
    sscanf_s(startInput.c_str(), "%d/%d/%d", &startDate.day, &startDate.month, &startDate.year);
    sscanf_s(endInput.c_str(), "%d/%d/%d", &endDate.day, &endDate.month, &endDate.year);

    if (!isValidYearFormat(academicYear)) {
        gotoxy(30, 18);
        cout << "Nhap sai dinh dang nam hoc. Tao hoc ki that bai.";
        cin.get();
        return;
    }

    if (!isValidSemester(semesterNumber)) {
        gotoxy(30, 18);
        cout << "Nhap sai dinh dang nam hoc. Tao hoc ki that bai.";
        cin.get();
        return;
    }

    ifstream file("Semester.csv");
    if (!file.is_open()) {
        gotoxy(30, 18);
        cout << "Khong mo duoc file. Tao hoc ki that bai.";
        cin.get();
        return;
    }

    if (yearExists(academicYear) == false) {
        gotoxy(30, 18);
        cout << "Nam hoc khong ton tai trong danh sach. Tao hoc ki that bai.";
        cin.get();
        return;
    }

    // Kiểm tra xem thời gian bắt đầu và kết thúc học kỳ có nằm trong khoảng thời gian của năm học không
    int hyphenPosition = academicYear.find('-');
    int startYear = stoi(academicYear.substr(0, hyphenPosition));
    int endYear = stoi(academicYear.substr(hyphenPosition + 1));

    if (startDate.year < startYear || endDate.year > endYear) {
        gotoxy(30, 18);
        cout << "Thoi gian bat dau va ket thuc hoc ky khong nam trong nam hoc. Tao hoc ki that bai.";
        cin.get();
        return;
    }

    // Kiểm tra xem học kỳ này của năm học đã tồn tại chưa
    if (isSemesterExists(semesterNumber, academicYear)) {
        gotoxy(30, 18);
        cout << "Hoc ky cho nam hoc nay da ton tai. Tao hoc ky that bai.";
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
    string newId = formatId_semester(nextId); // Định dạng ID mới

    // Mở file để ghi nội dung mới, nhưng trong chế độ thêm vào cuối
    ofstream outFile("Semester.csv", ios::app);

    if (!outFile.is_open()) {
        gotoxy(30, 18);
        cout << "Khong mo duoc file. Tao nam hoc that bai.";
        cin.get();
        return;
    }

    // Ghi dòng dữ liệu mới vào cuối file
    string _startDate = to_string(startDate.day) + "/" + to_string(startDate.month) + "/" + to_string(startDate.year);
    string _endDate = to_string(endDate.day) + "/" + to_string(endDate.month) + "/" + to_string(endDate.year);

    outFile << newId << ';' << semesterNumber << ';' << academicYear << ';' << _startDate << ';' << _endDate << '\n';
    outFile.close();

    gotoxy(30, 18);
    cout << "Da tao hoc ki " << semesterNumber << " voi ID " << newId << " trong nam hoc " << academicYear << endl;
    cin.ignore();
    cin.get();
    _getch();
}

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

bool isMSSVInStudentClass(const string& mssv) {
    ifstream studentClassFile("Student_class.csv");

    if (studentClassFile.is_open()) {
        string line;
        while (getline(studentClassFile, line)) {
            stringstream ss(line);
            string studentMSSV;
            getline(ss, studentMSSV, ';');
            if (studentMSSV == mssv) {
                studentClassFile.close();
                return true;
            }
        }
        studentClassFile.close();
    }

    return false;
}

void addStudentToClass() {
    system("cls");
    gotoxy(36, 4);
    cout << "Them sinh vien vao lop hoc" << endl;

    string mssv, className;
    bool retry = false;

    do {
        if (retry) {
            gotoxy(36, 10); 
            cout << "MSSV da ton tai trong Student_class.csv. Vui long nhap lai." << endl;
        }

        gotoxy(36, 8);
        cout << "Nhap MSSV sinh vien: ";
        getline(cin, mssv);

        retry = isMSSVInStudentClass(mssv);
    } while (retry);
    gotoxy(36, 10);
    cout << "                                                                                                                ";
    gotoxy(36, 10);
    cout << "Nhap ten lop hoc: ";
    getline(cin, className);

    bool studentFound = false, classFound = false;
    string studentFullName;

    // Check if the student exists in user.csv
    ifstream userFile("user.csv");
    if (userFile.is_open()) {
        string line;
        getline(userFile, line); // skip header
        while (getline(userFile, line)) {
            stringstream ss(line);
            string mssvRead, fullName;
            getline(ss, mssvRead, ';');
            getline(ss, fullName, ';');
            if (mssvRead == mssv) {
                studentFound = true;
                studentFullName = fullName;
                break;
            }
        }
        userFile.close();
    }

    // Check if the class exists in class.csv
    ifstream classFile("class.csv");
    if (classFile.is_open()) {
        string line;
        getline(classFile, line); // skip header
        while (getline(classFile, line)) {
            stringstream ss(line);
            string classId, classNameRead;
            getline(ss, classId, ';');
            getline(ss, classNameRead, ';');
            if (classNameRead == className) {
                classFound = true;
                break;
            }
        }
        classFile.close();
    }

    if (!studentFound) {
        gotoxy(30, 14);
        cout << "Khong tim thay sinh vien co MSSV: " << mssv << endl;
        gotoxy(30, 16);
        cout << "Them sinh vien vao lop hoc that bai." << endl;
        cin.get();
        return;
    }

    if (!classFound) {
        gotoxy(30, 14);
        cout << "Khong tim thay lop hoc co ten: " << className << endl;
        gotoxy(30, 16);
        cout << "Them sinh vien vao lop hoc that bai." << endl;
        cin.get();
        return;
    }

    ifstream studentClassFile("Student_class.csv");

    if (studentClassFile.is_open()) {
        string line;
        getline(studentClassFile, line); // Loại bỏ dòng tiêu đề
        while (getline(studentClassFile, line)) {
            stringstream ss(line);
            string currentMSSV, currentClassName;
            getline(ss, currentMSSV, ',');
            getline(ss, currentClassName, ',');
            if (currentMSSV == mssv) {
                gotoxy(30, 14);
                cout << "Sinh vien da ton tai trong lop hoc." << endl;
                studentClassFile.close();
                return;
            }
        }
        studentClassFile.close();
    }

    ofstream studentClassOut("Student_class.csv", ios::app);
    if (studentClassOut.is_open()) {
        studentClassOut << mssv << ';' << className << ';' << studentFullName << '\n';
        studentClassOut.close();
        cout << "Them sinh vien vao lop hoc thanh cong." << endl;
    }
    else {
        cout << "Khong mo duoc file Student_class.csv." << endl;
    }

    cin.get();
    _getch();
}