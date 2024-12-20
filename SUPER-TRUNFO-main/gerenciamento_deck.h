#include "struct_card.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ShowCards(Cards card);

void AddCard(Cards buffer, FILE *arq_dat);

void DeletCard(Cards deck[], FILE *arq_dat);

int SearchName(char buffer[], Cards card[], int n_cards);

void Filter(int navegate, Cards deck[], FILE *arq);

void SwitchStatus(Cards deck[], Cards buffer, FILE *arq_dat);

void ExportCsv(FILE *arq_dat);
