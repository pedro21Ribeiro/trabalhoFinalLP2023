#include <stdlib.h>
#include <stdio.h>
#include "funcoes.h"

p_contas usuarios[MAX];

int popularVetor(char *arquivo){
    FILE *fp = NULL;
    fp = fopen(arquivo, "rb");
    if(fp == NULL){
        return 1;
    }
    

    for(int i = 0; i<MAX; i++){
        usuarios[i] = (p_contas)malloc(sizeof(Conta));
        fread(usuarios[i], sizeof(Conta), 1, fp);
    }

    fclose(fp);
    return 0;
}

int adicionarUsuarios(char *arquivo, char nome[tamNome], int tipoDeConta, double saldo){
    int i = 0;
    popularVetor(arquivo);
    FILE *fp = NULL;
    fp = fopen(arquivo, "wb");
    fwrite("abc", sizeof("abc"), 1, fp);
    fclose(fp);
    
    fp = fopen(arquivo, "wb");

    if(fp == NULL){
        return 1;
    }
    //Esse for está vazio pois o objetivo dele é chegar no ultimo usuário adicionado
    /*for(i=0;i<MAX;i++){
        if(usuarios[i]->id!= i+1){
            break;
        }
    }*/
    usuarios[i] = (p_contas)(malloc(sizeof(Conta)));
    usuarios[i] -> id = 1;
    /*for(int j =0; j < tamNome; j++){
        usuarios[i] -> nome[j] = nome[j];
    }*/
    usuarios[i] -> tipoDeConta = 1;
    usuarios[i] -> saldo = 100;
    
    fwrite(&usuarios, sizeof(Conta), MAX, fp);
    fclose(fp);
    return 0;
}
