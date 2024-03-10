#include "header.h"

string formatId_course(int id) {
	// Định dạng ID thành CSCxxx
	string formattedId = "CSC";
	if (id < 10) {
		formattedId += "00";
	}
	else if (id < 100) {
		formattedId += "0";
	}
	formattedId += to_string(id);
	return formattedId;
}

bool isValidDayOfWeek(const string& dayOfWeek) {
	string validDays[] = { "MON", "TUE", "WED", "THU", "FRI", "SAT" };

	for (const string& validDay : validDays) {
		if (dayOfWeek == validDay) {
			return true;
		}
	}
	return false;
}

bool isValidSession(const string& session) {
	string validSessions[] = { "S1 (07:30)", "S2 (09:30)", "S3 (13:30)", "S4 (15:30)" };

	for (const string& validSession : validSessions) {
		if (session == validSession) {
			return true;
		}
	}
	return false; 
}

void createCourse() {
	system("cls");
	gotoxy(30, 10);

	Course course;

	cout << "Nhap ten khoa hoc: ";
	getline(cin, course.courseName);

	gotoxy(30, 12);
    cout << "Nhap ten lop: ";
    getline(cin, course.className);

	gotoxy(30, 14);
	cout << "Nhap ten giao vien: ";
	getline(cin, course.teacherName);

	gotoxy(30, 16);
	cout << "Nhap so tin chi: ";
	cin >> course.credit;

	gotoxy(30, 18);
	cout << "Nhap so luong hoc sinh toi da: ";
	cin >> course.maxStudents;

	cin.ignore();

	gotoxy(30, 20);
	cout << "Nhap ngay hoc: ";
	getline(cin, course.dayOfWeek);

	gotoxy(30, 22);
	cout << "Nhap thoi gian hoc: ";
	getline(cin, course.session);

	gotoxy(30, 24);
	cout << "Nhap hoc ki: ";
	getline(cin, course.semesterID);

	if (!isValidDayOfWeek(course.dayOfWeek)) {
		gotoxy(30, 26);
		cout << "Ngay hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
		return;
	}

	if (!isValidSession(course.dayOfWeek)) {
		gotoxy(30, 26);
		cout << "Thoi gian hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
		return;
	}

	ifstream file("Course.csv");
	if (!file.is_open()) {
		gotoxy(30, 26);
		cout << "Khong mo duoc file. Tao hoc ki that bai.";
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
	course.id = formatId_course(nextId); // Định dạng ID mới

	// Mở file để ghi nội dung mới, nhưng trong chế độ thêm vào cuối
	ofstream outFile("Course.csv", ios::app);
	if (!outFile.is_open()) {
		gotoxy(30, 26);
		cout << "Khong mo duoc file. Tao nam hoc that bai.";
		cin.get();
		return;
	}

	outFile << course.id << ';' << course.courseName << ';' << course.className << ';' << course.teacherName << ';' << course.credit 
		<< ';' << course.maxStudents << ';' << course.dayOfWeek << ';' << course.session << ';' << course.semesterID << '\n';
	outFile.close();

	gotoxy(30, 26);
	cout << "Da tao khoa hoc " << course.courseName << " voi ID " << course.id << " trong hoc ki " << course.semesterID << endl;
	cin.ignore();
	cin.get();
}