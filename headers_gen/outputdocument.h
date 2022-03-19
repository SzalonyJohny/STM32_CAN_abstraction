#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <cassert>

struct CanFrame {
    std::string frameName;
//    int id;
    std::vector<std::string> dataTypes;
    std::vector<std::string> dataNames;
    std::vector<std::string> comments;
};

class OutputDocument
{
public:
    bool write();
    OutputDocument(std::string const &genFileName);
    ~OutputDocument() { file.close(); }
    void addDeviceState(std::string const &newDeviceState);
    void addDeviceStateComment(std::string const &devStateComment);
    void newCanFrame(std::string const &frameName);
    void addElementToCanFrame(std::string const &dataType, std::string const &dataName,
                              std::string const &comment = "");
    void addID(int newId);
    void setDeviceName(std::string const &devName) { deviceName = removeIllegalChars(devName); }
private:
    void writeDeviceStates();
    void writeCanFrames(CanFrame const &frame);
    void writeHeaderGuards();
    void writeIDs();

    std::string removeIllegalChars(std::string const &target);

    std::string makeUppercase(std::string target);

    std::string fileName;
    std::string deviceName;
    std::vector<std::string> deviceStates;
    std::vector<std::string> deviceStateComments;
    std::vector<CanFrame> canFrames;
    std::vector<int> ids;

    std::ofstream file;
public:
    OutputDocument() = delete;
};

