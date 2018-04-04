#ifndef TP3_H
#define TP3_H

#include <stdlib.h>
#include <string.h>

typedef struct Transaction
{
    int id;
    float montant;
    char desc[255];
    struct Transaction *suiv;
} T_Transaction;

typedef struct Block
{
    int id;
    struct Transaction *liste;
    struct Block *suiv;
} T_Block;

typedef T_Block* BlockChain;

T_Transaction *ajouterTransaction(int idEtu, float montant, char *desc, T_Transaction *listeTransaction);

BlockChain ajouterBlock(BlockChain bc);

float totalTransactionEtudiantBlock(int idEtu, T_Block b);

float soldeEtudiant(int idEtu, BlockChain bc);

void crediter(int idEtu, float montant, char *desc, BlockChain bc);

int payer(int idEtu, float montant, char *desc, BlockChain bc);

void consulter(int idEtu, BlockChain bc);

int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc);

#endif