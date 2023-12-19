#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using std::vector;
using std::string;

int rand_idx(size_t len) {
    return (rand() % len);
}

void help_msg() {
    std::cout << "[Error] invalid argument.\n";
    std::cout 
        << "Usage:    rand" << "\n"
        << "          rand wn" << "\n"
        << "          rand ln" << "\n"
        << "[w] for words" << "\n"
        << "[l] for lines" << "\n"
        << "[n] is the number you want" << "\n";
}

int main(int argc, char **argv) 
{
    std::srand(time(0));

    if (argc == 1) {
        // rand word n = 1
        string word {};
        vector<string> words;
        while (std::cin >> word) {
            words.push_back(word);
        }
        std::cout << words.at(rand_idx(words.size())) << "\n";
    } else if (argc == 2) {
        if (std::regex_match(argv[1], std::regex("w+\\d+$"))) {
            // wn => rand words of n
            int num { std::stoi(string(argv[1]).erase(0, 1)) };
            string word {};
            vector<string> words;
            while (std::cin >> word) {
                words.push_back(word);
            }
            while (num--) {
                std::cout << words.at(rand_idx(words.size())) << "\n";
            }
        } else if (std::regex_match(argv[1], std::regex("l+\\d+$"))) {
            // ln => rand lines of n
            int num { std::stoi(string(argv[1]).erase(0, 1)) };
            string line {};
            vector<string> lines;
            while (std::getline(std::cin, line)) {
                lines.push_back(line);
            }
            while (num--) {
                std::cout << lines.at(rand_idx(lines.size())) << "\n";
            }
        } else {
            help_msg();
        }
    } else {
        help_msg();
    }
    return 0;
}
