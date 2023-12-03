# Trabalho final de Linguagem de Programação(LP) 2° Semestre de 2023

Este projeto é um aplicativo de manutenção de bancos de dados desenvolvido em C como parte de um projeto para a disciplina de Linguagem de Programação. O objetivo principal é proporcionar aos funcionários do banco uma ferramenta eficiente para gerenciar e manter registros de banco de dados. O aplicativo utiliza a linguagem de programação C para a lógica do sistema e integração com o MySQL para manipulação eficiente de dados. Os membros do grupo são:

* Mariane Oliveira dos Santos mariane.santos25@fatec.sp.gov.br
* Marjory Harumi Barbosa Hito marjory.hito@fatec.sp.gov.br
* Matheus Santos Alves de Lima Matheus.lima80@fatec.sp.gov.br
* Pedro Silva Ribeiro pedro.ribeiro32@fatec.sp.gov.br
* Raphael Nascimento da Silva raphael.silva118@fatec.sp.gov.br

## Requesitos

O aplicativo foi feito para ser usado em sistemas linux, recomendamos em específico o Ubuntu 22.04.03, pois foi onde o sistema foi desenvolvido

## Tutorial de Instalação do Sistema no linux

Primeiro, atualize todas as dependências do sistema usando o comando abaixo:

> sudo apt update && sudo apt full-upgrade

Feito isso, digite o comando abaixo:

> sudo apt-get install mysql-server libmysqlclient-dev gcc -y

Agora, conecte-se ao mysql usando o comando abaixo:

> sudo mysql -u root -p

Já no sql digite o comando abaixo ("Substitua o _Sua senha aqui_ por uma senha que escolher):

**ATENÇÃO, NÃO ESQUEÇA DO PONTO E VIRGULA AO FINAL DE CADA LINHA**

> ALTER USER 'root'@'localhost' IDENTIFIED BY 'sua senha aqui';

Recomenda-se criar um usuário para ser usado no código ao invés de usar o usuário root

Assim sendo, para criar um usuário, digite o comando abaixo no mysql:

> CREATE USER 'nomeDoUser'@'localhost' IDENTIFIED BY 'Senha';

Feito isso, conceda as permissões ao seu novo usuário:

> GRANT ALL PRIVILEGES ON banco.* TO 'nomeDoUser'@'localhost';

Crie o banco de dados que será usado por padrão. O programa usa um banco de dados chamado "banco". Desta forma, use o comando a seguir para criá-lo:

> CREATE DATABASE banco;

agora saia da interface do mysql:

> QUIT;

Vá até a pasta em está o projeto. Digite no terminal para gerar o banco de dados:

> sudo mysql -u root -p banco < banco.sql

Após gerar o banco de dados, digite os seguintes comandos no terminal para fazer a linkagem das flags do c:

> mysql_config --libs

> mysql_config --cflags

Feito isto, abra a pasta dos Conectores e abra a pasta do linux com o seguinte comando:

> cd Connectors/mysql-connector-c-6.1.11-linux-glibc2.12-x86_64/

Após realizar esse passo, digite o seguinte comando:

> sudo cp ./include/* /usr/include/ -r

Então, vá para a pasta inicial do aplicativo com o seguinte comando:

> cd ../..

Após isso realizado, vá no arquivo funcoes.c e mude os dados que estão no topo do arquivo para os dados criados com o sql:

> *user = "Seu usuário aqui";
> *password = "Senha do usuário aqui";

Após alterar os dados, volte ao terminal e digite o seguinte comando para compilar o programa:

> gcc funcoes.h funcoes.c main.c -o main -lmysqlclient

Então, após compilar, para rodar o programa digite: 

> ./main

**Atenção** caso o usuário colocado no funcoes.c seja root precisará de permissões elevadas para rodar o programa. Neste caso, use o seguinte comando:

> sudo ./main

## Principais funcionalidade

* **Cadastrar Usuário**:  Cadastrar novo usuário no banco de dados
* **Buscar por usuário(Nome, CPF ou ID)**: Busca pelos dados de um usuário usando um dos três critérios
* **Realizar movimentação**: Cria um movimento de dinheiro entre usuários do banco
* **Ver histórico de movimentação**: Busca pelas movimentações feitas de um usuário específico
* **Alterar dados**: Altera os dados de um usuário (exceto id)
* **Deletar usuário**: Deleta um usuário do banco de dados(As movimentações que este usuário participou ainda continuam)

## Estrutura do programa

* **main.c**: Arquivo de menus, poucas funções se encontram aqui.
* **funcoes.c**: Arquivo principal, aqui estão todas as funções utilizadas
* **funcoes.h**: Arquivo header para o "funcoes.c" usado para _linkagem_

## Contribuição

Contribuições são bem-vindas! Se você encontrar problemas ou desejar melhorar o aplicativo, sinta-se à vontade para abrir uma issue ou enviar um pull request.
