#include "ConfigurationManager.hpp"

ConfigurationManager::ConfigurationManager(std::unique_ptr<IConfigParser> parser){
    m_parser = std::move(parser);
}

std::expected<TcpConfig, ErrorCode> ConfigurationManager::get_tcp_config() {
    if (!m_parser) {
        return std::unexpected(ErrorCode::UNKNOWN_ERROR);
    }
    return m_parser->parseTcp();
}

std::expected<UartConfig, ErrorCode> ConfigurationManager::get_uart_config() {
    if (!m_parser) {
        return std::unexpected(ErrorCode::UNKNOWN_ERROR);
    }
    return m_parser->parseUart();
}