#include <iostream>
#include <memory>
#include "ConfigurationManager.hpp"
#include "IniParser.hpp"
#include <filesystem>

// Função Factory para demonstrar extensibilidade
std::expected<std::unique_ptr<IConfigParser>, ErrorCode> createParser(const std::string& filePath) {
    // Verificação determinística: o arquivo existe?
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return std::unexpected(ErrorCode::FILE_OPEN_FAILED);
    }
    else if (filePath.substr(filePath.find_last_of(".") + 1) != "ini") {
        return std::unexpected(ErrorCode::INVALID_FORMAT); // Formato não suportado
    }
    file.close();

    // Aqui você demonstra a troca fácil de formato:
    return std::make_unique<IniParser>(filePath);
    
    // No futuro, bastaria trocar para:
    // return std::make_unique<JsonParser>(filePath);
}

int main() {
    
    // 2. Criamos o Manager (O "chefe") e entregamos o parser para ele
    auto parser = createParser("config.ini");
    
    if (!parser) {
        std::cerr << "Erro fatal ao inicializar: " << errorCodeToString(parser.error()) << std::endl;
        std::cout << "Pressione Enter para sair..." << std::endl;
        std::cin.get(); 
        return 1;
    }

    ConfigurationManager manager(std::move(*parser));

    std::cout << "--- Carregando Configuracoes ---" << std::endl;

    // 3. Pegamos os dados do TCP
    auto tcp = manager.get_tcp_config();
    if (tcp) {
        std::cout << "[TCP] IP: " << tcp->ip << " | Port: " << tcp->port << " | Protocol: " << tcp->protocol << std::endl;
    } else {
        if(tcp.error() == ErrorCode::PARSE_ERROR) {
            std::cerr << "Erro: Arquivo de configuracao TCP corrompido ou mal formatado!" << std::endl;
        } else {
            tcp.error() = ErrorCode::UNKNOWN_ERROR;
            std::cerr << "Erro desconhecido ao carregar a configuracao TCP!" << std::endl;
        }
            std::cout << "Pressione Enter para sair..." << std::endl;
            std::cin.get();
            return 1;
    }

    // 4. Pegamos os dados da UART
    auto uart = manager.get_uart_config();
    if (uart) {
        std::cout << "[UART] Baudrate: " << uart->baudrate << " | Parity: " << uart->parity << " | Data Bits: " << uart->data_bits << " | Stop Bits: " << uart->stop_bits << std::endl;
    } else {
        if(uart.error() == ErrorCode::PARSE_ERROR) {
            std::cerr << "Erro: Arquivo de configuracao UART corrompido ou mal formatado!" << std::endl;
        } else {
            uart.error() = ErrorCode::UNKNOWN_ERROR;
            std::cerr << "Erro desconhecido ao carregar a configuracao UART!" << std::endl;
        }
            std::cout << "Pressione Enter para sair..." << std::endl;
            std::cin.get();
            return 1;
    }

    return 0;
}