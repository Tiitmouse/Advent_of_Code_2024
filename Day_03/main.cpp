//
// Created by Lorena Kovačić on 03.12.2024..
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

void read_memory(string &corrupted_memory) {
    ifstream file("corrupted_memory.txt");
    if (!file) {
        cout << "corrupted memory not found";
        return;
    }
    stringstream ss;
    ss << file.rdbuf();
    corrupted_memory = ss.str();
}

void find_valid_muls (string &corrupted_memory, vector<string> &valid_muls) {
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch matches;

    auto begin = sregex_iterator(corrupted_memory.begin(), corrupted_memory.end(), pattern);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        valid_muls.push_back(match.str());
    }
}

void find_valid_muls_by_instruction (string &corrupted_memory, vector<string> &valid_muls_by_instruction) {
    regex pattern(R"((mul\((\d{1,3}),(\d{1,3})\))|do\(\)|don't\(\))");
    smatch matches;
    bool add_muls = true;

    auto begin = sregex_iterator(corrupted_memory.begin(), corrupted_memory.end(), pattern);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        string match_str = match.str();

        if (match_str == "do()") {
            add_muls = true;
        } else if (match_str == "don't()") {
            add_muls = false;
        } else if (add_muls) {
            valid_muls_by_instruction.push_back(match_str);
        }
    }
}

int calculate_instructions(vector<string> &valid_muls) {
    int result = 0;
    for (string &mul: valid_muls) {
        int x = stoi(mul.substr(4, mul.find(',')));
        int y = stoi(mul.substr(mul.find(',') + 1, mul.find(')')));
        mul = "mul(" + to_string(x * y) + ")";
        result += x * y;
    }
    return result;
}

int main() {
    string corrupted_memory;
    vector<string> valid_muls;
    vector<string> valid_muls_by_instruction;
    read_memory(corrupted_memory);
    find_valid_muls(corrupted_memory, valid_muls);
    cout << "Calculated result: " << calculate_instructions(valid_muls) << endl;
    find_valid_muls_by_instruction(corrupted_memory, valid_muls_by_instruction);
    cout << "Calculated result(with instructions): " << calculate_instructions(valid_muls_by_instruction) << endl;


    return 0;
}