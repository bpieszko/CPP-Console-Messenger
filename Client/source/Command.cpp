#include "Command.hpp"

Command::Command(const std::string & message)
{
    const std::vector<std::string> msg_v = splitString(message);
    
    if (msg_v.size() == 0)
        throw CommandException("Empty command.");

    m_type = msg_v.at(0);

    for (int i = 1; i < msg_v.size(); ++i)
        m_args.push_back(msg_v.at(i));
}

const std::string Command::toString() const
{
    std::string result = m_type;

    for (auto i : m_args)
        result += " " + i;
    
    return result;
}

const std::vector<std::string> Command::splitString(const std::string & str) const
{
    std::istringstream iss(str);
    std::vector<std::string> result(
        std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>()
    );

    return result;
}