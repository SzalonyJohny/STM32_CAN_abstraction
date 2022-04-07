#include "outputdocument.h"
#include <iostream>

OutputDocument::OutputDocument(const std::string &genFileName, bool performCheck):
    performIllegalCharsCheck(performCheck)
{
    fileName = genFileName;
    fileName.erase(fileName.find('.'));
    fileName.erase(0, fileName.find('/') + 1);

    file.open("files/" + fileName + ".hpp");
}

bool OutputDocument::write()
{
    if (not(file.is_open()))
        return false;

    writeHeaderGuards();

    writeVerbatim();

    writeEnums();

    writeDeviceStates();
    file << std::endl;
    for (auto const & frame: canFrames)
        writeCanFrames(frame);

    writeIDs();

    writeHalDefinitons();

    file << "#endif" << std::endl << std::endl;

    return true;
}

void OutputDocument::addDeviceState(const std::string &newDeviceState)
{
    deviceStates.emplace_back(newDeviceState);
}

void OutputDocument::addDeviceStateComment(const std::string &devStateComment)
{
    deviceStateComments.emplace_back(devStateComment);
}

void OutputDocument::newCanFrame(const std::string &newFrameName)
{
    CanFrame newFrame;
    newFrame.frameName = deviceName + '_' + newFrameName;

    canFrames.emplace_back(newFrame);
}

void OutputDocument::addElementToCanFrame(const std::string &dataType, const std::string &dataName,
                                          const std::string &comment)
{
    auto &lastFrame = canFrames.at(canFrames.size() - 1);
    lastFrame.dataTypes.emplace_back(dataType);
    lastFrame.dataNames.emplace_back(dataName);
    lastFrame.comments.emplace_back(comment);
}

void OutputDocument::addVerbatim(const std::string &text)
{
    verbatim.emplace_back(text);
}

void OutputDocument::addID(int newId)
{
    canFrames.at(canFrames.size() - 1).id = newId;
}

void OutputDocument::setFrequency(int freq)
{
    canFrames.at(canFrames.size() - 1).frequency = freq;
}

void OutputDocument::addNewEnum(const std::string &name)
{
    CustomEnum newEnum;
    newEnum.name = name;
    customEnumVec.emplace_back(newEnum);
}

void OutputDocument::addEnumElement(const std::string &name, std::string const &comment)
{
    if (customEnumVec.empty())
        throw std::out_of_range("Custom Enum vector is empty");

    auto &lastEnum = customEnumVec.back();
    lastEnum.states.emplace_back(name);
    lastEnum.comments.emplace_back(comment);
}

void OutputDocument::writeDeviceStates()
{
    file << "enum struct " + deviceName + "_states: uint8_t {" << std::endl;

    for (std::size_t iter = 0; iter < deviceStates.size(); iter++) {
        file << '\t' << removeIllegalChars(deviceStates.at(iter)) << ',';

        if (deviceStateComments.at(iter) not_eq "\r")
            file << "\t// " << deviceStateComments.at(iter);

        file << std::endl;
    }

    file << "};" << std::endl;
}

void OutputDocument::writeCanFrames(const CanFrame &frame)
{
    assert(frame.dataNames.size() == frame.dataTypes.size());

    file << "struct __attribute__ ((packed)) " << frame.frameName << '{' << std::endl;

    for (std::size_t iter = 0; iter < frame.dataNames.size(); iter++) {

        if (frame.dataTypes.at(iter) == "state") {
            file << '\t' << deviceName + "_states";
        }
        else {
            file << '\t' << frame.dataTypes.at(iter);
        }
        file << ' ' << removeIllegalChars(frame.dataNames.at(iter)) << "; ";

        if (frame.comments.at(iter) not_eq "\r")
            file << "// " << frame.comments.at(iter);
        file << std::endl;
    }

    file << "};" << std::endl;
    file << std::endl;
}

void OutputDocument::writeHeaderGuards()
{
    std::time_t startTime = std::chrono::system_clock::to_time_t(
                std::chrono::system_clock::now());

    auto uppercaseName = makeUppercase(deviceName);

    file << "//Generated on " << std::ctime(&startTime);
    file << "#ifndef " << uppercaseName << std::endl;
    file << "#define " << uppercaseName << std::endl;

    file << std::endl;

    file << "#include <cstdint>" << std::endl;
    file << "#include \"hal_can.hpp\"" << std::endl;
    file << "#include \"message_abstraction.hpp\"" << std::endl;

    file << std::endl;
}

void OutputDocument::writeIDs()
{
    file << std::endl;
    for (auto const &frame: canFrames) {
        auto frameName = frame.frameName;
        auto upperCaseName = makeUppercase(frameName);
        file << std::hex;
        file << "const uint16_t " << upperCaseName << "_CAN_ID = " << frame.id << ";" << std::endl;
        file << std::dec;
        file << "const uint8_t " << upperCaseName << "_CAN_DLC = sizeof(" << frameName << ");" << std::endl;
        file << "const uint8_t " << upperCaseName << "_FREQUENCY = " << frame.frequency << ";" << std::endl;
    }

    file << std::endl;
}

void OutputDocument::writeVerbatim()
{
    if (verbatim.size() == 0)
        return;
    for (auto const & line: verbatim)
        file << line;
    file << std::endl;
    file << std::endl;
}

void OutputDocument::writeEnums()
{
    if (customEnumVec.empty())
        return;

    file << std::endl;

    for (auto const &item: customEnumVec) {
        file << "enum struct " + item.name + ": uint8_t {" << std::endl;
        for (std::size_t iter = 0; iter < item.states.size(); iter++) {
            file << '\t' << item.states.at(iter) << ',';
            if (item.comments.at(iter) not_eq "\r") {
                file << "\t//" << item.comments.at(iter);
            }
            file << std::endl;
        }
        file << "};" << std::endl;
        file << std::endl;
    }

    file << std::endl;
}

void OutputDocument::writeHalDefinitons()
{
    for (auto const& frame: canFrames) {
        std::string upperCaseName = makeUppercase(frame.frameName);
        file << "const CAN_TxHeaderTypeDef can_tx_header_" + deviceName + "{" << std::endl
             << upperCaseName + "_CAN_ID, 0xFFF, CAN_ID_STD, CAN_RTR_DATA, " + upperCaseName + "_CAN_DLC, DISABLE};" << std::endl;

        file << std::endl;
    }
}

std::string OutputDocument::removeIllegalChars(std::string const &target)
{
    std::string strcopy = target;
    if (performIllegalCharsCheck) {
        for (auto & ch: strcopy) {
            if (ch == ' ' or ch == '-')
                ch = '_';
        }
    }
    return strcopy;
}

std::string OutputDocument::makeUppercase(std::string target)
{
    for (auto & ch: target) {
        ch = toupper(ch);
    }
    return target;
}
