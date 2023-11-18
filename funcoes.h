//Olá mundo

#define MAX 100//Mude  o valor para mudar o numero máximo de usuários
#define tamNome 51//mude para aumentar o tamnho possivel do nome

typedef struct{
    int id;
    char nome[tamNome];
    int tipoDeConta;
    double saldo;
} Conta;

typedef Conta *p_contas;

extern p_contas usuarios[MAX];

int popularVetor(char *arquivo);
int adicionarUsuarios(char *arquivo, char nome[tamNome], int tipoDeConta, double saldo);
