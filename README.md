# Configuration Manager

## Descrição
Biblioteca C++ moderna desenvolvida para o gerenciamento eficiente e seguro de configurações em sistemas de controle e automação. O sistema permite a leitura de parâmetros de comunicação (TCP e UART) de forma extensível e resiliente a falhas de entrada de dados.

## Escolhas Técnicas

- **Tratamento de Erros (std::expected)**: Utilização do `std::expected` (C++23) para um fluxo de erro determinístico sem o uso de exceções. Isso garante que falhas como arquivos inexistentes, campos corrompidos ou tipos inválidos sejam tratadas de forma segura e explícita.
- **Arquitetura (Factory & Strategy)**: Implementação baseada em interfaces (`IConfigParser`) e o uso de uma função Factory para instanciação. Essa abordagem permite que a biblioteca seja estendida para novos formatos (como JSON ou XML) sem a necessidade de alterar a lógica de negócio do `ConfigurationManager`.
- **Cache de Memória (std::map)**: O arquivo de configuração é lido e processado uma única vez no construtor do Parser. Os dados são mapeados em um `std::map<std::string, std::string>`, eliminando acessos repetitivos ao disco (I/O) e garantindo maior performance e consistência dos dados.
- **Robustez e Validação**: Implementação de validação rigorosa de campos obrigatórios através de contadores e verificação de integridade de tipos numéricos (prevenindo falhas de conversão de string para int) antes do preenchimento das structs de configuração.

## Dependências
- Compilador com suporte a **C++23** (necessário para o uso de `std::expected` e `structured bindings`).
- CMake 3.15+ (recomendado).

## Compilação
```bash
mkdir build && cd build
cmake ..
cmake --build .