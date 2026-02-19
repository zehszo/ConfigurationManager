#ifndef I_CONFIG_PARSER_HPP
#define I_CONFIG_PARSER_HPP

#include <expected>
#include <string>
#include "error-handler.hpp" 

struct TcpConfig {
    std::string ip;
    int port;
    std::string protocol;
};

struct UartConfig {
    int baudrate;
    int data_bits;
    std::string parity;
    int stop_bits;
};

class IConfigParser {
public:
    virtual ~IConfigParser() = default;
    virtual std::expected<TcpConfig, ErrorCode> parseTcp() = 0;
    virtual std::expected<UartConfig, ErrorCode> parseUart() = 0;
};

#endif