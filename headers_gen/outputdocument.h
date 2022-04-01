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
    int frequency;
    int id;
};

struct CustomEnum {
    std::string name;
    std::vector<std::string> states;
    std::vector<std::string> comments;
};

class OutputDocument
{
public:
    bool write();
    OutputDocument(std::string const &genFileName, bool performCheck);
    ~OutputDocument() { file.close(); }
    void addDeviceState(std::string const &newDeviceState);
    void addDeviceStateComment(std::string const &devStateComment);
    void newCanFrame(std::string const &frameName);
    void addElementToCanFrame(std::string const &dataType, std::string const &dataName,
                              std::string const &comment = "");
    void addVerbatim(std::string const &text);
    void addID(int newId);
    void setFrequency(int freq);
    void setDeviceName(std::string const &devName) { deviceName = removeIllegalChars(devName); }

    void addNewEnum(std::string const &name);
    void addEnumElement(std::string const &name, std::string const &comment = "");

private:
    void writeDeviceStates();
    void writeCanFrames(CanFrame const &frame);
    void writeHeaderGuards();
    void writeIDs();
    void writeVerbatim();
    void writeEnums();

    std::string removeIllegalChars(std::string const &target);
    bool performIllegalCharsCheck;

    std::string makeUppercase(std::string target);

    std::string fileName;
    std::string deviceName;
    std::vector<std::string> deviceStates;
    std::vector<std::string> deviceStateComments;
    std::vector<std::string> verbatim;
    std::vector<CustomEnum> customEnumVec;
    std::vector<CanFrame> canFrames;

    std::ofstream file;
public:
    OutputDocument() = delete;
};

