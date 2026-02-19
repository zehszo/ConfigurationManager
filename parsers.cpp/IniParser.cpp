#include "IniParser.hpp"
#include <fstream>
#include <string>
#include <iostream>

IniParser::IniParser(const std::string& filePath) : m_filePath(filePath) {
    std::ifstream file(m_filePath);

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiterPos = line.find('=');
        if (delimiterPos != std::string::npos) {
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            m_configData[key] = value; // Armazena a chave e valor no mapa
        }
    }
}

std::expected<TcpConfig, ErrorCode> IniParser::parseTcp() {

    int fieldsFound = 0;
    TcpConfig config;

        for(const auto& [key, value] : m_configData) {
           if (key == "ip") { 
                config.ip = value;
                fieldsFound++;
            }
           else if(key == "port") {
                if(!value.empty() && value.find_first_not_of("0123456789") == std::string::npos){
                    config.port = std::stoi(value);
                    fieldsFound++;
                    }
            }
           else if(key == "protocol") {
                if(value == "TCP" || value == "UDP") {
                    config.protocol = value;
                    fieldsFound++;
                }
           }
        }
        if (fieldsFound != 3) {
            return std::unexpected(ErrorCode::PARSE_ERROR);
        }
        return config; // Retorna configuração TCP (a implementação real deve ler do arquivo)
    }

    std::expected<UartConfig, ErrorCode> IniParser::parseUart() {

        int fieldsFound = 0;
        UartConfig uartConfig;

       for(const auto& [key, value] : m_configData) {
           if (key == "baudrate") {
                if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) {
                    uartConfig.baudrate = std::stoi(value);
                    fieldsFound++;
                }
        } 
            else if (key == "data_bits") {
                if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) {
                    uartConfig.data_bits = std::stoi(value);
                    fieldsFound++;
                }
        } 
            else if (key == "parity") {
                if (!value.empty()) {
                    uartConfig.parity = value;
                    fieldsFound++;
                }
        } 
            else if (key == "stop_bits") {
                if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) {
                    uartConfig.stop_bits = std::stoi(value);
                    fieldsFound++;
                }
        }
        }
        if (fieldsFound != 4) {
            return std::unexpected(ErrorCode::PARSE_ERROR);
        }
        return uartConfig; // Retorna configuração UART (a implementação real deve ler do arquivo)
}

