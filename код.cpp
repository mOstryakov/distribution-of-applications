#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <random>
#include <io.h>
#include <filesystem> 



using namespace std;

int n = 34, m = 11;
int m2 = 11, n2 = 34;
int m1 = 7, n1 = 6;
int kl = 1;
int hg = 7;
int m3 = 5, n3 = 34;
int srtime = 5000;

vector<vector<string>> arr;

void QuickSort(int l, int r) {
    int i = l, j = r;
    int g = stoi(arr[(l + r) / 2][1]);
    while (i <= j) {
        while (stoi(arr[i][1]) < g) i++;
        while (stoi(arr[j][1]) > g)  j--;
        if (i <= j) {
            swap(arr[i][1], arr[j][1]);
            swap(arr[i][0], arr[j][0]);
            swap(arr[i][2], arr[j][2]);
            swap(arr[i][3], arr[j][3]);
            swap(arr[i][4], arr[j][4]);
            i++; 
            j--;
        }
    }
    if (l < j)QuickSort(l, j);
    if (i < r)QuickSort(i, r);
}

random_device rd;
mt19937 gen(rd());
int random(int low, int high) {
    uniform_int_distribution<> dist(low, high);
    return dist(gen);
}

vector<vector<string>>final_distribution(35, vector<string>(4));

bool FuncTime(string time, string fio) {
    string hour1;
    string min1;
    for (int i = n; i > 0; i--) {
        if (fio == final_distribution[i][0]) {
            string x = final_distribution[i][3];
            if (x.size() == 15) {
                hour1 = x.substr(11, 1);
                min1 = x.substr(13, 2);
                break;
            }
            else if (x.size() == 16) {
                hour1 = x.substr(11, 2);
                min1 = x.substr(14, 2);
                break;
            }
        }
        if (fio != final_distribution[i][0] && i < 3)return true;
        
    }
    string hour;
    string min;
    if (time.size() == 15) {
        hour = time.substr(11, 1);
        min = time.substr(13, 2);
    }
    else if (time.size() == 16) {
        hour = time.substr(11, 2);
        min = time.substr(14, 2);
    }

    if (stoi(hour1) * 3600 + stoi(min1) * 60 + srtime < stoi(hour) * 3600 + stoi(min) * 60)return true;
    else return false;
}

bool FuncDest(string fio) {
    int k = 0;
    for (int i = 1; i < n; i++) {
        if (final_distribution[i][0] == fio && final_distribution[i][2]=="0")k++;
    }
    if (k <= 3)return true;
    else return false;
}

vector<vector<string>>list1(n1, vector<string>(m1));

int FuncSerchNum(string fio) {
    for (int o = 1; o < n1; o++) {
        if (fio == list1[o][0]) {
            return o;
            break;
        }
    }
}

string FuncTimePer(string time) {
    string hour;
    string min;
    string date = time.substr(0, 10);
    if (time.size() == 15) {
        hour = time.substr(11, 1);
        min = time.substr(13, 2);
    }
    if (time.size() == 16) {
        hour = time.substr(11, 2);
        min = time.substr(14, 2);
    }
    string min_result;
    string hour_result;
    string result;
    min_result = to_string(stoi(min) + random(2, 9));
    if (stoi(min_result) <= 59) {
        result = date + " " + hour + ":" + min_result;
    }
    else if (stoi(min_result) > 59) {
        if (min_result == "60") {
            min_result = "00";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "61") {
            min_result = "01";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "62") {
            min_result = "02";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "63") {
            min_result = "03";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "64") {
            min_result = "04";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "65") {
            min_result = "05";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "66") {
            min_result = "06";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "67") {
            min_result = "07";
            hour_result = to_string(stoi(hour) + 1);
        }
        if (min_result == "68") {
            min_result = "08";
            hour_result = to_string(stoi(hour) + 1);
        }
        result = date + " " + hour_result + ":" + min_result;
    }
    return result;
}

int main() {

    setlocale(LC_ALL, "Russian");

    int l = 0;
    vector<vector<string>>list(n, vector<string>(m));
    ifstream file("таблица заявок csv.csv");
    string line;
    for (int i = 0; i < n; i++) {
        getline(file, line);
        for (int j = 0; j < m; j++) {
            line = line.substr(l, line.size() - l);
            int r = line.find(";");
            list[i][j] = line.substr(0, r);
            l = r + 1;
        }
    }
    
    int l1 = 0;
    ifstream file1("Таблица сотрудников новое (сотрудники).csv");
    string line1;
    for (int i = 0; i < n1; i++) {
        getline(file1, line1);
        for (int j = 0; j < m1; j++) {
            line1 = line1.substr(l1, line1.size() - l1);
            int r1 = line1.find(";");
            list1[i][j] = line1.substr(0, r1);
            l1 = r1 + 1;
        }
    }

    vector<vector<string>>list2(n2, vector<string>(m2));
    ifstream file2("Таблица сотрудников (выполнение заявок) csv.csv");
    string line2;

    int l2 = 0;
    for (int i = 0; i < n2; i++) {
        getline(file2, line2);
        for (int j = 0; j < m2; j++) {
            line2 = line2.substr(l2, line2.size() - l2);
            int r2 = line2.find(";");
            list2[i][j] = line2.substr(0, r2);
            l2 = r2 + 1;
        }
    }

    vector<vector<string>>q(n3, vector<string>(m3));

    q[0][0] = "Тип заявки";
    q[0][1] = "Среднее время";
    q[0][2] = "Фамилия Имя Отчество";
    q[0][3] = "Сумма";
    q[0][4] = "Количество";

    int t = 0;
    for (int i = 1; i < n2; i++) {
        int k = 0;
        t = 0;
        while (true) {
            if (list2[i][0] == q[k][2] && list2[i][7] == q[k][0]) {
                q[k][3] = to_string(stoi(q[k][3]) + stoi(list2[i][10]));
                q[k][4] = to_string(1 + stoi(q[k][4]));
                q[k][1] = to_string(stoi(q[k][3]) / stoi(q[k][4]));
                break;
            }
            else {
                k++;
                t++;
            }

            if (q[k][2] == "") {
                q[k][3] = "0";
                q[k][4] = "0";
                q[k][1] = "0";
                q[k][2] = list2[i][0];
                q[k][0] = list2[i][7];
                q[k][3] = to_string(stoi(q[k][3]) + stoi(list2[i][10]));
                q[k][4] = to_string(stoi(q[k][4]) + 1);
                q[k][1] = to_string(stoi(q[k][3]) / stoi(q[k][4]));

                break;
            }

        }
    }

    arr = q;
    QuickSort(1, t);

    ofstream fil("Среднее время.csv");
    for (int i = 0; i <= t; i++)
        fil << arr[i][0] << ';' << arr[i][1] << ';' << arr[i][2] << ';' << arr[i][3] << ';' << arr[i][4] << '\n';
    
    final_distribution[0][0] = "Фамилия Имя Отчество";
    final_distribution[0][1] = "Тип заявки";
    final_distribution[0][2] = "Статус заявки";
    final_distribution[0][3] = "Дата и время поступления";

    for (int i = 1; i < n; i++) {
        final_distribution[i][0] = "0";
        final_distribution[i][1] = "1";
        final_distribution[i][2] = "2";
        final_distribution[i][3] = "3";
    }

    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= t; j++) {
            
            if (list[i][9] == arr[j][0] && FuncDest(arr[j][2]) == true && FuncTime(list[i][10], arr[j][2]) == true) {
                final_distribution[kl][0] = arr[j][2];
                final_distribution[kl][1] = list[i][9];
                final_distribution[kl][2] = "1";
                final_distribution[kl][3] = list[i][10];
                kl++;
                break;
            }

            else if (j == t && FuncTime(list[i][10], arr[j][2]) == true) {
                final_distribution[kl][0] = arr[j][2];
                final_distribution[kl][1] = list[i][9];
                final_distribution[kl][2] = "1";
                final_distribution[kl][3] = list[i][10];
                kl++;
                break;
            }
            else if (j == t && FuncTime(list[i][10], arr[j][2]) == false) {
                if (hg == t)hg = 7;
                final_distribution[kl][0] = arr[hg][2];
                final_distribution[kl][1] = list[i][9];
                final_distribution[kl][2] = "1";
                final_distribution[kl][3] = list[i][10];
                hg++;
                kl++;
                break;
            }
        }
    }
    
    vector<vector<string>>finaly(n, vector<string>(m));
    finaly[0][0] = "Фамилия Имя Отчество";
    finaly[0][1] = "Дата рождения";
    finaly[0][2] = "Филиал";
    finaly[0][3] = "Подразделение";
    finaly[0][4] = "Отдел";
    finaly[0][5] = "Должность";
    finaly[0][6] = "Стаж работы";
    finaly[0][7] = "Тип заявки";
    finaly[0][8] = "Дата и время поступления";
    finaly[0][9] = "Начало рассмотрения";
    finaly[0][10] = "Длительность рассмотрения, сек";

    for (int i = 1; i < n; i++) {
        finaly[i][0] = final_distribution[i][0];
        int u = FuncSerchNum(finaly[i][0]);
        finaly[i][1] = list1[u][1];
        finaly[i][2] = list1[u][2];
        finaly[i][3] = list1[u][3];
        finaly[i][4] = list1[u][4];
        finaly[i][5] = list1[u][5];
        finaly[i][6] = list1[u][6];
        finaly[i][7] = final_distribution[i][1];
        finaly[i][8] = list[i][10];
        finaly[i][9] = FuncTimePer(final_distribution[i][3]);
        finaly[i][10] = to_string(random(180, 900) * 10);
    }
    ofstream fina("Итог.csv");
    for (int i = 0; i < n; i++) {
        fina << finaly[i][0] << ";" << finaly[i][1] << ";" << finaly[i][2] << ";" << 
            finaly[i][3] << ";" << finaly[i][4] << ";" << finaly[i][5] << ";" << 
            finaly[i][6] << ";" << finaly[i][7] << ";" << finaly[i][8] << ";" << 
            finaly[i][9] << ";" << finaly[i][10]<<"\n";
    }

    cout << "Норма заявок: 100" << "\n";
    cout << "Количество заявок: 33" << "\n";
    cout << "Максимальное количество заявок у одного сотрудника: 3";
} 