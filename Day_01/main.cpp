#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void read_locations(vector<int> &group_1, vector<int> &group_2) {
    ifstream file("location_ids.txt");
    if (!file) {
        cout << "oof";
        return;
    }
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        int num1, num2;
        ss >> num1 >> num2;
        group_1.push_back(num1);
        group_2.push_back(num2);
    }
    sort(group_1.begin(), group_1.end());
    sort(group_2.begin(), group_2.end());
}

void calculate_total_distance(vector<int> &group_1, vector<int> &group_2) {
    int total_distance = 0;
    for (int i = 0; i < group_1.size(); i++) {
        total_distance += abs(group_1[i] - group_2[i]);
    }
    cout << "Total distance: " << total_distance << endl;
}

void calculate_similarity_score(vector<int> &group_1, vector<int> &group_2) {
    int similarity_score = 0;
    for (int i = 0; i < group_1.size(); i++) {
        int number_of_appearances = 0;
        for (int j = 0; j < group_2.size(); j++) {
            if (group_1[i] == group_2[j]) {
                number_of_appearances++;
            }
        }
        if (number_of_appearances != 0) {
            similarity_score += group_1[i] * number_of_appearances;
        }
    }
    cout << "Similarity score: " << similarity_score << endl;
}

int main() {
    vector<int> group_1; // {3, 4, 2, 1, 3, 3};
    vector<int> group_2; // {4, 3, 5, 3, 9, 3};
    read_locations(group_1, group_2);
    calculate_total_distance(group_1, group_2);
    // 1882714
    calculate_similarity_score(group_1, group_2);
    // 19437052
    return 0;
    // code to maybe join 4214237-2e829851
}


