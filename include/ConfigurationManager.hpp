/*
 * ConfigurationManager.hpp
 *
 * Definição da classe ConfigurationManager, responsável por gerenciar a configuração do sistema, fornecendo uma interface para acessar os dados de configuração de forma segura e fácil de usar.
 * 
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

 /* Includes ------------------------------------------------------------------*/
#ifndef CONFIGURATION_MANAGER_HPP
#define CONFIGURATION_MANAGER_HPP

#include <memory>
#include "IConfigParser.hpp"
/*----------------------------------------------------------------------------*/

// Classe ConfigurationManager, que é responsável por gerenciar a configuração do sistema, fornecendo uma interface para acessar os dados de configuração de forma segura e fácil de usar. Ela utiliza um parser (que implementa a interface IConfigParser) para ler os dados do arquivo de configuração e fornece métodos para acessar as configurações específicas, como TCP e UART.
class ConfigurationManager 
{
private:
    std::unique_ptr<IConfigParser> m_parser; // Um ponteiro único para um objeto que implementa a interface IConfigParser, usado para ler os dados de configuração do arquivo. O uso de std::unique_ptr garante que o recurso seja gerenciado corretamente, evitando vazamentos de memória e garantindo a propriedade exclusiva do parser dentro da classe ConfigurationManager.
public:
    ConfigurationManager(std::unique_ptr<IConfigParser> parser); // Construtor que recebe um ponteiro único para um objeto que implementa a interface IConfigParser. O construtor é responsável por inicializar o membro m_parser com o parser fornecido, usando std::move para transferir a propriedade do parser para a classe ConfigurationManager. Isso garante que o parser seja gerenciado corretamente e evita cópias desnecessárias.
    std::expected<TcpConfig, ErrorCode> get_tcp_config(); // Método para obter a configuração TCP. Ele chama o método parseTcp do parser para ler os dados de configuração TCP do arquivo e retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
    std::expected<UartConfig, ErrorCode> get_uart_config(); // Método para obter a configuração UART, análogo ao método get_tcp_config.
};

#endif