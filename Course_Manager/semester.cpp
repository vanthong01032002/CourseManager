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
}