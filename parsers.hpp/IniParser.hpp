#ifndef INI_PARSER_HPP
#define INI_PARSER_HPP

#include "IConfigParser.hpp"
#include <string>
#include <fstream>
#include <map>

class IniParser : public IConfigParser {
private:
    std::string m_filePath;
    std::map <std::string, std::string> m_configData; // Armazena os dados lidos do arquivo INI
public:
    IniParser(const std::string& filePath);
    std::expected<TcpConfig, ErrorCode> parseTcp() override;
    std::expected<UartConfig, ErrorCode> parseUart() override;
};

#endif