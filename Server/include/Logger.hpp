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

    static void write(const std::string & message);
    
private:
    static const std::string getTime();
    static const std::string decorate(const std::string & message);

    static std::mutex m_file_mutex;
};