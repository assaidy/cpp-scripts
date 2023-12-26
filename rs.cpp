/*
 * Replace spaces in file names with (_)
 */

#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::string get_spaceless_name(const std::string& old_name) {
    std::string new_name {};
    for (char ch : old_name) {
	if (ch == ' ') {
	    new_name += '_';
	} else {
	    new_name += ch;
	}
    }
    return new_name;
}

void rename_file(const fs::path& old_name, const fs::path& new_name) {
    try {
	fs::rename(old_name, new_name);
	std::cout << "file renamed successfully.\n";
    } catch (fs::filesystem_error& e) {
	std::cerr << "Error renaming file: " << e.what(); 
    }
}

int main(int argc, char **argv)
{
    if (argc != 2) {
	std::cerr << "[Error] invalid argument.\n";
	std::cout << "Usage: rs <path>\n";
	return 1;
    } else {
	std::fstream file_handler(argv[1]);
	if (file_handler.fail()) {
	    std::cerr << "[Error] can't open file '" << argv[1] << "'\n";
	    return 1;
	}
	fs::path old_name = argv[1];
	fs::path new_name = get_spaceless_name(argv[1]);
	rename_file(old_name, new_name);

	file_handler.close();
    }
    return 0;
}
