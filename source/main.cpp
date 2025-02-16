//
// Created by pizza on 2/15/2025.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <lmcons.h>
#include <windows.h>

#pragma comment(lib, "advapi32.lib")

// Format: Year-Day-Month
struct VersionManifest
{
    int year;
    int day;
    int month;
    int software_version;
};


const std::string magenta = "\033[95m";
const std::string blue = "\033[94m";

auto version_manifest = VersionManifest { 25, 16, 2, 0 };

std::string appDataPath()
{
    char username[UNLEN + 1];
    DWORD username_length = UNLEN + 1;
    GetUserName(username, &username_length);
    const std::string current_username(username);
    return "C:/Users/" + current_username + "/AppData/Roaming";
}

std::string colorize(const std::string& clr, const std::string& text)
{
    return clr + text + "\033[0m";
}

int main(int argc, char* argv[])
{
    std::cout << "Welcome to " << colorize(magenta, "neon ")
        << colorize(blue, "loader")
        << " v"
        << std::to_string(version_manifest.software_version) << "\n";
    if (argv[0] == "--pak")
    {
        std::cout << "Packaging is currently under works" << "\n";
    }
    std::string path;

    if (std::ifstream file("dir.txt"); file.is_open())
    {
        file >> path;
    }

    const std::string appData = appDataPath();
    path.replace(path.find("{APP_DATA}"), 10, appData);

    int copied = 0;

    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator("contents"))
    {
        const std::string mod_path = appData + "/.minecraft" + "/mods/" + entry.path().filename().u8string();
        const std::filesystem::path mod_path_from_str = mod_path;
        if (!exists(mod_path_from_str))
        {
            copied += 1;
            std::cout << "Copying "
                << colorize(magenta, entry.path().filename().generic_u8string())
                << " to " << colorize(magenta, mod_path) << "\n";
            std::filesystem::copy_file(entry.path().generic_u8string(), mod_path);
        }
    }

    if (!copied)
    {
        std::cout << "All files are already copied";
    } else
    {
        std::cout << "Placed " << colorize(magenta, std::to_string(copied)) << " mod pack"
            << colorize(blue, std::to_string(version_manifest.year))
            << colorize(blue, std::to_string(version_manifest.day))
            << colorize(blue, std::to_string(version_manifest.month))
            << " into " << path << "\n";
    }
}
