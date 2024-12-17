#include "struct_card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowCards(Cards card){

    printf("| %c%d\n", card.tipo, card.numero);
    printf(" %s\n", card.nome);
    printf(" hp: %3.1d atk: %3.1d\n", card.hp, card.ataque);
    printf(" peso: %3.2f altura: %2.2f\n", card.peso, card.altura);
    printf(" habilidade: %15d |\n\n", card.habilidade);
}// mostra as informações de uma carta no deck

int SearchName(char buffer[], Cards card[], int n_cards){

    bool found;
    int x;

    for(int i =0; i < n_cards; i++){

        if(strcasecmp(card[i].nome, buffer) == 0){

            ShowCards(card[i]);

            x++;
            found = true;
        }
    }

    if(found == false){

        printf("Card não encontrado!\n");
    }

    return x;
}

void Filter(int navegate, Cards deck[], FILE *arq)
{
    char w;

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
                ShowCards(deck[i]);
            }
        }
        break;

    case 2:
        printf("STATS:\n");
        printf("1 - HP\n");
        printf("2 - Ataque\n");
        printf("3 - Peso\n");
        printf("4 - Altura\n");

        int opcao2 = 0;
        float X, Y;
        
        scanf("%d", &opcao2);

        switch (opcao2)
        {
        case 1:

            printf("HP entre X e Y:\n");
            setbuf(stdin, NULL);
            printf("X:");
            scanf("%f", &X);
            printf("Y:");
            scanf("%f", &Y);

            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].hp && Y >= deck[i].hp)
                {
                    ShowCards(deck[i]);
                } // if
            } // for

            break;

        case 2:
            printf("Ataque entre X e Y:\n");
            setbuf(stdin, NULL);
            printf("X:");
            scanf("%f", &X);
            printf("Y:");
            scanf("%f", &Y);

            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].ataque && Y >= deck[i].ataque)
                {
                    ShowCards(deck[i]);
                } // if
            } // for

            break;

        case 3:
            printf("Peso entre X e Y:\n");
            printf("X:");
            setbuf(stdin, NULL);
            scanf("%f", &X);
            printf("Y:");
            scanf("%f", &Y);

            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].peso && Y >= deck[i].peso)
                {
                    ShowCards(deck[i]);
                } // if
            } // for
            break;

        case 4:
            printf("Altura entre X e Y:\n");
            printf("X:");
            setbuf(stdin, NULL);
            scanf("%f", &X);
            setbuf(stdin, NULL);
            printf("Y:");
            scanf("%f", &Y);

            for (int i = 0; i < CountLines(arq); i++)
            {
                if (X <= deck[i].altura && Y >= deck[i].altura)
                {
                    ShowCards(deck[i]);
                } // if
            } // for
            break;
        }
        break;

    case 3:

        for (int i = 0; i < CountLines(arq); i++)
        {
            if (deck[i].trunfo == true)
            {
                ShowCards(deck[i]);
            } // if
        } // for

        break;

    default:
        break;
    }
}