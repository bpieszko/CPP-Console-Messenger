#pragma once

#include <string>
#include <mutex>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>

class Logger
{
public:
    Logger() = delete;
    Logger(const std::string & log_file);

    void write(const std::string & message);
    
private:
    const std::string getTime() const;
    const std::string decorate(const std::string & message) const;

    const std::string m_log_file;
    std::mutex m_file_mutex;
};