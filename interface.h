#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

void afficherMenu();

void afficherBlocks();

void afficherTransactionsBlock();

void afficherTransactionsEtuJour();

void afficherHistoriqueEtu();

void crediterCompte();

void payerRepas();

void transfertEtu();

void exporterTransactions();

void importerTransactions();

#endif