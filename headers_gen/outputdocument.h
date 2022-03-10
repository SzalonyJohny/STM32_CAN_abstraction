#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cassert>

struct CanFrame {
    std::string frameName;
    std::vector<std::string> dataTypes;
    std::vector<std::string> dataNames;
    std::vector<std::string> comments;
};

class OutputDocument
{
public:
    bool write();
    OutputDocument(std::string const &genFileName): fileName(genFileName) {file.open(genFileName);}
    ~OutputDocument() { file.close(); }
    void addDeviceState(std::string const &newDeviceState);
    void newCanFrame(std::string const &frameName);
    void addElementToCanFrame(std::string const &dataType, std::string const &dataName,
                              std::string const &comment = "");
    void addID(int newId) { ids.emplace_back(newId); }
private:
    void writeDeviceStates();
    void writeCanFrames(CanFrame const &frame);
    void writeHeaderGuards();
    void writeIDs();

    std::string makeUppercase(std::string target);

    std::string fileName;
    std::vector<std::string> deviceStates;
    std::vector<CanFrame> canFrames;
    std::vector<int> ids;

    std::ofstream file;
public:
    OutputDocument() = delete;
};

