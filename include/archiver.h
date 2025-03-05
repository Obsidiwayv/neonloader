//
// Created by pizza on 2/15/2025.
//

#ifndef ARCHIVER_H
#define ARCHIVER_H

#include <cstdint>
#include <filesystem>

struct JarPackageHeader
{
	uint32_t version;
	uint8_t encoding;
	uint8_t _padding[3];
	uint16_t alias_count;
};


class BundleArchive
{
public:
    // Getting the file will be covered later
    void pushFile(std::filesystem::directory_entry entry);
    void initHeader();
    void closeArchive();
private:
    JarPackageHeader header = {};
};

#endif //ARCHIVER_H
