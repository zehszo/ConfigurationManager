# Configuration Manager

## Descrição
Biblioteca C++ desenvolvida para o gerenciamento eficiente e seguro de configurações em software embarcado. O sistema permite a leitura de parâmetros de comunicação (TCP e UART) de forma extensível e resiliente a falhas de entrada de dados.

## Escolhas Técnicas

- **Tratamento de Erros (std::expected)**: Utilização do `std::expected` (C++23) para um fluxo de erro determinístico sem o uso de exceções. Isso garante que falhas como arquivos inexistentes, campos corrompidos ou tipos inválidos sejam tratadas de forma segura e explícita. Implementação de validação rigorosa de campos obrigatórios através de contadores e verificação de integridade de tipos numéricos (prevenindo falhas de conversão de string para int) antes do preenchimento das structs de configuração.
- **Arquitetura (Factory & std::map)**: Implementação baseada em interfaces (`IConfigParser`) e o uso de uma função Factory para instanciação. Essa abordagem permite que a biblioteca seja estendida para novos formatos (como JSON ou XML) sem a necessidade de alterar a lógica de funcionamento do `ConfigurationManager`. O arquivo de configuração é lido e processado uma única vez no construtor do Parser. Os dados são mapeados em um `std::map<std::string, std::string>`, eliminando acessos repetitivos ao disco (I/O) e garantindo maior performance e consistência dos dados.
- **Formato**: Implementação de um parser customizado para arquivos .ini. Este formato foi escolhido por ser um padrão de mercado intuitivo, facilitando a edição manual e garantindo uma estrutura de chaves e valores altamente legível. É uma solução leve e ideal para sistemas embarcados que exigem baixo consumo de recursos e alta confiabilidade na configuração.

## Dependências
- Compilador com suporte a **C++23** (necessário para o uso de `std::expected` e `structured bindings`).
- CMake 3.15+ (recomendado).

## Compilação
```bash
mkdir build 
cd build
cmake ..
cmake --build .
```

## Execução

Certifique-se de que o arquivo `config.ini` (ou qualquer arquivo que será lido) está presente no mesmo diretório do executável.

```bash
cd ..
cd examples
.\config_manager_exe.exe
```

### Estrutura

- `include/`: Headers da interface e definições de contratos.
- `lib/`: Utilitários globais e tratamento de erros via X-Macros
- `src/`: Implementações da lógica do Manager e do Parser específico para arquivos INI.
- `examples/`: Arquivo executável e .ini's de exemplo/teste.
