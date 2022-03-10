#include <iostream>
#include <filesystem>

#include "csv.h"

int main()
{
    auto csvFileList = csv::findAllCsv();

    if (csvFileList.size() == 0) {
        std::cerr << "Terminated: No csv files found" << std::endl;
        return 0;
    }
    for (const auto &entry: csvFileList) {
        std::cout << "Generating .h file for " << entry << std::endl;

        if (csv::parseCsv(entry)) {
            std::cout << "Done." << std::endl;
        }
        else {
            std::cout << "Parsing of " << entry << " failed.";
        }
    }

    return 0;
}
