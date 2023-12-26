/*
 * set a random background from a specific folder 
 */

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <string>
#include <thread>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

// INFO: get a list of all files
vector<string> get_dir_files(const string &_path) {
    vector<string> files;
    for (const auto &entry : fs::directory_iterator(_path))
        files.push_back(entry.path());
    return files;
}

// INFO: get a random file
string get_rand_file(vector<string> files) {
    return files.at(rand() % files.size());
}

void set_wal_wayland(const string &_choosen_bg) {
    const auto swww_cmd { "swww img " + _choosen_bg };
    system(swww_cmd.c_str());
}

void set_wal_xorg(const string &_choosen_bg) {
    const auto feh_cmd { "feh --bg-fill " + _choosen_bg };
    system(feh_cmd.c_str());
}

int main(int argc, char *argv[])
{
    srand(time(0));

    // INFO: declare the path
    string path;
    if (argc == 1) {
        string HOME { getenv("HOME") };
        path = HOME + "/Pictures/walls";
    } else {
	path = argv[1];
    }

    // INFO: get all files
    auto files { get_dir_files(path) };

    // INFO: choose random file
    string choosen_bg { get_rand_file(files) };

    // INFO: set as background (once)
    // set_wal_wayland(choosen_bg);
    set_wal_xorg(choosen_bg);

    // INFO: automatically change wallpaper by time period
    // while (true) {
    //     set_wal_wayland(choosen_bg);
    //     set_wal_xorg(choosen_bg);
    //     const std::chrono::minutes DURATION(10);
    //     std::this_thread::sleep_for(DURATION);
    //     choosen_bg = get_rand_file(files);
    // }

    // INFO: set pywal
    const auto pywal_cmd { "wal -i " + choosen_bg };
    // system(pywal_cmd.c_str());
    // system("xdotool key super+F5"); // to work on dwm

    // INFO: set wal-telegram
    // const auto waltelegram_cmd { "wal-telegram --wal " + choosen_bg };
    // system(waltelegram_cmd.c_str());

    return 0;
}
