#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

const string FULL { "full_path" };
const string RELATIVE { "relative_path" };
const string FIL { "file" };
const string DIR { "directory" };
const string OTH { "other" };

struct File {
    string path;
    string type;
};

bool compareFiles(const File &a, const File &b) {
    return a.path < b.path;
}

// get a list of all files
vector<File> list_files(string _path, string _type) {
    vector<File> files;
    for (const auto &entry : fs::directory_iterator(_path)) {
        File cur;
        if (fs::is_directory(entry.status()))
            cur.type = DIR;
        else if (fs::is_regular_file(entry.status()))
            cur.type = FIL;
        else
            cur.type = OTH;

        string full_path = entry.path().string();
        if (_type == FULL)
            cur.path = full_path;
        else if (_type == RELATIVE) {
            string relative_path = full_path.substr(_path.length() + 1);
            cur.path = relative_path;
        }
        else 
            throw std::invalid_argument("[Error] path types: 'FULL', 'RELATIVE'\n");

        files.push_back(cur);
    }
    std::sort(files.begin(), files.end(), compareFiles);
    return files;
}

// printing
void print(vector<File> &_files_list, string _path_type) {
    if (_path_type == RELATIVE) {
        for (const auto &file : _files_list) {
            if (file.type == DIR)
                std::cout << "\033[34m" << file.path << "\033[0m  ";  // Blue for directories
            else if (file.type == OTH)
                std::cout << "\033[32m" << file.path << "\033[0m  ";  // Green for other types
            else
                std::cout << file.path << "  ";
        }
        std::cout << "\n";
    }
    else {
        for (const auto &file : _files_list) {
            if (file.type == DIR)
                std::cout << "\033[34m" << file.path << "\033[0m\n";  // Blue for directories
            else if (file.type == OTH)
                std::cout << "\033[32m" << file.path << "\033[0m\n";  // Green for other types
            else
                std::cout << file.path << "\n";
        }
    }
}

int main(int argc, char *argv[]) 
{
    string path { fs::current_path() };
    string print_type { RELATIVE };

    if (argc == 1);
    else if (argc == 2) {
        if (strcmp(argv[1], "-l") == 0)
            print_type = FULL;
        else
            path = argv[1];
    }
    else if (argc == 3) {
        path = argv[2];
        if (strcmp(argv[1], "-l") == 0)
            print_type = FULL;
    }
    else
        throw std::invalid_argument("[Error] no more than 2 argument\nls [option] <file_path>\n");

    auto files_paths { list_files(path, RELATIVE) };
    print(files_paths, print_type);

    return 0;
}
