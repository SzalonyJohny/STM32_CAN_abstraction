#pragma once

#include <vector>
#include <string>
#include <filesystem>
#include <fstream>

namespace csv {

std::vector<std::string> findAllCsv(std::string const &path = "csvFiles")
{

    std::vector<std::string> csvFiles;
    for (const auto &file: std::filesystem::directory_iterator(path))
    {
        std::string path = file.path();
        if (path.compare(path.length(), 5, ".csv")) {
            csvFiles.emplace_back(file.path());
        }
    }
    return csvFiles;
}

bool parseCsv(std::string fileName)
{

    std::string hppFileName = fileName.replace(fileName.length() - 3, 3, "hpp");
    std::ifstream file;
    file.open(fileName);

    if (not(file.is_open())) {
        return false;
    }

    while (true) {

    }

    return true;
}

} //namespace csv
