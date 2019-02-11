#include "Logger.hpp"

Logger::Logger(const std::string & log_file)
    : m_log_file(log_file)
{

}

void Logger::write(const std::string & message)
{
    std::string out_msg = decorate(message);

    std::lock_guard<std::mutex> lock(m_file_mutex);

    std::cout << out_msg << std::endl;
    
    std::ofstream out("log.txt", std::ios_base::app);
    out << out_msg << std::endl;
}

const std::string Logger::decorate(const std::string & message) const
{
    return "[" + getTime() + "] " + message;
}

const std::string Logger::getTime() const
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    
    return ss.str();
}