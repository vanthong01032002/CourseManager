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

	gotoxy(30, 26);
	cout << "Nhap nam hoc: ";
	getline(cin, course.year);

	if (!isValidDayOfWeek(course.dayOfWeek)) {
		gotoxy(30, 28);
		cout << "Ngay hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
		return;
	}

	if (!isValidSession(course.dayOfWeek)) {
		gotoxy(30, 28);
		cout << "Thoi gian hoc khong hop le. Tao khoa hoc that bai.";
		cin.get();
		return;
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
		lastId = stoi(id.substr(1)); // Lấy số cuối cùng từ mã ID và chuyển thành số nguyên
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
	cin.ignore();

	uploadStudentList(course);

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
void uploadStudentList(const Course& course) {
	string fileName;
	std::cout << "Nhap ten tep CSV chua danh sach sinh vien: ";

	cin >> fileName;

	ifstream file(fileName);
	if (!file.is_open()) {
		std::cout << "Khong the mo tep. Tai len danh sach sinh vien that bai." << std::endl;
		return;
	}

	// Tạo tên tệp tin dựa trên ID của khóa học
	string studentCourseFileName = "student_course.txt";
	ofstream studentCourseFile(studentCourseFileName, ios::app); // Mở tệp để ghi thêm vào cuối

	string line;
	while (getline(file, line)) {
		// Ghi MSSV và ID của khóa học vào tệp tin
		studentCourseFile << line << "," << course.id << endl;
	}

	file.close();
	studentCourseFile.close();

	std::cout << "Danh sach sinh vien da duoc luu vao tep: " << studentCourseFileName << std::endl;
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



