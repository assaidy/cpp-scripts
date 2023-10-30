#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using std::string;
using std::vector;

class File {
private:
    string fpath;
    string rpath;
    string type;
    string permissions; //  owner group others 
                       //  (rwx) (rwx) (rwx)

public:
    void set_type(string _type) {
        type = _type;
    }

    string get_type() const {
        return type;
    }

    void set_permitions(string _permissions) {
        permissions = _permissions;
    }

    string get_permitions() const {
        return permissions;
    }

    void set_fpath(string _fpath) {
        fpath = _fpath;
    }

    string get_fpath() const {
        return fpath;
    }

    void set_rpath(string _rpath) {
        rpath = _rpath;
    }

    string get_rpath() const {
        return rpath;
    }
};

bool compareFiles(const File &a, const File &b) {
    return a.get_rpath() < b.get_rpath();
}

class Dir {
private:
    string path;
    vector<File> file_list;

    const string FPATH { "full_path" };
    const string RPATH { "relative_path" };
    const string FIL { "file" };
    const string DIR { "directory" };
    const string OTH { "other" };

    void load_files() {
        for (const auto &entry : fs::directory_iterator(path)) {
            File cur;
            // set file type
            if (fs::is_directory(entry.status()))
                cur.set_type(DIR);
            else if (fs::is_regular_file(entry.status()))
                cur.set_type(FIL);
            else
                cur.set_type(OTH);

            // set rpath & fpath
            string full_path = entry.path().string();
            cur.set_fpath(full_path);
            cur.set_rpath(full_path.substr(path.length() + 1));

            // set file permissions
            fs::perms p { fs::status(full_path).permissions() };
            std::ostringstream oss;
            oss << ((cur.get_type() == DIR) ? "d" : ".")
                << ((p & fs::perms::owner_read)   != fs::perms::none ? "r" : "-")
                << ((p & fs::perms::owner_write)  != fs::perms::none ? "w" : "-")
                << ((p & fs::perms::owner_exec)   != fs::perms::none ? "x" : "-")
                << ((p & fs::perms::group_read)   != fs::perms::none ? "r" : "-")
                << ((p & fs::perms::group_write)  != fs::perms::none ? "w" : "-")
                << ((p & fs::perms::group_exec)   != fs::perms::none ? "x" : "-")
                << ((p & fs::perms::others_read)  != fs::perms::none ? "r" : "-")
                << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
                << ((p & fs::perms::others_exec)  != fs::perms::none ? "x" : "-"); 
            cur.set_permitions(oss.str());

            file_list.push_back(cur);
        }
        std::sort(file_list.begin(), file_list.end(), compareFiles);
    }

public:
    Dir(string path) : path(path) {
        load_files();
    }

    const vector<File>& get_file_list() {
        return file_list;
    }

    // void print_fpath() {}
    // void print_rpath() {}
};


int main(int argc, char **argv) 
{
    string path { fs::current_path() };

    Dir cur_dir(path);

    for (const auto &file : cur_dir.get_file_list()) {
        std::cout 
            << file.get_permitions() << "  "
            << file.get_rpath() << "\n";
    }

    return 0;
}
