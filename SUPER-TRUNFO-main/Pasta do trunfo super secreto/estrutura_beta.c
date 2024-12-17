#include "gerenciamento_deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Strings(char a[], int b)
{

    setbuf(stdin, NULL);
    fgets(a, b, stdin);
    a[strcspn(a, "\n")] = '\0';
}

int main()
{

    Cards buffer;
    FILE *arq_csv, *arq_dat;

    arq_csv = fopen("list_cards.csv", "r+");
    if (arq_csv == NULL)
    {

        printf("FALHA AO LER ARQUIVO CSV!\n");
        exit(1);
    } // if erro ao ler arquivo csv (meta_game);

    arq_dat = fopen("save_cards.dat", "rb");
    if (arq_dat == NULL)
    {

        printf("PRIMEIRA INICIALIZAÇÃO...SALVANDO SEU JOGO <não feche o programa>\n");
        arq_dat = fopen("save_cards.dat", "wb");

        if (arq_dat == NULL)
        {

            printf("FALHA AO CRIAR ARQUIVO!\n");
        } // if erro ao criar arquivo bin;
        SaveBin(arq_csv, arq_dat, &buffer); // salva meta game no .dat
        memset(&buffer, 0, sizeof(Cards));  // limpa buffer

    } // if para a primeira inicialização;

    int navegate, n_cards = CountLines(arq_dat);
    Cards *deck = (Cards *)malloc(n_cards * sizeof(Cards)); // cria um vetor de estruturas == deck

    printf("Criando deck...\n\n\n");
    fread(deck, sizeof(Cards), n_cards, arq_dat);

    printf("MENU\n");
    printf("1- PLAY\n2- DECK\n3- OPTIONS\n4- EXIT\n");
    printf("Digite sua opção:");
    scanf("%d", &navegate);
    printf("\n\n");

    switch (navegate)
    {
    case 1:
        // Função Play(jogar) (em construção)
        printf("FUNÇÃO PLAY EM CONSTRUÇÃO\n");
        return 0;
        break;

    case 2:
        // Abre menu de opções de configuração do deck
        printf("1- BUSCAR\n");
        printf("2- FILTRAR\n");
        printf("3- ADICIONAR\n");
        printf("4- EXCLUIR\n");
        printf("5- VOLTAR\n");
        printf("Digite sua opção:");

        // Aguardando o input do usuário para o próximo comando
        navegate = 0;
        scanf("%d", &navegate);
        printf("\n\n");

        // Navegação com base no comando dado
        switch (navegate)
        {
        case 1:
            printf("🔍 ");
            Strings(buffer.nome, sizeof(buffer.nome)); // Função para entrada de nome
            SearchName(buffer.nome, deck, n_cards);    // Função de busca por nome
            break;

        case 2:

            navegate = 0;

            printf("FILTRAR POR\n");
            printf("1 - Tipo\n");
            printf("2 - Stats\n");
            printf("3 - Trunfos\n");
            printf("Digite sua opção:");

            scanf("%d", &navegate);
            printf("\n\n");
            Filter(navegate, deck, arq_dat);
            break;

        case 3:
            // Adicionar (em construção)
            printf("FUNCÃO ADICIONAR EM CONSTRUÇÃO\n");
            break;

        case 4:
            // Excluir (em construção)
            printf("FUNCÃO EXCLUIR EM CONSTRUÇÃO\n");
            break;

        case 5:
            // Voltar
            printf("VOLTANDO...\n");
            break;

        default:
            printf("Opção inválida no menu de opções.\n");
            break;
        }
        break; // Fim do case 2

    case 3:
        // Options do menu principal (em construção)
        printf("FUNÇÃO OPTIONS EM CONSTRUÇÃO\n");
        break;

    case 4:
        // Exit do menu principal (em construção)
        printf("FUNÇÃO EXIT EM CONSTRUÇÃO\n");
        break;

    default:
        printf("DEFAULT!\n");
        break;
    }

    return 0;
}
