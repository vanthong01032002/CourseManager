#include "header.h"

using namespace std;

// tạo năm học mới
string formatId_year(int id) {
    // Định dạng ID thành Yxxx
    string formattedId = "Y";
    if (id < 10) {
        formattedId += "00";
    }
    else if (id < 100) {
        formattedId += "0";
    }
    formattedId += to_string(id);
    return formattedId;
}

bool yearExists(const string& yearToCheck) {
    ifstream file("year.csv");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string id, year;
            getline(ss, id, ';');
            getline(ss, year, ';');

            if (year == yearToCheck) {
                file.close();
                return true; // Năm học đã tồn tại trong danh sách
            }
        }
        file.close();
    }
    return false; // Năm học chưa tồn tại trong danh sách
}

bool isValidYearFormat(const string& year) {
    // Kiểm tra xem chuỗi year có đúng định dạng (VD: 2020-2021) hay không
    if (year.length() != 9 || year[4] != '-' ||
        !isdigit(year[0]) || !isdigit(year[1]) || !isdigit(year[2]) || !isdigit(year[3]) ||
        !isdigit(year[5]) || !isdigit(year[6]) || !isdigit(year[7]) || !isdigit(year[8])) {
        return false;
    }
    return true;
}

void createYear() {
    system("cls");
    gotoxy(30, 10);
    cout << "Nhap nam hoc: ";

    string newYear;
    getline(cin, newYear);

    if (!isValidYearFormat(newYear)) {
        gotoxy(30, 12);
        cout << "Nhap sai dinh dang nam hoc. Vui long nhap lai.";
        cin.get();
        return;
    }

    ifstream file("Year.csv");
    if (!file.is_open()) {
        gotoxy(30, 12);
        cout << "Khong mo duoc file. Tao nam hoc that bai.";
        cin.get();
        return;
    }

    if (yearExists(newYear)) {
        gotoxy(30, 12);
        cout << "Nam hoc da ton tai trong danh sach. Tao nam hoc that bai.";
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
    string newId = formatId_year(nextId); // Định dạng ID mới

    // Mở file để ghi nội dung mới, nhưng trong chế độ thêm vào cuối
    ofstream outFile("Year.csv", ios::app);

    if (!outFile.is_open()) {
        gotoxy(30, 12);
        cout << "Khong mo duoc file. Tao nam hoc that bai.";
        cin.get();
        return;
    }

    // Ghi dòng dữ liệu mới vào cuối file
    outFile << newId << ';' << newYear << '\n';
    outFile.close();

    gotoxy(30, 12);
    cout << "Da tao nam hoc " << newYear << " voi ID " << newId;
    cin.get();
}