#include "Request.hpp"

Request::Request(const std::string & message)
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

void Request::parseVars(const std::string & vars)
{
    std::vector<std::string> results = splitString(vars, '&');

    for (auto & i : results)
    {
        std::vector<std::string> pair = splitString(i, '=');

        if (pair.size() != 2)
            throw RequestException("Wrong request. Pair is not complete in request.");
        
        if (m_variables.find(pair[0]) != m_variables.end())
            throw RequestException("Wrong request. Pair is already in structure.");

        m_variables.insert({pair[0], pair[1]});
    }
}

const std::string & Request::getType() const
{
    return m_type;
}

const std::string & Request::getMessage() const
{
    return m_message;
}

const std::string & Request::getVar(const std::string & key) const
{
    if (m_variables.find(key) == m_variables.end())
        throw RequestException("Key is not in request data strucure.");

    return m_variables.at(key);
}

std::vector<std::string> Request::splitString(const std::string & str, const char delimiter) const
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

RequestException::RequestException(const std::string & message)
    : m_message(message)
{
    
}