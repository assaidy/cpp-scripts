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

const char WAYLAND_MD {'w'};
const char XORG_MD {'x'};

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

void set_wal(const string &_choosen_bg, char mode) {
    const auto swww_cmd { "swww img " + _choosen_bg }; // Wayland
    const auto feh_cmd { "feh --bg-fill " + _choosen_bg }; // Xorg
    if (mode == WAYLAND_MD) {
        system(swww_cmd.c_str());
    } else if (mode == XORG_MD) {
        system(feh_cmd.c_str());
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        return 1;
    } else {
        srand(time(0));

        // declare the path
        // string HOME { getenv("HOME") };
        // string path { HOME + "/Pictures/walls" };

        // get all files
        auto files { get_dir_files(argv[1]) };

        // choose random file
        string choosen_bg { get_rand_file(files) };

        // set as background (once)
        set_wal(choosen_bg, WAYLAND_MD);

        // automatically change wallpaper (work in bg)
        // while (true) {
        //     set_wal(choosen_bg, 'W');
        //     const std::chrono::minutes DURATION(10);
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
}
