#ifndef CONFIGURATION_MANAGER_HPP
#define CONFIGURATION_MANAGER_HPP

#include <memory>
#include "IConfigParser.hpp"

class ConfigurationManager {
private:
    std::unique_ptr<IConfigParser> m_parser;
public:
    ConfigurationManager(std::unique_ptr<IConfigParser> parser);
    std::expected<TcpConfig, ErrorCode> get_tcp_config();
    std::expected<UartConfig, ErrorCode> get_uart_config();
};

#endif