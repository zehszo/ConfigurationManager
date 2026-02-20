/*
 * main.cpp
 *
 * Demonstração de um sistema de configuração robusto e extensível usando C++ moderno.
 * O código é estruturado para ser fácil de entender, mantendo a complexidade oculta.
 *
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */


/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <memory>
#include <filesystem>
#include "ConfigurationManager.hpp"
#include "IniParser.hpp"
/*----------------------------------------------------------------------------*/

/**
******************************************************************************
* @brief   : Função para criar o parser de configuração. Ela verifica se o arquivo existe e se tem a extensão correta antes de criar o parser.
* @details : Esta função é responsável por validar o caminho do arquivo de configuração e criar uma instância do parser apropriado (neste caso, um IniParser). Ela retorna um std::expected contendo o parser ou um código de erro, permitindo que o chamador lide com falhas de forma elegante.
******************************************************************************.
* @param: filePath - O caminho para o arquivo de configuração.
* @return: std::expected<std::unique_ptr<IConfigParser>, ErrorCode> - Retorna um std::expected contendo um ponteiro único para o parser ou um código de erro.
******************************************************************************
*/

std::expected<std::unique_ptr<IConfigParser>, ErrorCode> createParser(const std::string& filePath) {

    std::ifstream file(filePath); // Tenta abrir o arquivo para verificar se ele existe

    if (!file.is_open()) // Verifica se o arquivo foi aberto com sucesso
    {
        return std::unexpected(ErrorCode::FILE_OPEN_FAILED); // Retorna um erro se o arquivo não puder ser aberto (não existe ou falta permissão)
    }
    else if (filePath.substr(filePath.find_last_of(".") + 1) != "ini") // Verifica se a extensão do arquivo é .ini. Se não for, retorna um erro de formato inválido. Pode ser facilmente estendido para suportar outros formatos, como JSON, XML, etc., adicionando mais condições e parsers correspondentes.
    {
        return std::unexpected(ErrorCode::INVALID_FORMAT); // Retorna um erro se o formato do arquivo for inválido (extensão diferente de .ini)
    }
    file.close(); // Fecha o arquivo após a verificação

    return std::make_unique<IniParser>(filePath); // Retorna um parser válido para arquivos INI. Se quisermos adicionar suporte para outros formatos, podemos criar mais condições aqui e retornar o parser correspondente. Por exemplo, para JSON, poderíamos verificar a extensão .json e retornar um JsonParser.
    
    // Exemplo de como adicionar suporte para outros formatos:
    // return std::make_unique<JsonParser>(filePath);
    // return std::make_unique<XmlParser>(filePath);
}

int main() { // 1. Inicialização do sistema de configuração
    
    // 2. Criamos o parser usando a função createParser, que lida com a validação do arquivo e retorna um std::expected contendo o parser ou um código de erro. Isso permite que o código de inicialização seja limpo e fácil de entender, enquanto a complexidade da validação do arquivo fica oculta dentro da função createParser.
    auto parser = createParser("config.ini");
    
    if (!parser) // Verifica se o parser foi criado com sucesso. Se não, exibe uma mensagem de erro e aguarda o usuário pressionar Enter antes de sair.
    {
        std::cerr << "Erro fatal ao inicializar: " << errorCodeToString(parser.error()) << std::endl; // Exibe a mensagem de erro correspondente ao código de erro retornado pela função createParser. A função errorCodeToString é usada para converter o código de erro em uma string legível para o usuário.
        std::cout << "Pressione Enter para sair..." << std::endl; // Solicita ao usuário que pressione Enter para sair.
        std::cin.get(); // Aguarda o usuário pressionar Enter antes de fechar a janela do console.
        return 1; // Retorna um código de erro para indicar que a inicialização falhou.
    }

    // 3. Criamos o ConfigurationManager, passando o parser criado. O ConfigurationManager é responsável por gerenciar a configuração do sistema, fornecendo uma interface para acessar os dados de configuração de forma segura e fácil de usar. Ele utiliza o parser para ler os dados do arquivo de configuração e fornece métodos para acessar as configurações específicas, como TCP e UART.
    ConfigurationManager manager(std::move(*parser)); // Passa o parser para o ConfigurationManager usando std::move para transferir a propriedade do parser para o manager. Isso garante que o parser seja gerenciado corretamente e evita cópias desnecessárias.

    std::cout << "--- Carregando Configuracoes ---" << std::endl; // Exibe uma mensagem indicando que o processo de carregamento das configurações está começando.

    // 4. Pegamos os dados da TCP usando o método get_tcp_config do ConfigurationManager. Este método retorna um std::expected contendo a configuração TCP ou um código de erro. O código verifica se a configuração foi carregada com sucesso e, em caso de falha, exibe uma mensagem de erro específica com base no código de erro retornado. 
    auto tcp = manager.get_tcp_config(); // Chama o método get_tcp_config para obter a configuração TCP. O resultado é um std::expected que pode conter a configuração TCP ou um código de erro.

    if (tcp) // Verifica se a configuração TCP foi carregada com sucesso. Se sim, exibe os detalhes da configuração TCP.
    {
        std::cout << "[TCP] IP: " << tcp->ip << " | Port: " << tcp->port << " | Protocol: " << tcp->protocol << std::endl; // Exibe os detalhes da configuração TCP.
    } 
    
    else // Se a configuração TCP não foi carregada com sucesso, verifica o código de erro para determinar a causa da falha e exibe uma mensagem de erro apropriada.
    {
        if(tcp.error() == ErrorCode::PARSE_ERROR) // Verifica se o erro é um erro de parsing, indicando que o arquivo de configuração TCP está corrompido ou mal formatado.
        {
            std::cerr << "Erro: Arquivo de configuracao TCP corrompido ou mal formatado!" << std::endl; // Exibe uma mensagem de erro específica para indicar que o arquivo de configuração TCP está corrompido ou mal formatado.
        } 
        
        else // Se o erro não for um erro de parsing, assume-se que é um erro desconhecido e exibe uma mensagem de erro genérica.
        {
            tcp.error() = ErrorCode::UNKNOWN_ERROR; // Define o código de erro como UNKNOWN_ERROR para indicar que ocorreu um erro desconhecido ao carregar a configuração TCP.
            std::cerr << "Erro desconhecido ao carregar a configuracao TCP!" << std::endl; // Exibe uma mensagem de erro genérica para indicar que ocorreu um erro desconhecido ao carregar a configuração TCP.
        }
            std::cout << "Pressione Enter para sair..." << std::endl; // Solicita ao usuário que pressione Enter para sair.
            std::cin.get(); //Aguarda o usuário pressionar Enter.
            return 1; // Retorna um código de erro para indicar que houve uma falha ao carregar a configuração TCP.
    }

    // 5. Pegamos os dados da UART usando o método get_uart_config do ConfigurationManager. Este método também retorna um std::expected contendo a configuração UART ou um código de erro. O código verifica se a configuração foi carregada com sucesso e, em caso de falha, exibe uma mensagem de erro específica com base no código de erro retornado, semelhante ao processo para a configuração TCP.
    auto uart = manager.get_uart_config(); // Chama o método get_uart_config para obter a configuração UART. O resultado é um std::expected que pode conter a configuração UART ou um código de erro.

    if (uart) // Verifica se a configuração UART foi carregada com sucesso. Se sim, exibe os detalhes da configuração UART.
    {
        std::cout << "[UART] Baudrate: " << uart->baudrate << " | Parity: " << uart->parity << " | Data Bits: " << uart->data_bits << " | Stop Bits: " << uart->stop_bits << std::endl; // Exibe os detalhes da configuração UART.
    } 
    
    else // Se a configuração UART não foi carregada com sucesso, verifica o código de erro para determinar a causa da falha e exibe uma mensagem de erro apropriada.
    {
        if(uart.error() == ErrorCode::PARSE_ERROR) // Verifica se o erro é um erro de parsing, indicando que o arquivo de configuração UART está corrompido ou mal formatado.
        {
            std::cerr << "Erro: Arquivo de configuracao UART corrompido ou mal formatado!" << std::endl; // Exibe uma mensagem de erro específica para indicar que o arquivo de configuração UART está corrompido ou mal formatado.
        } 
        
        else // Se o erro não for um erro de parsing, assume-se que é um erro desconhecido e exibe uma mensagem de erro genérica.
        {
            uart.error() = ErrorCode::UNKNOWN_ERROR; // Define o código de erro como UNKNOWN_ERROR para indicar que ocorreu um erro desconhecido.
            std::cerr << "Erro desconhecido ao carregar a configuracao UART!" << std::endl; // Exibe uma mensagem de erro genérica para indicar que ocorreu um erro desconhecido ao carregar a configuração UART.
        }
            std::cout << "Pressione Enter para sair..." << std::endl; // Solicita ao usuário que pressione Enter para sair.
            std::cin.get(); // Aguarda o usuário pressionar Enter.
            return 1; // Retorna um código de erro para indicar que houve uma falha ao carregar a configuração UART.
    }

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso.
}