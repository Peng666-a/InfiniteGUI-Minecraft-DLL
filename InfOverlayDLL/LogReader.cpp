#include "LogReader.h"
#include <iostream>
#include <sstream>

LogReader::LogReader(const std::string& logFilePath)
    : logFilePath(logFilePath) {
    logFile.open(logFilePath);
}

void LogReader::ReadLogAndUpdateDanmaku(DanmakuWindow& danmakuWindow) {
    std::string line;

    while (std::getline(logFile, line)) {
        if (line.find("進入了直播間") != std::string::npos) {
            std::string username = ExtractUsername(line);
            danmakuWindow.AddEnterRoomMessage(username + " 进入了直播间");
        }
        else if (line.find("贈送了礼物:") != std::string::npos) {
            std::string username = ExtractUsername(line);
            std::string gift = ExtractGift(line);
            std::string giftMessage = username + " 赠送了礼物：" + gift;
            danmakuWindow.AddGiftMessage(giftMessage);
        }
        else {
            std::string message = ExtractMessage(line);
            danmakuWindow.AddMessage(message);
        }
    }
}

std::string LogReader::ExtractUsername(const std::string& line) {
    size_t start = line.find(":") + 1;
    size_t end = line.find(" 進入了直播間");
    return line.substr(start, end - start);
}

std::string LogReader::ExtractGift(const std::string& line) {
    size_t start = line.find("贈送的:") + 6;
    size_t end = line.find(" x");
    return line.substr(start, end - start);
}

std::string LogReader::ExtractMessage(const std::string& line) {
    return line;
}