/*
 * IConfigParser.hpp
 *
 * Definição da interface IConfigParser, que é responsável por definir os métodos para ler e interpretar os dados de configuração do arquivo. Esta interface é implementada por classes específicas de parser, como o IniParser, que sabem como ler arquivos de configuração em formatos específicos (neste caso, arquivos INI).
 * 
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

/* Includes ------------------------------------------------------------------*/
#ifndef I_CONFIG_PARSER_HPP
#define I_CONFIG_PARSER_HPP

#include <expected>
#include <string>
#include "error-handler.hpp" 
/*----------------------------------------------------------------------------*/

// Estruturas para armazenar as configurações de TCP e UART. 
struct TcpConfig 
{
    std::string ip; // Endereço IP para a configuração TCP.
    int port; // Porta para a configuração TCP.
    std::string protocol; // Protocolo para a configuração TCP (por exemplo, "TCP" ou "UDP").
};

struct UartConfig 
{
    int baudrate; // Taxa de transmissão para a configuração UART.
    int data_bits; // Número de bits de dados para a configuração UART.
    std::string parity; // Paridade para a configuração UART (por exemplo, "None", "Even", "Odd").
    int stop_bits; // Número de bits de parada para a configuração UART.
};

// Interface IConfigParser, que define os métodos para ler e interpretar os dados de configuração do arquivo. Esta interface é implementada por classes específicas de parser, como o IniParser, que sabem como ler arquivos de configuração em formatos específicos (neste caso, arquivos INI).
class IConfigParser 
{
public:
    virtual ~IConfigParser() = default; // Destrutor virtual para garantir que os recursos sejam liberados corretamente quando um objeto que implementa esta interface for destruído.
    virtual std::expected<TcpConfig, ErrorCode> parseTcp() = 0; // Método virtual puro para ler e interpretar os dados de configuração TCP do arquivo. Retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
    virtual std::expected<UartConfig, ErrorCode> parseUart() = 0; // Método virtual puro para ler e interpretar os dados de configuração UART do arquivo. Retorna um std::expected contendo a configuração UART ou um código de erro, permitindo que o chamador lide com falhas.
};

#endif