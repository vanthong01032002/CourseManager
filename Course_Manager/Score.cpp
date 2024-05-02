#include "header.h"

string getCourseNameByID(const string& courseId) {
    ifstream courseFile("Course.csv");
    if (!courseFile.is_open()) {
        cout << "Khong mo duoc file Course.csv." << endl;
        return "";
    }

    string line;
    getline(courseFile, line); // Skip header line

    while (getline(courseFile, line)) {
        stringstream ss(line);
        string currentCourseId, courseName;
        getline(ss, currentCourseId, ';'); // Đọc trường CourseID
        getline(ss, courseName, ';'); // Đọc trường CourseName

        if (currentCourseId == courseId) {
            courseFile.close();
            return courseName;
        }
    }

    courseFile.close();
    return "";
}


void ShowListScore() {
    system("cls");
    gotoxy(30, 2);

    ifstream file("Score.csv");
    if (!file.is_open()) {
        cout << "Unable to open file." << endl;
        return;
    }

    ifstream courseFile("Course.csv");
    if (!courseFile.is_open()) {
        cout << "Khong the mo file Course.csv." << endl;
        return;
    }

    string line;
    getline(file, line); // Skip header line
    gotoxy(14, 6);
    cout << left << setw(10) << "ID";
    cout << left << setw(15) << "MSSV";
    cout << left << setw(30) << "Course Name";
    cout << left << setw(10) << "Total";
    cout << left << setw(10) << "Final";
    cout << left << setw(10) << "Midterm";
    cout << left << setw(10) << "Other" << endl;

    int row = 8;
    while (getline(file, line)) {
        stringstream ss(line);
        Score score;
        getline(ss, score.id, ';');
        getline(ss, score.mssv, ';');
        getline(ss, score.courseId, ';');
        ss >> score.total;
        ss.ignore(); // Ignore the tab
        ss >> score.final;
        ss.ignore(); // Ignore the tab
        ss >> score.midterm;
        ss.ignore(); // Ignore the tab
        ss >> score.other;

        string courseName = getCourseNameByID(score.courseId);

        gotoxy(14, row);
        cout << left << setw(10) << score.id;
        cout << left << setw(15) << score.mssv;
        cout << left << setw(30) << courseName;
        cout << left << setw(10) << score.total;
        cout << left << setw(10) << score.final;
        cout << left << setw(10) << score.midterm;
        cout << left << setw(10) << score.other << endl;
        row += 2;
    }

    file.close();
    _getch();
}
 
bool isMSSVExist(string mssv) {
    ifstream userFile("user.csv");
    if (!userFile.is_open()) {
        cout << "Khong mo duoc file." << endl;
        return false;
    }

    string line;
    getline(userFile, line); // Skip header line

    while (getline(userFile, line)) {
        stringstream ss(line);
        string currentMSSV;
        getline(ss, currentMSSV, ';');
        if (currentMSSV == mssv) {
            userFile.close();
            return true;
        }
    }

    userFile.close();
    return false;
}

bool isCourseIDExist(const string& courseId) {
    ifstream courseFile("Course.csv");
    if (!courseFile.is_open()) {
        cout << "Khong mo duoc file Course.csv." << endl;
        return false;
    }

    string line;
    getline(courseFile, line); // Skip header line

    while (getline(courseFile, line)) {
        stringstream ss(line);
        string currentCourseId;
        getline(ss, currentCourseId, ';'); // Đọc trường CourseID

        if (currentCourseId == courseId) {

            courseFile.close();
            return true;
        }
    }

    courseFile.close();
    return false;
}


string generateNewID() {
    ifstream scoreFile("Score.csv");
    if (!scoreFile.is_open()) {
        cout << "Khong mo duoc file." << endl;
        return "";
    }

    string lastID;
    string line;
    while (getline(scoreFile, line)) {
        stringstream ss(line);
        getline(ss, lastID, ';'); // Read ID field
    }

    scoreFile.close();

    if (lastID.empty()) {
        return "SC001";
    }
    else {
        int number = stoi(lastID.substr(2)) + 1;
        string newID = "SC" + to_string(number);
        return newID;
    }
}

bool isMSSVAndCourseIDExistInScore(string mssv, string courseId) {
    ifstream scoreFile("Score.csv");
    if (!scoreFile.is_open()) {
        cout << "Unable to open Score.csv file." << endl;
        return false;
    }

    string line;
    getline(scoreFile, line); // Skip header line

    while (getline(scoreFile, line)) {
        stringstream ss(line);
        string id, currentMSSV, currentCourseID, total, final, midterm, other;
        getline(ss, id, ';'); // Bỏ qua trường ID
        getline(ss, currentMSSV, ';'); // Đọc trường MSSV
        getline(ss, currentCourseID, ';'); // Đọc trường CourseID
        getline(ss, total, ';'); // Bỏ qua các trường khác
        getline(ss, final, ';');
        getline(ss, midterm, ';');
        getline(ss, other, ';');

        if (currentMSSV == mssv && currentCourseID == courseId) {
            scoreFile.close();
            return true;
        }
    }

    scoreFile.close();
    return false;
}

// Thêm điểm cho sinh viên
void addScore() {
    system("cls");

    gotoxy(30, 2);
    cout << "Nhap MSSV: ";
    string mssv;
    getline(cin, mssv);

    gotoxy(30, 4);
    cout << "Nhap CourseID: ";
    string courseId;
    getline(cin, courseId);

    // Kiểm tra xem MSSV có tồn tại trong user.csv hay không
    if (!isMSSVExist(mssv)) {
        gotoxy(30, 6);
        cout << "MSSV khong ton tai" << endl;
    }
    if (!isCourseIDExist(courseId)) {
        gotoxy(30, 6);
        cout << "CourseID khong ton tai" << endl;
    }
    else {
        if (isMSSVAndCourseIDExistInScore(mssv, courseId)) {
            gotoxy(30, 6);
            cout << "MSSV va CourseID da ton tai trong Score.csv. Khong the them." << endl;
        }
        else {
            double total, final, midterm, other;
            gotoxy(30, 6);
            cout << "Nhap diem tong: ";
            cin >> total;
            gotoxy(30, 8);
            cout << "Nhap diem cuoi ky: ";
            cin >> final;
            gotoxy(30, 10);
            cout << "Nhap diem giua ky: ";
            cin >> midterm;
            gotoxy(30, 12);
            cout << "Nhap diem thanh phan khac: ";
            cin >> other;

            // Tạo ID mới cho sinh viên
            string newID = generateNewID();

            // Ghi thông tin mới vào Score.csv
            ofstream scoreFile("Score.csv", ios::app);
            if (!scoreFile.is_open()) {
                gotoxy(30, 14);
                cout << "Khon mo duoc file." << endl;
                return;
            }

            scoreFile << newID << ";" << mssv << ";" << courseId << ";" << total << ";" << final << ";" << midterm << ";" << other << endl;

            scoreFile.close();

            gotoxy(30, 14);
            cout << "Them du lieu thanh cong." << endl;
        }
        
    }
    _getch();
}