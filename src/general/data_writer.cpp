#include "depthai-shared/general/data_writer.hpp"

#include <assert.h>

#include <fstream>
#include <iostream>

using namespace std;

DataWriter::~DataWriter() {
    _file.close();
}

bool DataWriter::init(const std::string& file_path) {
    _file.open(file_path, std::fstream::out | std::fstream::binary | std::ios_base::app);
    return _file.is_open();
}

unsigned DataWriter::writeData(unsigned char* buffer, unsigned buff_size) {
    _file.write(reinterpret_cast<const char*>(buffer), buff_size);
    _file.flush();
    return _file.gcount();
}
