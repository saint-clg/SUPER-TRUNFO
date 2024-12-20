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
    return;
} // mostra as informações de uma carta no deck

void AddCard(Cards buffer, FILE *arq_dat)
{
    Cards buffer_line;
    long posicao;
    int num = 1, sub_menu;
    char confirm, tipo;
    bool end = false;

    do
    {
        num = 1;

        printf("Digite o nome:");
        Strings(buffer.nome, 15);
        do
        {
            printf("Digite o tipo: (P/L/G/D)\n");
            setbuf(stdin, NULL);
            scanf("%c", &buffer.tipo);
            tipo = buffer.tipo;
            if (tipo != 'P' && tipo != 'L' && tipo != 'D' && tipo != 'G' && tipo != 'p' && tipo != 'l' && tipo != 'd' && tipo != 'g')
            {

                printf("TIPO NÃO EXISTENTE:\n(P) PSIQUICO\n(L) LUTADOR\n(G) GELO\n(D) DRAGÃO\nEscolha um dos tipos disponíveis!\n");
            }
        } while (tipo != 'P' && tipo != 'L' && tipo != 'D' && tipo != 'G' && tipo != 'p' && tipo != 'l' && tipo != 'd' && tipo != 'g');
        rewind(arq_dat);
        while (fread(&buffer_line, sizeof(Cards), 1, arq_dat) == 1)
        {

            if (buffer_line.tipo == buffer.tipo)
            {
                num++;
            } // if
        } // while
        buffer.numero = num;

        printf("Criar SUPER TRUNFO??\n0 - Não\n1 - Sim\n...");
        scanf("%1d", (int *)&buffer.trunfo);
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

        printf("Tem certeza que deseja criar a carta?(s/n)");
        ShowCards(buffer);
        setbuf(stdin, NULL);
        scanf("%c", &confirm);
        if (confirm == 's' || confirm == 'S')
        {
            if (buffer.trunfo == 1)
            {

                rewind(arq_dat);
                while (fread(&buffer_line, sizeof(Cards), 1, arq_dat) == 1)
                {

                    if (buffer_line.tipo == buffer.tipo && buffer_line.trunfo == 1)
                    {

                        buffer_line.trunfo = 0;
                        posicao = ftell(arq_dat) - sizeof(Cards);
                        fseek(arq_dat, posicao, SEEK_SET);
                        fwrite(&buffer_line, sizeof(Cards), 1, arq_dat);
                        fseek(arq_dat, 0, SEEK_CUR);

                    } // if
                } // while

                rewind(arq_dat);
            } // if super trunfo

            fseek(arq_dat, 0, SEEK_END);
            fwrite(&buffer, sizeof(Cards), 1, arq_dat);
            rewind(arq_dat);

            printf("%s Foi criado como Carta de N = %d do tipo %c\n", buffer.nome,
                   buffer.numero,
                   buffer.tipo);

            end = true;
        } // if
        else
        {

            printf("Voltar (1)\nCriar nova carta (2)\n...");
            setbuf(stdin, NULL);
            scanf("%d", &sub_menu);
            if (sub_menu == 1)
            {

                end = true;
            } // if
            else
            {

                continue;
            } // else
        } // else

    } while (!end);
    return;
} // Add Card

void DeletCard(Cards deck[], FILE *arq_dat)
{

    char buffer_nome[20];
    int lines = CountLines(arq_dat), new_size = 0;
    Cards temp_deck[lines];
    bool encontrado = false, end = false;

    do
    {

        new_size = 0;
        encontrado = false;

        printf("Nome da carta: ");
        Strings(buffer_nome, 20);

        for (int i = 0; i < lines; i++)
        {

            if (strcasecmp(deck[i].nome, buffer_nome) != 0)
            {

                temp_deck[new_size++] = deck[i];
            }
            else
            {

                encontrado = true;
                ShowCards(deck[i]);
            }
        }

        if (encontrado == true)
        {

            char verificacao;
            printf("Tem certeza que deseja excluir o %s? (s/n)\n", buffer_nome);
            scanf("%c", &verificacao);

            if (verificacao == 's' || verificacao == 'S')
            {

                fclose(arq_dat);
                arq_dat = fopen("save_cards.dat", "w+b");
                if (arq_dat == NULL)
                {

                    printf("ERRO AO ZERAR ARQ_DAT!\n");
                    return;
                }

                rewind(arq_dat);
                fwrite(temp_deck, sizeof(Cards), new_size, arq_dat);
                printf("%s foi excluido!\n", buffer_nome);
                end = true;
            }
            else
            {

                printf("Operação cancelada\n");
                return;
            }
        }
        else
        {

            char verificacao;
            printf("Carta não encontrada!\nTentar novamente?(s\n)\n");
            scanf("%c", &verificacao);
            if (verificacao == 'n' || verificacao == 'N')
            {

                end = true;
            }
        }
    } while (!end);
    return;
} // DeletCard

int SearchName(char buffer[], Cards card[], int n_cards)
{

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
} // Search Name

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
        break;

    case 2:

        navegate = 0;

        printf("Filtro por status:\n1 - HP\n2 - ATK\n3 - Peso\n4 - Altura\n....: ");

        float X, Y;

        scanf("%d", &navegate);

        printf("\n\n");

        printf("Filtrar valor (X <= Y)\n");
        printf("X:");
        scanf("%f", &X);
        printf("Y:");
        scanf("%f", &Y);

        if (navegate == 1)
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
        }

        if (navegate == 2)
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
        }

        if (navegate == 3)
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
        } // if

        if (navegate == 4)
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
        break;

    default:
        break;
    }

    if (found == false)
    {
        printf("Nenhuma carta encontrada.\n");
    }

    return;
} // Filter

void SwitchStatus(Cards deck[], Cards buffer, FILE *arq_dat)
{
    char confirm;
    int sub_menu = 0, savei;
    bool end = false, alterCard = false;

    do
    {
        printf("Nome da carta: ");
        Strings(buffer.nome, 20);

        for (int i = 0; i < CountLines(arq_dat); i++)
        {

            if (strcasecmp(deck[i].nome, buffer.nome) == 0)
            {

                ShowCards(deck[i]);

                printf("Deseja alterar os status dessa carta?(s/n)\n");
                scanf("%c", &confirm);
                if (confirm == 's' || confirm == 'S')
                {

                    printf("ALTERAR:\n1- HP\n2- ATK\n3- PESO\n4- ALTURA\n...");
                    setbuf(stdin, NULL);
                    scanf("%d", &sub_menu);
                    savei = i;
                    do
                    {

                        if (sub_menu == 1)
                        {

                            printf("NOVO HP: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &deck[i].hp);
                            end = true;
                            alterCard = true;
                        }
                        if (sub_menu == 2)
                        {

                            printf("NOVO ATK: ");
                            setbuf(stdin, NULL);
                            scanf("%d", &deck[i].ataque);
                            end = true;
                            alterCard = true;
                        }
                        if (sub_menu == 3)
                        {

                            printf("NOVO PESO: ");
                            setbuf(stdin, NULL);
                            scanf("%f", &deck[i].peso);
                            end = true;
                            alterCard = true;
                        }
                        if (sub_menu == 4)
                        {

                            printf("NOVA ALTURA: ");
                            setbuf(stdin, NULL);
                            scanf("%f", &deck[i].altura);
                            end = true;
                            alterCard = true;
                        }

                        if (sub_menu != 1 && sub_menu != 2 && sub_menu != 3 && sub_menu != 4)
                        {

                            printf("ERRO AO AVANÇAR PELO SUB_MENU!\n");
                            end = false;
                        }
                    } while (sub_menu != 1 && sub_menu != 2 && sub_menu != 3 && sub_menu != 4);
                }
                else
                {

                    printf("1- Cancelar\n2- Pesquisar outra carta\n...");
                    scanf("%d", &sub_menu);
                    if (sub_menu == 1)
                    {

                        end = true;
                    }
                    else
                    {

                        continue;
                    }
                }
            }
        }
    } while (!end);

    if (alterCard)
    {

        int total_lines = CountLines(arq_dat);
        fclose(arq_dat);
        arq_dat = fopen("save_cards.dat", "w+b");
        if (arq_dat == NULL)
        {

            printf("ERRO AO ZERAR ARQ_DAT!\n");
            return;
        }

        fwrite(deck, sizeof(Cards), total_lines, arq_dat);

        printf("CARTA SENDO ADICIONADA AO ARQ.DAT... NÃO DESLIGUE O PROGRAMA...\n");

        printf("CARTA ALTERADA COM SUCESSO!");
        ShowCards(deck[savei]);
    }

    return;
} // SwitchStatus

void ExportCsv(FILE *arq_dat)
{

    FILE *n_arq_csv = fopen("deck_supertrunfo.csv", "w+b");
    if (n_arq_csv == NULL)
    {

        printf("FALHA AO CRIAR ARQUIVO PARA EXPORTAÇÃO DE DECK\n");
        return;
    }

    Cards buffer;
    rewind(arq_dat);

    fprintf(n_arq_csv, "nome,tipo,numero,trunfo,hp,ataque,peso,altura,habilidade\n");

    while (fread(&buffer, sizeof(Cards), 1, arq_dat) == 1)
    {

        fprintf(n_arq_csv, "%s,%c,%d,%d,%d,%d,%.2f,%.2f,%d\n", buffer.nome,
                buffer.tipo,
                buffer.numero,
                (int)buffer.trunfo,
                buffer.hp,
                buffer.ataque,
                buffer.peso,
                buffer.altura,
                buffer.habilidade);
    }

    printf("ARQUIVO EXPORTADO PARA "
           "deck_supertrunfo.csv"
           "\n");

    fclose(n_arq_csv);
    return;
} // ExportCsv
