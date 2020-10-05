#include "depthai-shared/logger/logs_writer.hpp"

#include <iostream>

LogsWriter* LogsWriter::instance = nullptr;

void LogsWriter::releaseInstance() {
    if(instance) {
        delete instance;
        instance = nullptr;
    }
}
LogsWriter* LogsWriter::getInstanse() {
    return instance;
}