#include "Message.hpp"

Message::Message(const std::string & message)
{
    std::istringstream iss(message);
    std::getline(iss, m_type);
    
    std::string vars;
    std::getline(iss, vars);
    parseVars(vars);

    std::string line;
    while (std::getline(iss, line))
    {
        m_message += line;
    }
}

void Message::parseVars(const std::string & vars)
{
    std::vector<std::string> results = splitString(vars, '&');

    for (auto & i : vars)
    {
        std::vector<std::string> pair = splitString(vars, '=');
        
        if (pair.size() != 2)
            throw "Cannot read variables.";
        
        if (m_variables.find(pair[0]) != m_variables.end())
            throw "The same key in one response.";

        m_variables.insert({pair[0], pair[1]});
    }
}

const std::string & Message::getType() const
{
    return m_type;
}

const std::string & Message::getMessage() const
{
    return m_message;
}

const std::string & Message::getVar(const std::string & key) const
{
    if (m_variables.find(key) == m_variables.end())
        throw "Key is not in message data strucure.";

    return m_variables.at(key);
}

std::vector<std::string> Message::splitString(const std::string & str, const char delimiter) const
{
    std::istringstream iss(str);
    std::vector<std::string> result;
    std::string token;
    while (std::getline(iss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}