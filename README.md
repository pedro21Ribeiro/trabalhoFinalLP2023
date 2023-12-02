# Tutorial de Instalação do Sistema no linux

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

