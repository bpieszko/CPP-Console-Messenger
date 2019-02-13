#include "Client.hpp"

Client::Client()
    : m_resolver()
{

}

void Client::start()
{
    showMenu();

    while (true)
    {
        try
        {
            handleCommand(getCommand(">"));
        }
        catch (CommandException & e)
        {
            showMessage(WARNING, e.what());
        }
    }
}

void Client::handleCommand(const Command & cmd)
{
    if (!m_resolver->resolve(cmd))
        throw CommandException("Unknown command type.");
}

void Client::showMessage(const MSG_TYPE type, const std::string & msg) const
{
    switch (type)
    {
        case NORMAL:
            std::cout << "[*] " << msg << std::endl;
            break;
        case WARNING:
            std::cout << "[!] " << msg << std::endl;
            break;
        case ERROR:
            throw CommandException("[!!!] Error: " + msg);
            break;
        default:
            throw CommandException("Unknown message type.");
    }
}

const Command Client::getCommand(const std::string & pre_msg) const
{
    std::string result;

    std::cout << pre_msg << " ";
    std::cin >> result;

    return Command(result);
}

void Client::showMenu() const
{
    showMessage(NORMAL, "Client started.");
    showMessage(NORMAL, "Commands:");
    for (auto i : m_resolver.getCommands())
    {
        showMessage(NORMAL, i->getMenu());
    }
}