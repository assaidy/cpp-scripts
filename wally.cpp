#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>
#include <string>
#include <thread>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

// get a list of all files
vector<string> get_dir_files(const string &_path) {
    vector<string> files;
    for (const auto &entry : fs::directory_iterator(_path))
        files.push_back(entry.path());
    return files;
}

// get a random file
string get_rand_file(vector<string> files) {
    return files.at(rand() % files.size());
}

void set_wal(const string &_choosen_bg) {
    const auto feh_cmd { "feh --bg-fill " + _choosen_bg };
    system(feh_cmd.c_str());
}

int main()
{
    srand(time(0));

    // declare the path
    string HOME { getenv("HOME") };
    string path { HOME + "/Pictures/walls" };

    // get all files
    auto files { get_dir_files(path) };

    // choose random file
    string choosen_bg { get_rand_file(files) };

    // set as background (once)
    set_wal(choosen_bg);

    // automatically change wallpaper (work in bg)
    // while (true) {
    //     set_wal(choosen_bg);
    //     const std::chrono::minutes DURATION(1);
    //     std::this_thread::sleep_for(DURATION);
    //     choosen_bg = get_rand_file(files);
    // }

    // set pywal
    // const auto pywal_cmd { "wal -i " + choosen_bg };
    // system(pywal_cmd.c_str());

    // set wal-telegram
    // const auto waltelegram_cmd { "wal-telegram --wal " + choosen_bg };
    // system(waltelegram_cmd.c_str());

    return 0;
}
