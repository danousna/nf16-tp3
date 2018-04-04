#include "tp3.h"

T_Transaction *ajouterTransaction(int idEtu, float montant, char *desc, T_Transaction *listeTransaction)
{
    T_Transaction *new = malloc(sizeof(T_Transaction));

    new->id = idEtu;
    new->montant = montant;
    strcpy(new->desc, desc);
    new->suiv = listeTransaction;

    return new;
}

BlockChain ajouterBlock(BlockChain bc)
{
    T_Block *newB = malloc(sizeof(T_Block));
    T_Transaction *newL = malloc(sizeof(T_Transaction));

    // bc pointe vers le dernier block.
    newB->id = bc->id + 1;
    newB->liste = newL;
    newB->suiv = bc;

    return &newB;
}

float totalTransactionEtudiantBlock(int idEtu, T_Block b)
{

}

float soldeEtudiant(int idEtu, BlockChain bc)
{

}

void crediter(int idEtu, float montant, char *desc, BlockChain bc)
{

}

int payer(int idEtu, float montant, char *desc, BlockChain bc)
{

}

void consulter(int idEtu, BlockChain bc)
{

}

int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc)
{

}