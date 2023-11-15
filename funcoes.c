#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"


int tamanhoArquivo(char *arquivo){
    int size;
    //Declaração da variavel do arquivo a ser aberto
    //representado por File Pointer(fp)
    FILE *fp = NULL; 
    fp = fopen(arquivo, "rb");
    //Caso ainda seja NULL o arquivo não foi aberto ou não existe
    //por isso a função retornara -1 que é um tamanho impossivel
    if(fp==NULL){
        return -1;
    }
    //A função fseek está movendo o ponteiro do arquivo para o fim dele
    //Assim achando o tamanho do arquivo
    fseek(fp, 0l, SEEK_END);
    //Retorna onde o ponteiro está, portanto o tamnaho
    size = ftell(fp);
    //retorna o ponteiro ao começo do arquivo
    rewind(fp);
    fclose(fp);
    return size;
}


