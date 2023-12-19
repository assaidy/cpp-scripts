#include <fstream>
#include <iostream>
#include <string>

void help_msg() {
    std::cout << "[Error] invalid argument.\n";
    std::cout << "Usage: mycat [PATH]\n";
}

int main(int argc, char *argv[])
{
    if (argc == 2) {
        std::string path {argv[1]};
        std::fstream file_handler(path.c_str());
        if (file_handler.fail()) {
            std::cout << "[Error] cannot open the file '" << path << "'.\n";
            return 1;
        } else {
            std::string line;
            while (std::getline(file_handler, line))
                std::cout << line << "\n";
        }
        file_handler.close();
    }
    else {
        help_msg();
        return 1;
    }
    return 0;
}

