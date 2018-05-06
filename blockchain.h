#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include <f2fs_fs.h>

typedef struct Transaction {
    int id;
    float montant;
    char desc[255];
    struct Transaction *suiv;
} T_Transaction;

typedef struct Block {
    int id;
    struct Transaction *liste;
    struct Block *suiv;
} T_Block;

typedef struct Timestamp {
    long timestamp;
    struct Transaction *transactions;
    struct Timestamp *nextTimestamp;

} T_Timestamp;

typedef T_Block *BlockChain;

T_Transaction *ajouterTransaction(int idEtu, float montant, char *desc, T_Transaction *listeTransaction);

BlockChain ajouterBlock(BlockChain bc);

float totalTransactionEtudiantBlock(int idEtu, T_Block *b);

float soldeEtudiant(int idEtu, BlockChain bc);

void crediter(int idEtu, float montant, char *desc, BlockChain bc);

int payer(int idEtu, float montant, char *desc, BlockChain bc);

void consulter(int idEtu, BlockChain bc);

int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc);

void afficherTransaction(T_Transaction *transaction);

T_Block *getBlock(int id, BlockChain bc);

int exporter(char *fileName, BlockChain blockChain);

T_Timestamp *insert(long timestamp, T_Transaction *transaction, T_Timestamp *timestampList);

BlockChain importer(char *fileName);

void liberer();

void freeTimestamp(T_Timestamp *timestamp);

int max(int a, int b);

void DatePlusDays(struct tm *date, int days);

#endif