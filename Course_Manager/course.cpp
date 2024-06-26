﻿#include "header.h"

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
	string validSessions[] = { "S1", "S2", "S3", "S4" };

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
	cout << "Nhap thoi gian hoc (S1 (07:30), S2 (09:30), S3(13:30) and S4 (15:30)): ";
	getline(cin, course.session);

	gotoxy(30, 24);
	cout << "Nhap hoc ki: ";
	getline(cin, course.semesterID);

	gotoxy(30, 26);
	cout << "Nhap nam hoc: ";
	getline(cin, course.year);

	if (!isValidDayOfWeek(course.dayOfWeek)) {
		gotoxy(30, 28);
		cout << "Ngay hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
	}

	if (!isValidSession(course.session)) {
		gotoxy(30, 28);
		cout << "Thoi gian hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
	}

	ifstream file("Course.csv");
	if (!file.is_open()) {
		gotoxy(30, 28);
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
		lastId = stoi(id.substr(3)); // Lấy số cuối cùng từ mã ID và chuyển thành số nguyên
	}

	int nextId = lastId + 1;
	course.id = formatId_course(nextId); // Định dạng ID mới

	// Mở file để ghi nội dung mới, nhưng trong chế độ thêm vào cuối
	ofstream outFile("Course.csv", ios::app);
	if (!outFile.is_open()) {
		gotoxy(30, 28);
		cout << "Khong mo duoc file. Tao nam hoc that bai.";
		cin.get();
		return;
	}

	outFile << course.id << ';' << course.courseName << ';' << course.className << ';' << course.teacherName << ';' << course.credit 
		<< ';' << course.maxStudents << ';' << course.dayOfWeek << ';' << course.session << ';' << course.semesterID << ';' <<course.year << '\n';
	outFile.close();

	gotoxy(30, 26);
	cout << "Da tao khoa hoc " << course.courseName << " voi ID " << course.id << " trong hoc ki " << course.semesterID << endl;
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
		setw(10) << "Day Of Week" << setw(10) << "Session" << setw(10) << "Semester" << setw(10) << "Year" << endl;

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
			setw(10) << course.dayOfWeek << setw(10) << course.session << setw(10) << course.semesterID << setw(10) << course.year << endl;

		row += 2; // Di chuyển xuống để hiển thị thông tin sinh viên tiếp theo
	}

	file.close();

	cin.get();
}

// Function to upload CSV file containing list of students enrolled in the course
void uploadStudentList() {
	system("cls");
	gotoxy(30, 10);

	cout << "Nhap vao CourseID: ";
	string courseID;
	getline(cin, courseID);

	gotoxy(30, 12);
	string fileName;
	cout << "Nhap ten tep CSV chua danh sach sinh vien: ";

	cin >> fileName;
	cin.ignore();

	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "Khong the mo tep. Tai len danh sach sinh vien that bai." << std::endl;
		return;
	}

	// Tạo tên tệp tin dựa trên ID của khóa học
	string studentCourseFileName = "student_course.txt";
	ofstream studentCourseFile(studentCourseFileName, ios::app); // Mở tệp để ghi thêm vào cuối

	string line;
	while (getline(file, line)) {
		// Ghi MSSV và ID của khóa học vào tệp tin
		studentCourseFile << line << "," << courseID << endl;
	}

	gotoxy(30, 14);
	cout << "Danh sach sinh vien da duoc luu vao tep: " << studentCourseFileName << endl;

	file.close();
	studentCourseFile.close();
	cin.get();
}
void updateCourseInfo() {
	system("cls");
	gotoxy(30, 10);
	cout << "===== CAP NHAT THONG TIN KHOA HOC =====" << endl;

	string courseId;
	cout << "Nhap ID cua khoa hoc can nhap thong tin: ";
	cin >> courseId;

	ifstream file("Course.csv");
	if (!file.is_open()) {
		std::cout << "Khong the mo file." << std::endl;
		cin.get();
		return;
	}

	ofstream tempFile("temp.csv");
	if (!tempFile.is_open()) {
		std::cout << "Khong the tao file tam thoi." << std::endl;
		file.close();
		cin.get();
		return;
	}

	string line;
	bool found = false;
	while (getline(file, line)) {
		// Tách dữ liệu trong dòng thành các trường
		stringstream ss(line);
		string id;
		getline(ss, id, ';');

		// So sánh ID nhập vào với ID trong file
		if (id == courseId) {
			// Nếu trùng khớp, cho phép người dùng cập nhật thông tin
			found = true;

			Course course;
			course.id = id;

			// Nhập thông tin mới từ người dùng
			cout << "Nhap ten moi cua khoa hoc: ";
			getline(cin >> ws, course.courseName);

			cout << "Nhap ten lop moi: ";
			getline(cin, course.className);

			cout << "Nhap ten giao vien moi: ";
			getline(cin, course.teacherName);

			cout << "Nhap so tin chi moi: ";
			cin >> course.credit;

			cout << "Nhap so luong hoc sinh toi da moi: ";
			cin >> course.maxStudents;

			cout << "Nhap ngay hoc moi: ";
			cin >> ws;
			getline(cin, course.dayOfWeek);

			cout << "Nhap thoi gian hoc moi: ";
			getline(cin, course.session);

			cout << "Nhap hoc ki moi: ";
			getline(cin, course.semesterID);

			cout << "Nhap nam hoc moi: ";
			getline(cin, course.year);

			// Ghi thông tin mới vào file tạm thời
			tempFile << course.id << ';' << course.courseName << ';' << course.className << ';' << course.teacherName << ';' << course.credit
				<< ';' << course.maxStudents << ';' << course.dayOfWeek << ';' << course.session << ';' << course.semesterID << ';' << course.year << '\n';
		}
		else {
			// Nếu không trùng khớp, giữ nguyên dòng thông tin và ghi vào file tạm thời
			tempFile << line << '\n';
		}
	}

	file.close();
	tempFile.close();

	// Xóa file cũ và đổi tên file tạm thành tên file gốc
	remove("Course.csv");
	rename("temp.csv", "Course.csv");
	if (!found) {
		std::cout << "Khong tim thay khoa hoc voi ID da nhap." << std::endl;

	}
	else {
		std::cout << "Thong tin khoa hoc da duoc cap nhat." << std::endl;

	}

	cin.get();
}
void addStudentToCourse() {
	system("cls");
	gotoxy(30, 10);
	cout << "===== THEM HOC VIEN VAO KHOA HOC =====" << endl;

	gotoxy(30, 12);
	string courseId;
	cout << "Nhap ID cua khoa hoc: ";
	cin >> courseId;

	ifstream courseFile("Course.csv");
	if (!courseFile.is_open()) {
		cout << "Khong the mo file." << endl;
		cin.get();
	}

	gotoxy(30, 14);
	string studentId;
	cout << "Nhap MSSV cua hoc vien: ";
	cin >> studentId;

	ifstream studentFile("studentList.csv");
	if (!studentFile.is_open()) {
		cout << "Khong the mo file." << endl;
		courseFile.close();
		cin.get();
	}

	bool courseFound = false;
	string line;
	while (getline(courseFile, line)) {
		stringstream ss(line);
		string id;
		getline(ss, id, ';');

		if (id == courseId) {
			courseFound = true;
			break;
		}
	}

	if (!courseFound) {
		cout << "Khong tim thay khoa hoc voi ID da nhap." << endl;
		courseFile.close();
		studentFile.close();
		cin.get();
	}

	// Check if student exists
	bool studentFound = false;
	while (getline(studentFile, line)) {
		stringstream ss(line);
		string id;
		getline(ss, id, ';');

		if (id == studentId) {
			studentFound = true;
			break;
		}
	}

	if (!studentFound) {
		cout << "Khong tim thay hoc vien voi MSSV da nhap." << endl;
		courseFile.close();
		studentFile.close();
		cin.get();
	}

	// Append student to course file
	ofstream outFile("student_course.csv", ios::app);
	if (!outFile.is_open()) {
		cout << "Khong the mo file." << endl;
		courseFile.close();
		studentFile.close();
		cin.get();
	}

	outFile << courseId << ';' << studentId << endl;
	outFile.close();

	cout << "Da them hoc vien voi MSSV " << studentId << " vao khoa hoc voi ID " << courseId << endl;

	courseFile.close();
	studentFile.close();
	cin.get();
	_getch();
}

//Xóa học viên
void removeStudentFromCourse() {
	system("cls");
	gotoxy(30, 10);
	cout << "===== XOA HOC VIEN RA KHOA HOC =====" << endl;

	gotoxy(30, 12);
	string courseId;
	cout << "Nhap ID cua khoa hoc: ";
	cin >> courseId;

	ifstream courseFile("Course.csv");
	if (!courseFile.is_open()) {
		cout << "Khong the mo file." << endl;
		cin.get();
		return;
	}

	bool courseFound = false;
	string line;
	while (getline(courseFile, line)) {
		stringstream ss(line);
		string id;
		getline(ss, id, ';');

		if (id == courseId) {
			courseFound = true;
			break;
		}
	}

	courseFile.close();

	if (!courseFound) {
		cout << "Khong tim thay khoa hoc voi ID da nhap." << endl;
		cin.get();
	}

	gotoxy(30, 14);
	string studentId;
	cout << "Nhap MSSV cua hoc vien can xoa: ";
	cin >> studentId;

	ifstream inFile("Student_course.csv");
	if (!inFile.is_open()) {
		cout << "Khong the mo file." << endl;
		cin.get();
	}

	vector<string> lines; // Vector lưu trữ dữ liệu không cần xóa

	bool studentFound = false;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string storedCourseId, storedStudentId;
		getline(ss, storedCourseId, ';');
		getline(ss, storedStudentId);

		if (storedCourseId == courseId && storedStudentId == studentId) {
			studentFound = true;
		}
		else {
			lines.push_back(line); // Thêm dòng này vào vector nếu không phải dòng cần xóa
		}
	}

	inFile.close();

	if (!studentFound) {
		cout << "Khong tim thay hoc vien voi MSSV da nhap trong khoa hoc." << endl;
		cin.get();
	}

	ofstream outFile("student_course.csv");
	if (!outFile.is_open()) {
		cout << "Khong the mo file." << endl;
		cin.get();
	}

	// Ghi lại toàn bộ dữ liệu từ vector vào file student_course.csv
	for (const string& line : lines) {
		outFile << line << endl;
	}

	outFile.close();

	cout << "Da xoa hoc vien voi MSSV " << studentId << " ra khoa hoc voi ID " << courseId << endl;
	cin.get();
	_getch();
}

void removeCourse() {
	system("cls");
	gotoxy(30, 10);
	cout << "===== XOA KHOA HOC =====" << endl;

	gotoxy(30, 12);
	string courseId;
	cout << "Nhap ID cua khoa hoc can xoa: ";
	cin >> courseId;
	cin.ignore();

	ifstream inFile("Course.csv");
	if (!inFile.is_open()) {
		cout << "Khong the mo file." << endl;
		cin.get();
		return;
	}

	ofstream tempFile("temp.csv");
	if (!tempFile.is_open()) {
		cout << "Khong the tao file tam thoi." << endl;
		inFile.close();
		cin.get();
		return;
	}

	string line;
	bool courseFound = false;
	while (getline(inFile, line)) {
		stringstream ss(line);
		string id;
		getline(ss, id, ';');

		if (id == courseId) {
			courseFound = true;
		}
		else {
			tempFile << line << endl;
		}
	}

	inFile.close();
	tempFile.close();

	if (!courseFound) {
		cout << "Khong tim thay khoa hoc voi ID da nhap." << endl;
		remove("temp.csv");
		cin.get();
		return;
	}

	remove("Course.csv");
	rename("temp.csv", "Course.csv");

	cout << "Da xoa khoa hoc voi ID " << courseId << endl;
	cin.get();
}




