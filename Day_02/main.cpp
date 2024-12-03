#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void read_reports(vector<vector<int>> &reports) {
    ifstream file("reports.txt");
    if (!file) {
        cout << "oof";
        return;
    }
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        vector<int> report;
        int num;
        while (ss >> num) {
            report.push_back(num);
        }
        reports.push_back(report);
    }
}

bool check_increasing(vector<int> &report) {
    for (size_t i = 0; i < report.size() - 1; i++) {
        if (report[i] > report[i + 1]) {
        } else return false;
    }
    return true;
}

bool check_decreasing(vector<int> &report) {
    for (size_t i = 0; i < report.size() - 1; i++) {
        if (report[i] < report[i + 1]) { continue; } else return false;
    }
    return true;
}

bool check_difference(vector<int> &report) {
    vector<int> differences;
    for (size_t i = 0; i < report.size() - 1; i++) {
        differences.push_back(abs(report[i + 1] - report[i]));
    }
    for (int diff : differences) {
        if (diff >= 1 && diff <= 3) { continue; } else return false;
    }
    return true;
}

bool problem_dampener(vector<int> &report) {

    for (size_t i = 0; i < report.size(); i++) {
        vector<int> new_report;
        new_report = report;
        new_report.erase(new_report.begin() + i);
        cout << "(trying to remove " << report[i] << " )";
        if (check_increasing(new_report) || check_decreasing(new_report)) {
            if (check_difference(new_report)) {
                cout << "\tremoved " << report[i] <<"\tchanged to\t";
                for (int level : new_report) {
                    cout << level << " ";
                }
                cout << "\t";
                return true;
            }
        }
    }
    return false;
}

bool is_safe(vector<int> report) {

    if ((check_increasing(report) || check_decreasing(report)) && check_difference(report)) {
        return true;
    } else if (problem_dampener(report)) {
        return true;
    }
    return false;
}

int main() {
    vector<vector<int>> reports;
    read_reports(reports);
    int safe_count = 0;

//    for (const auto &report : reports) {
//        for (int level : report) {
//            cout << level << " ";
//        }
//        cout << endl;
//    }

    for (const auto &report : reports) {
        for (int level : report) {
            cout << level << " ";
        }
        cout << "\t";
        if (is_safe(report)){
              safe_count++;
              cout << "is safe" << endl;
       } else cout << "is not safe" << endl;
    }
    cout <<"safe count " <<safe_count << endl;
}


