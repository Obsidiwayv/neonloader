//
// Created by pizza on 2/15/2025.
//

#ifndef ARCHIVER_H
#define ARCHIVER_H
#include <cstdint>
#include <filesystem>



class PakArchiver
{
public:
    // Getting the file will be covered later
    void pushFile(std::filesystem::directory_entry entry);
    void initHeader();
    void closeArchive();
//private:
    //JarPakHeader header = {};
};

#endif //ARCHIVER_H
