#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>

void list(const std::string &path = ".", bool showAll = false, bool longFormat = false) {
    DIR *dir = opendir(path.c_str());
    if (!dir) {
        std::cerr << "Error: Could not open directory " << path << "\n";
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr) {
        if (!showAll && entry->d_name[0] == '.') {
            continue;
        }
        if (longFormat) {
            struct stat fileStat;
            stat(entry->d_name, &fileStat);
            std::cout << fileStat.st_size << "\t";
        }
        std::cout << entry->d_name << "\n";
    }
    closedir(dir);
}

void pwd() {
    char current_dir[1024];
    if (getcwd(current_dir, sizeof(current_dir)) != nullptr) {
        std::cout << current_dir << "\n";
    } else {
        std::cerr << "Error: Could not get current working directory\n";
    }
}

void cd(const std::string &path) {
    if (chdir(path.c_str()) != 0) {
        std::cerr << "Error: Could not change directory to " << path << "\n";
    }
}

void mkdir(const std::string &path) {
    if (::mkdir(path.c_str(), 0755) != 0) {
        std::cerr << "Error: Could not create directory " << path << "\n";
    }
}

void rm(const std::string &path) {
    if (remove(path.c_str()) != 0) {
        std::cerr << "Error: Could not remove " << path << "\n";
    }
}

void touch(const std::string &path) {
    std::ofstream ofs(path);
    if (!ofs) {
        std::cerr << "Error: Could not create file " << path << "\n";
    }
}

void cp(const std::string &source, const std::string &destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);
    if (!src || !dst) {
        std::cerr << "Error: Could not copy file\n";
        return;
    }
    dst << src.rdbuf();
}

void mv(const std::string &source, const std::string &destination) {
    cp(source, destination);
    rm(source);
}

void cat(const std::string &path) {
    std::ifstream ifs(path);
    if (!ifs) {
        std::cerr << "Error: Could not open file " << path << "\n";
        return;
    }
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << "\n";
    }
}

void help() {
    std::cout << "Supported commands:\n"
              << "ls [path] [-a] [-l]\n"
              << "pwd\n"
              << "cd <path>\n"
              << "mkdir <path>\n"
              << "rm <path>\n"
              << "touch <path>\n"
              << "cp <source> <destination>\n"
              << "mv <source> <destination>\n"
              << "cat <path>\n"
              << "help\n"
              << "EXIT\n";
}

int main() {
    std::string input_string;
    std::vector<std::string> arg_vector;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input_string);
        if (input_string.empty())
            continue;
        arg_vector.clear();
        std::string arg;
        std::istringstream string_stream(input_string);
        while (string_stream >> arg) {
            arg_vector.push_back(arg);
        }
        if (arg_vector[0] == "EXIT" || arg_vector[0] == "exit") {
            break;
        } else if (arg_vector[0] == "ls") {
            std::string path = ".";
            bool showAll = false;
            bool longFormat = false;
            for (size_t i = 1; i < arg_vector.size(); ++i) {
                if (arg_vector[i] == "-a")
                    showAll = true;
                else if (arg_vector[i] == "-l")
                    longFormat = true;
                else
                    path = arg_vector[i];
            }
            list(path, showAll, longFormat);
        } else if (arg_vector[0] == "pwd") {
            pwd();
        } else if (arg_vector[0] == "cd") {
            if (arg_vector.size() < 2) {
                std::cerr << "Usage: cd <path>\n";
            } else {
                cd(arg_vector[1]);
            }
        } else if (arg_vector[0] == "mkdir") {
            if (arg_vector.size() < 2) {
                std::cerr << "Usage: mkdir <path>\n";
            } else {
                mkdir(arg_vector[1]);
            }
        } else if (arg_vector[0] == "rm") {
            if (arg_vector.size() < 2) {
                std::cerr << "Usage: rm <path>\n";
            } else {
                rm(arg_vector[1]);
            }
        } else if (arg_vector[0] == "touch") {
            if (arg_vector.size() < 2) {
                std::cerr << "Usage: touch <path>\n";
            } else {
                touch(arg_vector[1]);
            }
        } else if (arg_vector[0] == "cp") {
            if (arg_vector.size() < 3) {
                std::cerr << "Usage: cp <source> <destination>\n";
            } else {
                cp(arg_vector[1], arg_vector[2]);
            }
        } else if (arg_vector[0] == "mv") {
            if (arg_vector.size() < 3) {
                std::cerr << "Usage: mv <source> <destination>\n";
            } else {
                mv(arg_vector[1], arg_vector[2]);
            }
        } else if (arg_vector[0] == "cat") {
            if (arg_vector.size() < 2) {
                std::cerr << "Usage: cat <path>\n";
            } else {
                cat(arg_vector[1]);
            }
        } else if (arg_vector[0] == "help") {
            help();
        } else {
            std::cerr << "Unknown command: " << arg_vector[0] << "\n";
        }
    }
    return 0;
}
