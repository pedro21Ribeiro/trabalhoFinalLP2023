# Tutorial de Instalação do Sistema no linux

Primeiro de tudo atualize todas as dependencias do sistema usando o comando abaixo

> sudo apt update && sudo apt full-upgrade

Feito isso Digite o comando abaixo

> sudo apt-get install mysql-server libmysqlclient-dev gcc -y

Agora conecte-se ao mysql usando o comando abaixo

> sudo mysql -u root -p

Dentro do sql digite o comando abaixo ("Substitua o _Sua senha aqui_ por uma senha que escolher)

==**ATNÇÃO NÃO ESQUEÇA DO PONTO E VIRGULA AO FINAL DE CADA LINHA**==

> ALTER USER 'root'@'localhost' IDENTIFIED BY 'sua senha aqui';

Recomendo já criar um usuário para ser usado no código ao invez de usar o usuário root

para criar um usuário digite o comando abaixo no mysql

> CREATE USER 'nomeDoUser'@'localhost' IDENTIFIED BY 'Senha';

Feito isso de as permissões ao seu novo usuário

> GRANT ALL PRIVILEGES ON banco.* TO 'nomeDoUser'@'localhost';

Crie o banco de dados que será usado por padrão o programa usa um banco de dados chamado "banco" use o comando a seguir para cria-lo:

> CREATE DATABASE banco;

agora saia da interface do mysql 

> QUIT;

na pasta onde está o projeto digite no terminal, para gerar o banco de dados

> sudo mysql -u root -p banco < banco.sql

com o banco de dados gerado digite os seguintes comandos no terminal para fazer a linkagem das flags do c

> mysql_config --libs

> mysql_config --cflags

agora abra a pasta dos Conectores e abra a pasta do linux com o seguinte comando

> cd Connectors/mysql-connector-c-6.1.11-linux-glibc2.12-x86_64/

e digite o seguinte comando

> sudo cp ./include/* /usr/include/ -r

volte para a pasta inicial do aplicativo com o seguinte comando

> cd ../..

 e no arquivo funcoes.c mude os dados que estão no topo do arquivo para os dados criado com o sql

> *user = "Seu usuário aqui";
> *password = "Senha do usuário aqui";

feito isso volte ao terminal e digite o seguinte comando para compilar o programa

> gcc funcoes.h funcoes.c main.c -o main -lmysqlclient

para rodar digite 

> ./main

**Atenção** caso o usuário colocado no funcoes.c seja root precisara de permissões elevadas para rodar o programa nesse caso use o seguinte comando

> sudo ./main
