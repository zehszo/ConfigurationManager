/*
 * error-handler.hpp
 *
 * Definição dos códigos de erro e funções relacionadas para lidar com erros de forma consistente em todo o sistema de configuração. Esta abordagem centraliza a definição dos erros, facilitando a manutenção e a extensão do sistema no futuro.
 * 
 * Autor: José Pedro Rodrigues de Freitas
 * Data: 20-02-2026
 */

 /* Includes ------------------------------------------------------------------*/
#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP
/*----------------------------------------------------------------------------*/

// Definição dos códigos de erro usando uma macro para facilitar a adição de novos erros no futuro. A macro ERROR_CODE_LIST é usada para definir os códigos de erro de forma concisa, e a enum struct ErrorCode é gerada a partir dessa lista. A função errorCodeToString é usada para converter os códigos de erro em strings legíveis para exibição ao usuário.
#define ERROR_CODE_LIST \
    X(FILE_OPEN_FAILED) \
    X(INVALID_FORMAT) \
    X(PARSE_ERROR) \
    X(UNKNOWN_ERROR)

// Enumeração dos códigos de erro, gerada a partir da macro ERROR_CODE_LIST. 
enum struct ErrorCode 
{
    #define X(name) name, // Define cada código de erro na enumeração usando a macro X.
    ERROR_CODE_LIST // Expande a lista de códigos de erro definida na macro ERROR_CODE_LIST.
    #undef X // Limpa a definição da macro X para evitar conflitos futuros.
};

// Função para converter os códigos de erro em strings legíveis para exibição ao usuário. Ela usa um switch para mapear cada código de erro para sua representação em string, facilitando a compreensão dos erros quando eles são exibidos.
inline const char* errorCodeToString(ErrorCode code) 
{
    switch(code) // Usa um switch para mapear cada código de erro para sua representação em string.
    {
        #define X(name) case ErrorCode::name: return #name; // Define cada caso do switch usando a macro X para retornar o nome do código de erro como string.
        ERROR_CODE_LIST // Expande a lista de códigos de erro definida na macro ERROR_CODE_LIST para gerar os casos do switch.
        #undef X // Limpa a definição da macro X para evitar conflitos futuros.
        default: return "UNRECOGNIZED_ERROR"; // Retorna "UNRECOGNIZED_ERROR" para qualquer código de erro que não seja reconhecido, garantindo que a função sempre retorne uma string válida.
    }
}

#endif