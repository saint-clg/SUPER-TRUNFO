#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    char nome[15];
    char tipo;
    int numero;
    bool trunfo;
    int hp;
    int ataque;
    float peso;
    float altura;
    int habilidade;
}Cards;// estrutura das cartas

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer){

    char header[200], linha[200];

    fgets(header, 200, arq_csv);// ignora cabeçalho
    
    while(fgets(linha, 60, arq_csv) != NULL){
        
        sscanf(linha, " %14[^,], %c, %d, %d, %d, %d, %f, %f, %d",                   buffer->nome,
                                                                                    &buffer->tipo,
                                                                                    &buffer->numero,
                                                                                    (int*)&buffer->trunfo,
                                                                                    &buffer->hp,
                                                                                    &buffer->ataque,
                                                                                    &buffer->peso,
                                                                                    &buffer->altura,
                                                                                    &buffer->habilidade);

        fwrite(buffer, sizeof(Cards), 1, arq_dat);
    }// enquanto houver linhas

    rewind(arq_dat);

}// salva o metagame no arquivo bin na primeira vez que você abre o jogo

int CountLines(FILE *arq_dat){

    int lines = 0;
    long int size;

    fseek(arq_dat, 0, SEEK_END);
    size = ftell(arq_dat);
    lines = size / sizeof(Cards);// verifica quantas cartas tem no arquivo bin
    
    rewind(arq_dat);

    return lines;
}// conta quantas linhas tem no arquivo csv (quantidade de cartas)

