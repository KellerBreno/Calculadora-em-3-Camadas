# Calculadora em 3 Camadas

Este trabalho é um projeto-exemplo de construção de uma calculadora com arquitetura cliente/servidor dividida em três camadas, utilizando APIs do QT. 

## Ponto de Partida

Nessa seção é explicado os requisitos para se compilar o projeto e como executá-lo no seu computador.

### Dependências

Para compilar este projeto é necessário que você tenha instaladas as APIs QT SQL, QT Network, QT Database, QT Threads e QT Charts. Essas APIs estão disponíveis na ferramenta *QT Maintenance Tool* instalada junto com o QT.

### Executando o Projeto

Após compilar o projeto e gerar os executáveis do cliente e servidor, para executar o código do servidor é necessário:

#### Windows/Linux
Copiar o arquivo calc_example.sqlite da pasta Recursos para a localização do executável CalcServer. 

#### MacOS
Copiar o arquivo calc_example.sqlite da pasta Recursos para dentro do .app gerado no diretório onde o executável do CalcServer está localizado.

### Banco de Dados vazio

Caso deseje criar uma nova instância do banco de dados, é possível utilizar o arquivo calc_example.sql localizado na pasta Recursos para se criar um nova instância do banco por meio do programa *DB Browser for SQLite* disponível para Linux e MacOS.

## Versões

Após clonar o projeto para a sua máquina, você pode acessar as versões do projeto. Essas versões estão listadas abaixo:

- [V1](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V1) - Versão 1: Projeto com classes concretas;

- [V1a](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V1a) - Versão 1a: Teste para GUI e Classes concretas;

- [V2](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V2) - Versão 2: Projeto com documentação das classes concretas.

- [V3](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V3) - Versão 3: Projeto com APIs separadas.

- [V3a](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V3a) - Versão 3a: Projeto com GUI e lógica de negócio separadas.

- [V4](https://bitbucket.org/KellerBreno/calculadora/commits/tag/V4) - Versão 4: Utilizando Actor-Role.

Para acessar as versões tagueadas é **necessário** realizar um checkout no commit referente a aquela tag ou realizar um checkout na tag correspondente.

### Exemplo 

Caso deseje ver o projeto na Versão 1, você pode fazer:

Para checkouts pelo código do commit:

~~~
git checkout a5d02da 
~~~

Para checkouts pela tag:
~~~
git checkout V1 
~~~

## Documentação

Nessa seção é explicado como gerar a documentação do código utilizando a ferramenta *Doxygen*.

### Pré-Requisitos

Para se utilizar essa ferramenta é necessário instalá-la no seu computador. Para isso você pode fazer:

#### Linux

Você pode adicionar a ferramenta pelo terminal por meio do apt-get:

~~~
sudo apt-get install doxygen 
~~~

A documentação gerada também utiliza a ferramenta *dot* oferecida pelo *graphviz* para gerar gráficos da relação entre as classes. Portanto para a ferramenta funcionar corretamente é necessário instalar o graphviz:

~~~
sudo apt-get install graphviz
~~~

Por fim, caso deseje utilizar a ferramenta com GUI do *Doxygen* para editar o arquivo de configuração é necessário:

~~~
sudo apt-get install doxygen-gui
~~~

### Como utilizar

Nessa seção será explicado como gerar a documentação através da ferramenta *Doxygen*.

#### Terminal

Para gerar a documentação sem os testes, basta digitar no terminal (aberto na pasta raiz do projeto) o comando: 

~~~
doxygen Doxygen.config 
~~~

Com isso ele irá gerar uma pasta nomeada "Documentação" contendo duas pastas "html", a qual conterá a documentação no formato de uma página WEB e "latex", a qual conterá a documentação no formato latex que poderá ser utilizado para gerar um arquivo pdf. No caso da documentação gerada por latex é preciso que o compilador para o latex esteja pré-configurado na máquina.

#### Interface Gráfica

Caso deseje utilizar a ferramenta gráfica para isso, você deve digitar no terminal: 

~~~
doxywizard Doxygen.config
~~~

Ao executar o comando, ele abrirá uma janela. Nessa janela você pode alterar as configurações ou gerar a documentação.