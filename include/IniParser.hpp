/*
 * IniParser.hpp
 *
 * Definição da classe IniParser, que é responsável por ler arquivos de configuração no formato INI e interpretar os dados para fornecer as configurações de TCP e UART. Esta classe implementa a interface IConfigParser.
 *
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

 /* Includes ------------------------------------------------------------------*/
#ifndef INI_PARSER_HPP
#define INI_PARSER_HPP

#include <string>
#include <fstream>
#include <map>
#include "IConfigParser.hpp"
/*----------------------------------------------------------------------------*/

// Classe IniParser, que é responsável por ler arquivos de configuração no formato INI e interpretar os dados para fornecer as configurações de TCP e UART. Esta classe implementa a interface IConfigParser.
class IniParser : public IConfigParser 
{
private:
    std::string m_filePath; // Caminho para o arquivo de configuração INI
    std::map <std::string, std::string> m_configData; // Mapa para armazenar as chaves e valores lidos do arquivo de configuração. A chave é o nome da configuração (por exemplo, "ip", "port", "protocol" para TCP) e o valor é a string correspondente lida do arquivo. Este mapa facilita a busca dos valores de configuração durante a interpretação dos dados e otimiza o processo de parsing, permitindo que o método parseTcp e parseUart acessem os dados de configuração de forma eficiente.
public:
    IniParser(const std::string& filePath); // Construtor que recebe o caminho para o arquivo de configuração INI. Ele é responsável por ler o arquivo e armazenar os dados em um mapa para uso posterior pelos métodos parseTcp e parseUart. O construtor deve lidar com a leitura do arquivo, verificando se ele existe e se pode ser aberto, e deve interpretar as linhas do arquivo para preencher o mapa de configuração. Se o arquivo não puder ser lido ou estiver mal formatado, o construtor deve lançar uma exceção ou lidar com o erro de forma apropriada.
    std::expected<TcpConfig, ErrorCode> parseTcp() override; // Método para ler e interpretar os dados de configuração TCP do arquivo. Ele deve acessar o mapa de configuração preenchido pelo construtor, extrair os valores correspondentes às chaves "ip", "port" e "protocol", e preencher uma estrutura TcpConfig com esses valores. O método deve validar os dados (por exemplo, verificar se a porta é um número válido e se o protocolo é "TCP" ou "UDP") e retornar um std::expected contendo a configuração TCP ou um código de erro, permitindo que o chamador lide com falhas.
    std::expected<UartConfig, ErrorCode> parseUart() override; // Método para ler e interpretar os dados de configuração UART do arquivo, análogo ao método parseTcp. 
};

#endif