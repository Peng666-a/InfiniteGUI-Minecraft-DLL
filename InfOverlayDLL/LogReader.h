#pragma once
#include <string>
#include <fstream>
#include "DanmakuWindow.h"

class LogReader {
public:
    LogReader(const std::string& logFilePath);
    void ReadLogAndUpdateDanmaku(DanmakuWindow& danmakuWindow);

private:
    std::string ExtractUsername(const std::string& line);
    std::string ExtractGift(const std::string& line);
    std::string ExtractMessage(const std::string& line);

    std::ifstream logFile;
    std::string logFilePath;
};