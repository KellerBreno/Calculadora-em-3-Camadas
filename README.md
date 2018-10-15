# Calculadora em 3 Camadas

Projeto de exemplo de construção de uma calculadora com arquitetura em 3 camadas, utilizando APIs do QT. 

## Getting Started

Nessa seção é explicado os requisitos para se compilar o projeto e como executá-lo na sua máquina.

### Pré Requisitos

Para executar esse projeto é necessário que você tenha as APIs QT Network, QT Database, QT Threads e QT Charts.
Essas APIs estão disponíveis na ferramenta QT Maintenance Tool instalada junto com o QT.

### Executando o Projeto

Após compilar o projeto e gerar os executáveis, para executar o código do server é necessário:

#### Linux
Copiar o arquivo calc_example.sqlite da pasta Recursos para a localização do executável CalcServer. 

#### MacOS
Copiar o arquivo calc_example.sqlite da pasta Recursos para dentro do .app gerado no diretório onde o executavel do CalcServer está localizado.

### Nova instância do banco de dados

Caso deseje criar uma nova instância do banco de dados, é possível utilizar o arquivo calc_example.sql localizado na pasta Recursos para se criar um novo .sqlite através do programa DB Browser para SQLite (Linux).