#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>

class Command
{
public:
    Command() = delete;
    Command(const std::string & message);

    const std::string & toString() const;

private:
    const std::vector<std::string> & splitString(const std::string & str) const;
    
    std::string m_type;
    std::vector<std::string> m_args;
};

class CommandException : public std::exception
{
public:
    CommandException() = delete;
    explicit CommandException(const std::string & message) 
        : m_message(message) {}
    virtual const char * what() const throw() { 
        return m_message.c_str();
    }
private:
    std::string m_message;
};