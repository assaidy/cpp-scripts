#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// split by any type of spaces [another way of counting words]
// split then count
std::vector<std::string> split_str_by_sp(const std::string &str) {
    std::string token;
    std::vector<std::string> result;
    for (size_t i = 0; i < str.size(); i++) {
        if (isprint(str.at(i)) && str.at(i) != ' ') {
            token += str.at(i);
        } else {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        }
    }
    if (!token.empty()) {
        result.push_back(token);
    }
    return result;
}

void help_msg() {
    cout << "[Error] invalide argument.\n"
        << "Usage: wcount [OPTION] [PATH]\n"
        << "\t-c             char counts\n"
        << "\t-w             word counts\n"
        << "\t-l             line counts\n"
        << "\t-b             byte counts\n"
        << "\t-h, --help     help message\n";
}

unsigned count_chars(std::fstream &file) {
    char c;
    unsigned char_cnt {};
    while (file.get(c)) {
        char_cnt++;
    }
    return char_cnt;
}

unsigned count_lines(std::fstream &file) {
    string line;
    unsigned line_cnt {};
    while (getline(file, line)) {
        line_cnt++;
    }
    return line_cnt;
}

unsigned count_words(std::fstream &file) {
    string line;
    string word;
    unsigned word_cnt {};
    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> word)
            word_cnt++;
    }
    return word_cnt;
}

int main(int argc, char *argv[])
{
    if (argc == 3) {
        string mode {argv[1]};
        string path {argv[2]};
        std::fstream file_handler(path.c_str());
        if (file_handler.fail()) {
            cout << "[Error] can't open file.\n";
            return 1;
        } else {
            // char counts
            if (mode == "-c") {
                cout << count_chars(file_handler) << "\n";
            }
            // word counts
            else if (mode == "-w") {
                cout << count_words(file_handler) << "\n";
            }
            // line counts
            else if (mode == "-l") {
                cout << count_lines(file_handler) << "\n";
            }
            // byte counts
            else if (mode == "-b") {
                // each char is 1 byte in ASCII/UTF-8
                cout << count_chars(file_handler) << "\n";
            }
            else {
                help_msg();
                return 1;
            }
        }
        file_handler.close();
    } else {
        help_msg();
        return 1;
    }
    return 0;
}
