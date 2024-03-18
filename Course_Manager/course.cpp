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

void showListCourse() {
	system("cls");
	gotoxy(36, 4);
	cout << "Danh sach khoa hoc" << endl;

	ifstream file("Course.csv");

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
	gotoxy(10, 6);
	cout << left << setw(10) << "ID" << setw(25) << "Course name" << setw(25) << "Class name" <<
		setw(25) << "Teacher name" << setw(8) << "Credit" << setw(12) << "Max students" <<
		setw(10) << "Day Of Week" << setw(10) << "Session" << setw(10) << "Semester" << endl;

	int row = 8;

	// Đọc và hiển thị thông tin từ file
	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		Course course;

		// Trích xuất thông tin của lớp học từ dòng CSV
		getline(ss, course.id, ';');
		getline(ss, course.courseName, ';');
		getline(ss, course.className, ';');
		getline(ss, course.teacherName, ';');
		ss >> course.credit;
		ss.ignore(); // Ignore the semicolon
		ss >> course.maxStudents;
		ss.ignore(); // Ignore the semicolon
		getline(ss, course.dayOfWeek, ';');
		getline(ss, course.session, ';');
		getline(ss, course.semesterID, ';');

		// Hiển thị thông tin sinh viên
		gotoxy(10, row);
		cout << left << setw(10) << course.id << setw(25) << course.courseName << setw(25) << course.className <<
			setw(25) << course.teacherName << setw(8) << course.credit << setw(12) << course.maxStudents <<
			setw(10) << course.dayOfWeek << setw(10) << course.session << setw(10) << course.semesterID << endl;

		row += 2; // Di chuyển xuống để hiển thị thông tin sinh viên tiếp theo
	}

	file.close();

	cin.get();
}

// m làm rồi thì xóa này đi nha
void updateCourseInfo() {
	//system("cls");
	//gotoxy(36, 2);
	//ifstream file("course.csv");
	//if (!file.is_open()) {
	//	cout << "Khong mo duoc file." << endl;
	//	return;
	//}

	//string line;
	//getline(file, line); // Skip header line

	//string searchID;
	//gotoxy(36, 2);
	//cout << "Nhap ID cua khoa hoc ban muon cap nhat: ";
	//cin >> searchID;


	//bool found = false;
	//Course course;

	//while (getline(file, line)) {
	//	stringstream ss(line);
	//	getline(ss, course.id, ';');
	//	getline(ss, course.courseName, ';');
	//	getline(ss, course.className, ';');
	//	getline(ss, course.teacherName, ';');
	//	ss >> course.credit;
	//	ss.ignore(); // Ignore the semicolon
	//	ss >> course.maxStudents;
	//	ss.ignore(); // Ignore the semicolon
	//	getline(ss, course.dayOfWeek, ';');
	//	getline(ss, course.session, ';');
	//	getline(ss, course.semesterID, ';');

	//	if (course.id == searchID) {
	//		found = true;
	//		break;
	//	}
	//}

	//file.close();

	//if (!found) {
	//	gotoxy(36, 4);
	//	cout << "ID khoa hoc khong ton tai." << endl;
	//}
	//else {
	//	// Display current course info
	//	gotoxy(30, 4);
	//	cout << "Current information for course " << course.id << ":" << endl;
	//	gotoxy(30, 5);
	//	cout << "Course Name: " << course.courseName << endl;
	//	gotoxy(30, 6);
	//	cout << "Class Name: " << course.className << endl;
	//	gotoxy(30, 7);
	//	cout << "Teacher Name: " << course.teacherName << endl;
	//	gotoxy(30, 8);
	//	cout << "Credit: " << course.credit << endl;
	//	gotoxy(30, 9);
	//	cout << "Max Students: " << course.maxStudents << endl;
	//	gotoxy(30, 10);
	//	cout << "Day of Week: " << course.dayOfWeek << endl;
	//	gotoxy(30, 11);
	//	cout << "Session: " << course.session << endl;
	//	gotoxy(30, 12);
	//	cout << "Semester ID: " << course.semesterID << endl;

	//	// Allow user to update info
	//	gotoxy(30, 14);
	//	cout << "Nhap thong tin moi" << endl;
	//	gotoxy(30, 15);
	//	cout << "New Course Name: ";
	//	cin.ignore(); // Ignore the newline character left in the buffer
	//	getline(cin, course.courseName);
	//	gotoxy(30, 16);
	//	cout << "New Class Name: ";
	//	getline(cin, course.className);
	//	gotoxy(30, 17);
	//	cout << "New Teacher Name: ";
	//	getline(cin, course.teacherName);
	//	gotoxy(30, 18);
	//	cout << "New Credit: ";
	//	cin >> course.credit;
	//	gotoxy(30, 19);
	//	cout << "New Max Students: ";
	//	cin >> course.maxStudents;

	//	gotoxy(30, 20);
	//	cout << "New Day of Week: ";
	//	getline(cin, course.dayOfWeek);

	//	gotoxy(30, 21);
	//	cout << "New Session: ";
	//	getline(cin, course.session);
	//	gotoxy(30, 22);
	//	cout << "New Semester ID: ";
	//	getline(cin, course.semesterID);

	//	// Update course info in file
	//	ofstream outFile("course.csv");
	//	if (!outFile.is_open()) {
	//		cout << "Khong the mo file." << endl;
	//		return;
	//	}

	//	outFile << "ID;CourseName;ClassName;TeacherName;Credit;MaxStudents;DayOfWeek;Session;SemesterID" << endl;
	//	outFile << course.id << ";" << course.courseName << ";" << course.className << ";" << course.teacherName << ";" << course.credit << ";" << course.maxStudents << ";" << course.dayOfWeek << ";" << course.session << ";" << course.semesterID << endl;

	//	outFile.close();
	//	gotoxy(30, 30);
	//	cout << "Thong Tin khoa hoc cap nhat thanh cong." << endl;
	//}

	//
	//_getch();
}