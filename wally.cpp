#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

// get a list of all files
vector<string> get_dir_files(string path) {
    vector<string> files;
    for (const auto &entry : fs::directory_iterator(path))
        files.push_back(entry.path());
    return files;
}

// get a random file
string get_rand_file(vector<string> files) {
    srand(time(0));
    return files.at(rand() % files.size());
}

int main()
{
    // declare the path
    string HOME { getenv("HOME") };
    string path { HOME + "/Pictures/walls" };

    // get all files
    auto files { get_dir_files(path) };

    // print random file
    string choosen_bg { get_rand_file(files) };

    // set as background
    const auto feh_cmd { "feh --bg-fill " + choosen_bg };
    system(feh_cmd.c_str());

    // set pywal
    // const auto pywal_cmd { "wal -i " + choosen_bg };
    // system(pywal_cmd.c_str());

    // set wal-telegram
    // const auto waltelegram_cmd { "wal-telegram --wal " + choosen_bg };
    // system(waltelegram_cmd.c_str());

    return 0;
}
