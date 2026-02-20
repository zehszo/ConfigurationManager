/*
 * ConfigurationManager.cpp
 *
 * Implementação da classe ConfigurationManager, responsável por gerenciar a configuração do sistema, fornecendo uma interface para acessar os dados de configuração de forma segura e fácil de usar.
 *
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

/* Includes ------------------------------------------------------------------*/
 #include "ConfigurationManager.hpp"
/*----------------------------------------------------------------------------*/

/**
******************************************************************************
* @brief   : Implementação da classe ConfigurationManager, responsável por gerenciar a configuração do sistema, fornecendo uma interface para acessar os dados de configuração de forma segura e fácil de usar.
* @details : A classe ConfigurationManager utiliza um parser (que implementa a interface IConfigParser) para ler os dados do arquivo de configuração e fornece métodos para acessar as configurações específicas, como TCP e UART. O construtor da classe recebe um ponteiro único para o parser, garantindo que o recurso seja gerenciado corretamente e evitando vazamentos de memória.
******************************************************************************.
* @param: parser - Um ponteiro único para um objeto que implementa a interface IConfigParser, usado para ler os dados de configuração do arquivo.
******************************************************************************
*/
ConfigurationManager::ConfigurationManager(std::unique_ptr<IConfigParser> parser)
{
    m_parser = std::move(parser); // Inicializa o membro m_parser com o parser fornecido, usando std::move para transferir a propriedade do parser para a classe ConfigurationManager. Isso garante que o parser seja gerenciado corretamente e evita cópias desnecessárias.
}

/**
******************************************************************************
* @brief   : Método para obter a configuração TCP. Ele chama o método parseTcp do parser para ler os dados de configuração TCP do arquivo e retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
* @details : O método get_tcp_config verifica se o parser foi inicializado corretamente antes de chamar o método parseTcp. Se o parser não estiver disponível, ele retorna um código de erro desconhecido. Caso contrário, ele delega a leitura da configuração TCP para o parser e retorna o resultado, que pode ser a configuração TCP ou um código de erro específico, dependendo do sucesso ou falha da operação.
******************************************************************************.
* @return: std::expected<TcpConfig, ErrorCode> - Retorna um std::expected contendo a configuração TCP ou um código de erro.
******************************************************************************
*/
std::expected<TcpConfig, ErrorCode> ConfigurationManager::get_tcp_config() 
{
    if (!m_parser) // Verifica se o parser foi inicializado corretamente antes de chamar o método parseTcp. Se o parser não estiver disponível, ele retorna um código de erro desconhecido.
    {
        return std::unexpected(ErrorCode::UNKNOWN_ERROR); // Retorna um código de erro desconhecido se o parser não estiver disponível, garantindo que o método sempre retorne um std::expected válido, mesmo em casos de falha.
    }
    return m_parser->parseTcp(); // Delegar a leitura da configuração TCP para o parser e retorna o resultado, que pode ser a configuração TCP ou um código de erro específico, dependendo do sucesso ou falha da operação.
}

/**
******************************************************************************
* @brief   : Método para obter a configuração UART, análogo ao método get_tcp_config. 
* @details : O método get_uart_config segue a mesma lógica do método get_tcp_config.
******************************************************************************.
* @return: std::expected<UartConfig, ErrorCode> - Retorna um std::expected contendo a configuração UART ou um código de erro.
******************************************************************************
*/
std::expected<UartConfig, ErrorCode> ConfigurationManager::get_uart_config() 
{
    if (!m_parser) // Verifica se o parser foi inicializado corretamente antes de chamar o método parseUart. Se o parser não estiver disponível, ele retorna um código de erro desconhecido.
    {
        return std::unexpected(ErrorCode::UNKNOWN_ERROR); // Retorna um código de erro desconhecido se o parser não estiver disponível, garantindo que o método sempre retorne um std::expected válido, mesmo em casos de falha.
    }
    return m_parser->parseUart(); // Delegar a leitura da configuração UART para o parser e retorna o resultado, que pode ser a configuração UART ou um código de erro específico, dependendo do sucesso ou falha da operação.
}