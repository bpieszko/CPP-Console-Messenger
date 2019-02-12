#include "Logger.hpp"

std::mutex Logger::m_file_mutex;

/*
 *  @Brief:
 *      Method to writing message to log file
 *      and on standard output.
 *  @Args:
 *      message - reference to message
 */
void Logger::write(const std::string & message)
{
    std::string out_msg = decorate(message);

    std::lock_guard<std::mutex> lock(m_file_mutex);

    std::cout << out_msg << std::endl;
    
    std::ofstream out("log.txt", std::ios_base::app);
    out << out_msg << std::endl;
}

/*
 *  @Brief:
 *      Decorator to message
 *  @Args:
 *      message
 *  @Return:
 *      Decorated message
 */
const std::string Logger::decorate(const std::string & message)
{
    return "[" + getTime() + "] " + message;
}

/*
 *  @Brief:
 *      Getter to actual time.
 *  @Return:
 *      Time in string in RRRR-MM-DD HH-mm-SS format.
 */
const std::string Logger::getTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    
    return ss.str();
}