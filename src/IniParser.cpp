/*
 * IniParser.cpp
 *
 * Implementação da classe IniParser, que é responsável por ler arquivos de configuração no formato INI e interpretar os dados para fornecer as configurações de TCP e UART. Esta classe implementa a interface IConfigParser.
 *
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

 /* Includes ------------------------------------------------------------------*/
#include "IniParser.hpp"
#include <fstream>
#include <string>
#include <iostream>
/*----------------------------------------------------------------------------*/

/**
******************************************************************************
* @brief   : Implementação da classe IniParser, que é responsável por ler arquivos de configuração no formato INI e interpretar os dados para fornecer as configurações de TCP e UART. Esta classe implementa a interface IConfigParser.
* @details : O construtor da classe IniParser recebe o caminho para o arquivo de configuração INI e é responsável por ler o arquivo e armazenar os dados em um mapa para uso posterior pelos métodos parseTcp e parseUart. 
******************************************************************************.
* @param: filePath - O caminho para o arquivo de configuração INI. O construtor é responsável por ler o arquivo e armazenar os dados em um mapa para uso posterior pelos métodos parseTcp e parse Uart.
* @return: std::expected<TcpConfig, ErrorCode> - Retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
******************************************************************************
*/
IniParser::IniParser(const std::string& filePath) : m_filePath(filePath) 
{
    std::ifstream file(m_filePath); //Tenta abrir o arquivo para leitura.
    std::string line; // Variável para armazenar cada linha lida do arquivo.

    while (std::getline(file, line)) // Lê o arquivo linha por linha.
    {
        size_t delimiterPos = line.find('='); // Procura o delimitador '=' para separar a chave do valor.
        if (delimiterPos != std::string::npos) // Se o delimitador for encontrado, extrai a chave e o valor e os armazena no mapa de configuração.
        {
            std::string key = line.substr(0, delimiterPos); // Extrai a chave, que é a parte da linha antes do delimitador '='.
            std::string value = line.substr(delimiterPos + 1); // Extrai o valor, que é a parte da linha após o delimitador '='.
            m_configData[key] = value; // Armazena a chave e o valor no mapa de configuração, permitindo que os métodos parseTcp e parseUart acessem os dados de configuração de forma eficiente.
        }
    }
}

/**
******************************************************************************
* @brief   : Implementação do método parseTcp da classe IniParser, que é responsável por ler e interpretar os dados de configuração TCP do arquivo. 
* @details : Ele acessa o mapa de configuração preenchido pelo construtor, extrai os valores correspondentes às chaves "ip", "port" e "protocol", e preenche uma estrutura TcpConfig com esses valores. O método valida os dados (por exemplo, verifica se a porta é um número válido e se o protocolo é "TCP" ou "UDP") e retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
******************************************************************************.
* @return: std::expected<TcpConfig, ErrorCode> - Retorna um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
******************************************************************************
*/
std::expected<TcpConfig, ErrorCode> IniParser::parseTcp() 
{

    int fieldsFound = 0; // Variável para contar o número de campos encontrados na configuração TCP. Isso é usado para validar se todos os campos necessários foram encontrados e preenchidos corretamente.
    TcpConfig tcpConfig; // Estrutura para armazenar a configuração TCP. O método irá preencher esta estrutura com os valores lidos do mapa de configuração e retorná-la se a leitura for bem-sucedida. 

        for(const auto& [key, value] : m_configData) // Itera sobre o mapa de configuração para encontrar as chaves e valores correspondentes à configuração TCP. Ele verifica cada chave para determinar se ela corresponde a um campo de configuração TCP (ip, port, protocol) e valida os valores antes de preenchê-los na estrutura TcpConfig.
        {
           if (key == "ip") // Se a chave for "ip", armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
            { 
                if(!value.empty()) // Verifica se o valor do IP não está vazio. Se for válido, armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
                {
                    tcpConfig.ip = value; // Armazena o valor do endereço IP na estrutura TcpConfig.
                    fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "ip" foi encontrado e preenchido corretamente.
                }
            }
           else if(key == "port") // Se a chave for "port", verifica se o valor é um número válido e, se for, armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
           {
                if(!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) // Verifica se o valor da porta é um número válido (não vazio e composto apenas por dígitos). Se for válido, armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
                {
                    tcpConfig.port = std::stoi(value); // Converte o valor da porta de string para inteiro e armazena na estrutura TcpConfig.
                    fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "port" foi encontrado e preenchido corretamente.
                }
           }
           else if(key == "protocol") // Se a chave for "protocol", verifica se o valor é "TCP" ou "UDP" e, se for válido, armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
           {
                if(value == "TCP" || value == "UDP") // Verifica se o valor do protocolo é "TCP" ou "UDP". Se for válido, armazena o valor na estrutura TcpConfig e incrementa o contador de campos encontrados.
                {
                    tcpConfig.protocol = value; // Armazena o valor do protocolo na estrutura TcpConfig.
                    fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "protocol" foi encontrado e preenchido corretamente.
                }
           }
        }

        if (fieldsFound != 3) // Verifica se todos os campos necessários para a configuração TCP foram encontrados e preenchidos corretamente.
        {
            return std::unexpected(ErrorCode::PARSE_ERROR); // Se algum campo estiver faltando ou for inválido, retorna um código de erro de parsing.
        }
        return tcpConfig; // Retorna a configuração TCP preenchida com os valores lidos do mapa de configuração. 
    }

/**
******************************************************************************
* @brief   : Implementação do método parseUart da classe IniParser, análogo ao método parseTcp.
* @details : Ele acessa o mapa de configuração preenchido pelo construtor, extrai os valores correspondentes às chaves "baudrate", "data_bits", "parity" e "stop_bits", e preenche uma estrutura UartConfig com esses valores. O método valida os dados (por exemplo, verifica se a baudrate e data_bits são números válidos e se a paridade é "None", "Even" ou "Odd") e retorna um std::expected contendo a configuração UART ou um código de erro, permitindo que o chamador lide com falhas.
******************************************************************************.
* @return: std::expected<UartConfig, ErrorCode> - Retorna um std::expected contendo a configuração UART ou um código de erro, permitindo que o chamador lide com falhas.
******************************************************************************
*/
std::expected<UartConfig, ErrorCode> IniParser::parseUart() 
{
    int fieldsFound = 0; // Variável para contar o número de campos encontrados na configuração UART.
    UartConfig uartConfig; // Estrutura para armazenar a configuração UART.

    for(const auto& [key, value] : m_configData) // Itera sobre o mapa de configuração para encontrar as chaves e valores correspondentes à configuração UART.
    {
        if (key == "baudrate") // Se a chave for "baudrate", verifica se o valor é um número válido.
        {
            if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) // Verifica se o valor da baudrate é um número válido (não vazio e composto apenas por dígitos).
            {
                uartConfig.baudrate = std::stoi(value); // Converte o valor da baudrate de string para inteiro e armazena na estrutura UartConfig.
                fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "baudrate" foi encontrado e preenchido corretamente.
            }
        } 
        else if (key == "data_bits") // Se a chave for "data_bits", verifica se o valor é um número válido.
        {
            if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) // Verifica se o valor de data_bits é um número válido (não vazio e composto apenas por dígitos).
            {
                uartConfig.data_bits = std::stoi(value); // Converte o valor de data_bits de string para inteiro e armazena na estrutura UartConfig.
                fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "data_bits" foi encontrado e preenchido corretamente.
            }
        } 
        else if (key == "parity") // Se a chave for "parity", verifica se o valor é "None", "Even" ou "Odd".
        {
            if (!value.empty() && (value == "None" || value == "Even" || value == "Odd")) // Verifica se o valor da paridade é "None", "Even" ou "Odd". Se for válido, armazena o valor na estrutura UartConfig e incrementa o contador de campos encontrados.
            {
                uartConfig.parity = value; // Armazena o valor da paridade na estrutura UartConfig.
                fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "parity" foi encontrado e preenchido corretamente.
            }
        } 
        else if (key == "stop_bits") // Se a chave for "stop_bits", verifica se o valor é um número válido.
        {
            if (!value.empty() && value.find_first_not_of("0123456789") == std::string::npos) // Verifica se o valor de stop_bits é um número válido (não vazio e composto apenas por dígitos).
            {
                uartConfig.stop_bits = std::stoi(value); // Converte o valor de stop_bits de string para inteiro e armazena na estrutura UartConfig.
                fieldsFound++; // Incrementa o contador de campos encontrados para indicar que o campo "stop_bits" foi encontrado e preenchido corretamente.
            }
        }
    }
        
    if (fieldsFound != 4) // Verifica se todos os campos necessários para a configuração UART foram encontrados e preenchidos corretamente.
    {
        return std::unexpected(ErrorCode::PARSE_ERROR); // Se algum campo estiver faltando ou for inválido, retorna um código de erro de parsing.
    }

    return uartConfig; // Retorna a configuração UART preenchida com os valores lidos do mapa de configuração.
}

