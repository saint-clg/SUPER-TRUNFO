#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char nome[20];
    char tipo;
    int numero;
    bool trunfo;
    int hp;
    int ataque;
    float peso;
    float altura;
    int habilidade;
} Cards; // estrutura das cartas

void Strings(char a[], int b);

void SaveBin(FILE *arq_csv, FILE *arq_dat, Cards *buffer);

int CountLines(FILE *arq_dat);
