#include "struct_card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ShowCards(Cards card)
{
    printf("\n| %c%d", card.tipo, card.numero);
    if (card.trunfo == true)
        printf("            SUPER TRUNFO\n");
    printf(" %s\n", card.nome);
    printf(" HP: %3.1d Atk: %3.1d\n", card.hp, card.ataque);
    printf(" Peso: %3.2f Altura: %2.2f\n", card.peso, card.altura);
    printf(" Habilidade: %15d |\n\n", card.habilidade);
} // mostra as informações de uma carta no deck

void preencheStruct(Cards buffer, FILE *arq_dat)
{
    Cards buffer_line;
    long posicao;
    int num =1;

    printf("Digite o nome:");
    Strings(buffer.nome, 15);
    printf("Digite o tipo:");
    setbuf(stdin, NULL);
    scanf("%c", &buffer.tipo);
    rewind(arq_dat);
    while (fread(&buffer_line, sizeof(Cards),1,arq_dat) == 1)
    {
        
        if(buffer_line.tipo == buffer.tipo){
            
            ShowCards(buffer_line);
            num++;
        }
    }
    buffer.numero = num;

    printf("A carta é super trunfo?\n0 - Não\n1 - Sim");
    scanf("%1d", (int*)&buffer.trunfo);
    if(buffer.trunfo == 1){

        rewind(arq_dat);
        
        while(fread(&buffer_line, sizeof(Cards), 1, arq_dat) == 1){
              
            if(buffer_line.tipo == buffer.tipo && buffer_line.trunfo == 1){

                ShowCards(buffer_line);
                buffer_line.trunfo = 0;
                posicao = ftell(arq_dat) - sizeof(Cards);
                fseek(arq_dat , posicao, SEEK_SET);
                fwrite(&buffer_line,sizeof(Cards),1,arq_dat); 
                fseek(arq_dat, 0, SEEK_CUR);

                ShowCards(buffer_line);
            }

        }

        rewind(arq_dat);
    }
    printf("Digite o HP:");
    scanf("%d", &buffer.hp);
    printf("Digite o ataque:");
    scanf("%d", &buffer.ataque);
    printf("Digite o peso:");
    scanf("%f", &buffer.peso);
    printf("Digite a altura:");
    scanf("%f", &buffer.altura);
    printf("Digite a habilidade:");
    scanf("%d", &buffer.habilidade);

    fseek(arq_dat, 0, SEEK_END);
    fwrite(&buffer, sizeof(Cards), 1, arq_dat);
    rewind(arq_dat);

    ShowCards(buffer);
}

int SearchName(char buffer[], Cards card[], int n_cards) {

    bool found;
    int x;

    for (int i = 0; i < n_cards; i++)
    {

        if (strcasecmp(card[i].nome, buffer) == 0)
        {

            ShowCards(card[i]);

            x++;
            found = true;
        }
    }

    if (found == false)
    {

        printf("Card não encontrado!\n");
    }

    return x;
}

void Filter(int navegate, Cards deck[], FILE *arq)
{
    char w;
    bool found;

    switch (navegate)
    {
    case 1:

        printf("Digite o tipo a ser filtrado:");
        getchar();
        scanf("%c", &w);

        for (int i = 0; i < CountLines(arq); i++)
        {
            if (w == deck[i].tipo)
            {
                found = true;
                ShowCards(deck[i]);
            }
        }

        if (found == false)
        {
            printf("Nenhuma carta encontrada.\n");
        }

        break;

    case 2:
        printf("STATS:\n1 - HP\n2 - Ataque\n3 - Peso\n4 - Altura\nDigite sua opção: ");

        int opcao2 = 0;
        float X, Y;

        scanf("%d", &opcao2);

        printf("\n\n");

        printf("Filtrar valor entre X e Y.\n");
        printf("X:");
        scanf("%f", &X);
        printf("Y:");
        scanf("%f", &Y);

        if (opcao2 == 1)
        {
            printf("HP entre %.f e %.f:\n", X, Y);
            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].hp && Y >= deck[i].hp)
                {
                    found = true;
                    ShowCards(deck[i]);
                } // if
            } // for

            if (found == false)
            {
                printf("Nenhuma carta encontrada.\n");
            }
        }

        if (opcao2 == 2)
        {
            printf("Ataque entre %.f e %.f:\n", X, Y);
            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].ataque && Y >= deck[i].ataque)
                {
                    found = true;
                    ShowCards(deck[i]);
                } // if
            } // for

            if (found == false)
            {
                printf("Nenhuma carta encontrada.\n");
            }
        }

        if (opcao2 == 3)
        {
            printf("Peso entre %.2f e %.2f:\n", X, Y);
            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].peso && Y >= deck[i].peso)
                {
                    found = true;
                    ShowCards(deck[i]);
                } // if
            } // for

            if (found == false)
            {
                printf("Nenhuma carta encontrada.\n");
            }
        }

        if (opcao2 == 4)
        {
            printf("Altura entre %.2f e %.2f:\n", X, Y);
            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].altura && Y >= deck[i].altura)
                {
                    found = true;
                    ShowCards(deck[i]);
                } // if
            } // for

            if (found == false)
            {
                printf("Nenhuma carta encontrada.\n");
            }
        }

        break;
    case 3:

        for (int i = 0; i < CountLines(arq); i++)
        {
            if (deck[i].trunfo == true)
            {
                found = true;
                ShowCards(deck[i]);
            } // if
        } // for

        if (found == false)
        {
            printf("Nenhuma carta encontrada.\n");
        }

        break;

    default:
        break;
    }
}