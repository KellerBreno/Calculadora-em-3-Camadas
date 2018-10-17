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

Caso deseje criar uma nova instância do banco de dados, é possível utilizar o arquivo calc_example.sql localizado na pasta Recursos para se criar um novo .sqlite através do programa 'DB Browser for SQLite' (Linux).

## Versões

Após clonar o projeto para a sua maquina, você pode acessar as versões do projeto. Essas versões estão listadas abaixo:

\- [V1](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V1) - Utilizando classes concretas

Para acessar as versões tageadas é **necessário** realizar um checkout no commit referente a aquela tag ou realizar um checkout na tag correspondente.

### Exemplos 

Para a tag V1, você pode fazer:

\- git checkout 115865f (para checkouts pelo código do commit)

**ou** 

\- git checkout V1 (para checkouts pela tag)