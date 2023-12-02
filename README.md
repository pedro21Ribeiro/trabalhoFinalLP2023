# Trabalho final de Linguagem de Programação(LP) 2° Semestre de 2023

Este projeto é um aplicativo de manutenção de bancos de dados desenvolvido em C como parte de um projeto para a disciplina de Linguagem de Programação. O objetivo principal do aplicativo é proporcionar aos funcionários do banco uma ferramenta eficiente para gerenciar e manter registros de banco de dados. O aplicativo utiliza a linguagem de programação C para a lógica do sistema e integração com o MySQL para manipulação eficiente de dados. Os integrantes do grupo são:

* Mariane Oliveira dos Santos mariane.santos25@fatec.sp.gov.br
* Marjory Harumi Barbosa Hito marjory.hito@fatec.sp.gov.br
* Matheus Santos Alves de Lima Matheus.lima80@fatec.sp.gov.br
* Pedro Silva Ribeiro pedro.ribeiro32@fatec.sp.gov.br
* Raphael Nascimento da Silva raphael.silva118@fatec.sp.gov.br

## Requesitos

Antes de começar a instalar certifique-se que o sistema onde o programa irá funcionar é uma distribuição de linux.
O projeto em especifico foi feito no Ubuntu 22.04.03, recomendamos usar a mesma versão ou uma versão próxima para evitar complicações


#﻿# Tutorial de Instalação do Sistema no linux

Primeiro, atualize todas as dependências do sistema usando o comando abaixo:

> sudo apt update && sudo apt full-upgrade

Feito isso, digite o comando abaixo:

> sudo apt-get install mysql-server libmysqlclient-dev gcc -y

Agora, conecte-se ao mysql usando o comando abaixo:

> sudo mysql -u root -p

Dentro do sql, digite o comando abaixo ("Substitua o _Sua senha aqui_ por uma senha que escolher)

**ATENÇÃO, NÃO ESQUEÇA DO PONTO E VIRGULA AO FINAL DE CADA LINHA**

> ALTER USER 'root'@'localhost' IDENTIFIED BY 'sua senha aqui';

Recomenda-se já deixar criado um usuário para ser usado no código ao invés de usar o usuário root.

Para criar um usuário digite o comando abaixo no mysql:

> CREATE USER 'nomeDoUser'@'localhost' IDENTIFIED BY 'Senha';

Feito isso, dê as permissões ao seu novo usuário:

> GRANT ALL PRIVILEGES ON banco.* TO 'nomeDoUser'@'localhost';

Crie o banco de dados que será usado.
Por padrão, o programa usa um banco de dados chamado "banco", use o comando a seguir para cria-lo:

> CREATE DATABASE banco;

Após isso feito, saia da interface do mysql.

> QUIT;

Na pasta em está o projeto digite para gerar o banco de dados no terminal:

> sudo mysql -u root -p banco < banco.sql

Assim, com o banco de dados gerado, digite os seguintes comandos no terminal para fazer a linkagem das flags do c:

> mysql_config --libs

> mysql_config --cflags

Agora, abra a pasta dos Conectores e, posteriormente, abra a pasta do linux com o seguinte comando:

> cd Connectors/mysql-connector-c-6.1.11-linux-glibc2.12-x86_64/

Então, digite o seguinte comando:

> sudo cp ./include/* /usr/include/ -r

Feito isso, volte para a pasta inicial do aplicativo com o seguinte comando:

> cd ../..

Assim sendo, no arquivo funcoes.c mude os dados que estão no topo do arquivo para os dados criado com o sql:

> *user = "Seu usuário aqui";
> *password = "Senha do usuário aqui";

Após fazer este passo, volte ao terminal e digite o seguinte comando para compilar o programa:

> gcc funcoes.h funcoes.c main.c -o main -lmysqlclient

Entao, para rodar o programa, digite:

> ./main

**Atenção** caso o usuário colocado no funcoes.c seja root precisará de permissões elevadas para rodar o programa. Neste caso, use o seguinte comando:

> sudo ./main


## Funcionalidades Principais

* **Adicionar usuário**: Adicionar um usuário ao banco de dados
* **Buscar por usuário (nome, cpf ou id)**: Buscar por um usuário utilizando um dos três critérios
* **Movimentar dinheiro entre contas**: Movimentar dinheiro entre a conta de dois usuários
* **Ver histórico de movimentação de um usuário**: Ver o histórico de movimentação de um usuário especifico
* **Alterar dados de um usuário**: Modificar os dados de um usuário
* **Adicionar dinheiro a um usuário**: Adicionar dinheiro a conta de um usuário
* **Deletar um usuário**: Remover o usuário do banco de dados (Movimentações feitas continuam no sistema)

## Estrutura do programa

* **main.c**: Arquivo de menu principal, poucas interações são realizadas nesse arquivo
* **funcoes.c**: Arquivo principal do programa, onde estão todas as funcionalidades do programa
* **funcoes.h**: Arquivo header do programa, utilizado para fazer a _linkagem_ entre o "funcoes.c" e o "main.c"
* **banco.sql**: Arquivo dump do MySQL, usado para definir todos os campos nescessários que serão usados no banco de dados

## Contribuição

Contribuições são bem-vindas! Se você encontrar problemas ou desejar melhorar o aplicativo, sinta-se à vontade para abrir uma issue ou enviar um pull request.
