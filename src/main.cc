#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <aux.hpp>
#include <ios>
#include <print>
#include <string>

constexpr long s2i(const std::string s) {
    long i = 0;
    for (char c : s) i += c;
    return i;
}

int main() {
    const char* home = std::getenv("HOME");
    if (!home) {
        throw std::runtime_error("HOME not set");
    }

    std::filesystem::path configPath =
        std::filesystem::path(home) / ".local/state/wallpapersconfig.txt";

    std::filesystem::create_directories(configPath.parent_path());

    if (!std::filesystem::exists(configPath)) {
        std::ofstream createFile(configPath);
    }

    std::ifstream file(configPath);
    std::string line;
    EntryInfo MainInfo;
    while (std::getline(file, line)) {
        if (std::filesystem::is_directory(line)) {
            for (const std::filesystem::path& path : std::filesystem::directory_iterator(line)) {
                MainInfo.Files.push_back(path);
            }
        } else {
            MainInfo.Files.push_back(line);
        }
    }

    if (MainInfo.Files.size() != 0) PassControl(MainInfo);
    else std::println("There aren't wallpapers in ~/.local/state/wallpapersconfig.txt");

    return 0;
}