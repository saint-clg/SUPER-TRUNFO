#include "gerenciamento_deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    Cards buffer;
    FILE *arq_csv, *arq_dat;

    arq_dat = fopen("save_cards.dat", "r+b");
    if (arq_dat == NULL)
    {
        arq_csv = fopen("list_cards.csv", "r+");
        if (arq_csv == NULL)
        {

            printf("FALHA AO LER ARQUIVO CSV!\n");
            exit(1);
        } // if erro ao ler arquivo csv (meta_game);

        printf("PRIMEIRA INICIALIZAÇÃO...SALVANDO SEU JOGO <não feche o programa>\n");
        arq_dat = fopen("save_cards.dat", "w+b");

        if (arq_dat == NULL)
        {

            printf("FALHA AO CRIAR ARQUIVO!\n");
        } // if erro ao criar arquivo bin;
        SaveBin(arq_csv, arq_dat, &buffer); // salva meta game no .dat
        memset(&buffer, 0, sizeof(Cards));  // limpa buffer

        fclose(arq_csv);

    } // if para a primeira inicialização;

    int navegate, n_cards = CountLines(arq_dat);
    Cards *deck = (Cards *)malloc(n_cards * sizeof(Cards)); // cria um vetor de estruturas == deck

    printf("Criando deck...\n\n\n");
    fread(deck, sizeof(Cards), n_cards, arq_dat);
    printf("MENU\n");
    do
    {
        /* code */
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
            printf("1- BUSCAR\n2- FILTRAR\n3- ADICIONAR\n4- EXCLUIR\n5- ALTERAR\n6- EXPORTAR\n7- VOLTAR\n...");

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
                navegate = 0; // Abertura de submenu
                printf("FILTRAR:\n1- TIPO\n2- STATS\n3- SUPER TRUNFOS\n...");
                scanf("%d", &navegate);
                printf("\n\n");
                Filter(navegate, deck, arq_dat);
                break;

            case 3:
                AddCard(buffer, arq_dat);
                n_cards = CountLines(arq_dat);
                deck = realloc(deck, n_cards * (sizeof(Cards)));
                fread(deck, sizeof(Cards), n_cards, arq_dat);
                memset(&buffer, 0, sizeof(Cards));
                break;

            case 4:
                DeletCard(deck, arq_dat);
                n_cards = CountLines(arq_dat);
                deck = realloc(deck, n_cards * (sizeof(Cards)));
                rewind(arq_dat);
                fread(deck, sizeof(Cards), n_cards, arq_dat);
                break;

            case 5:
                SwitchStatus(deck, buffer, arq_dat);
                memset(&buffer, 0, sizeof(Cards));
                break;

            case 6:
                ExportCsv(arq_dat);
                break;
            
            case 7:
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
            printf("Saindo do arquivo rsrsrs\n");
            break;

        default:
            printf("OPÇÃO INVALIDA NO MENU DE OPÇOES BURRO!\n");
            break;
        }

    } while (navegate != 4);
    


    fclose(arq_dat);
    free(deck);

    return 0;
} // main
