//
// Created by pizza on 2/15/2025.
//
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <lmcons.h>
#include <windows.h>

#pragma comment(lib, "advapi32.lib")

struct FolderMove
{
	std::string oldFolder;
	std::string newFolder;
};

struct Flags
{
	bool MoveOldContent;
};


const std::string magenta = "\033[95m";
const std::string blue = "\033[94m";

void RunRepak(std::string flags)
{
	std::string command = "repak.exe unpack " + flags;
	system(command.c_str());
}

std::string AppDataPath()
{
    char username[UNLEN + 1];
    DWORD username_length = UNLEN + 1;
    GetUserName(username, &username_length);
    const std::string current_username(username);
    return "C:/Users/" + current_username + "/AppData/Roaming";
}

Flags GetFlags() 
{
	std::string line;
	Flags f;
	if (std::ifstream file("flags"); file.is_open()) 
	{
		file >> line;
		if (line.find("@move") != std::string::npos)
		{
			f.MoveOldContent = true;
		};
	};
	return f;
}

std::string Colorize(const std::string& clr, const std::string& text)
{
    return clr + text + "\033[0m";
}

int main(int argc, char* argv[])
{
    std::string path;

    if (std::ifstream file("dir.txt"); file.is_open())
    {
        file >> path;
    }

    const std::string appData = AppDataPath();
    path.replace(path.find("{APP_DATA}"), 10, appData);
    int copied = 0;
    const Flags pFlags = GetFlags();
    const std::string mod_path = appData + "/.minecraft" + "/mods/";

	if (std::ifstream indexFile("Contents/INDEX"); indexFile.is_open())
	{
		std::string currentPackage;
		while (std::getline(indexFile, currentPackage))
		{
			RunRepak(currentPackage + ".pak");
			std::this_thread::sleep_for(std::chrono::seconds(2));
		    for (std::filesystem::directory_entry entry : std::filesystem::directory_iterator(currentPackage))
		    {
		        const std::string mEntry = mod_path + entry.path().filename().u8string();
		        const std::filesystem::path mod_path_from_str = mEntry;
			if (!std::filesystem::exists(mod_path_from_str))
			{
			    copied += 1;
		            std::cout << "Copying "
		                << Colorize(magenta, entry.path().filename().generic_u8string())
		                << " to " << Colorize(magenta, mod_path) << "\n";
		            std::filesystem::copy_file(entry.path().generic_u8string(), mEntry);
			}
		    }
		    std::filesystem::remove_all(currentPackage);
		}
	}

    if (!copied)
    {
        std::cout << "All files are already copied";
    } else
    {
        std::cout << "Finished";
    }
}
