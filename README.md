# trabalhoFinalLP2023
Trabalho final da matéria Linguagem de Programação com o Professor Marcos Roberto de Moraes vulgo Maromo

# Como compilar e rodar o programa

O programa usa o banco de dados do MySql, para isso é nescessário cria-lo
está disponivel um arquivo dump onde está a base do banco nessa arquivo já existem alguns
dados para teste. Siga o passo a passo para instalar o MySql e o banco de dados.

- 1. Instale o [MySql](https://dev.mysql.com/doc/mysql-getting-started/en/) seguindo o guia deles e crie um usuário
- 2. No terminal digite o seguinte comando ´msyql -u {seu usuário aqui} -p < banco.sql´
- 3. Com isso o banco de dados é para estar instalado.
- 5. Recomendo criar um novo usuário para acessar o banco de dados sem ser o root.
- 6. Baixe o conector de c para MySql disponível [aqui](https://downloads.mysql.com/archives/c-c/)
- 7. Abra o arquivo funcoes.c no topo do arquivo edite o usuário e senha para o usuário que ira acessar o DB.
- 8. Compile o programa usando o seguinte comando ´cc main.c funcoes.h funcoes.c  -o main -lmysqlclient´
- 9. Caso esteja usando gcc ´gcc main.c funcoes.h funcoes.c  -o main -lmysqlclient´
- 10. agora simplesmente rode o programa no Linux será o comando "./main" no windows é somente abrir o exe criado.
