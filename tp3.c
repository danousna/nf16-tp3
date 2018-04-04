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
    if (bc == NULL) {
        newB->id = 0;
    } else {
        newB->id = bc->id + 1;
    }

    newB->liste = newL;
    newB->suiv = bc;

    return newB;
}

float totalTransactionEtudiantBlock(int idEtu, T_Block b) {
    float total = 0;
    T_Transaction *next = b.liste;

    while (next != NULL) {
        if (next->id == idEtu) {
            total += next->montant;
        }
        next = next->suiv;
    }
    return total;
}

float soldeEtudiant(int idEtu, BlockChain bc)
{
    T_Block *x = bc;
    float solde = 0;

    while (x->suiv != NULL)
    {
        T_Transaction *transaction = x->liste;
        while(transaction != NULL)
        {
            if (transaction->id == idEtu)
                solde += transaction->montant;
            
            transaction = transaction->suiv;
        }
        x = x->suiv;
    }

    return solde;
}

void crediter(int idEtu, float montant, char *desc, BlockChain bc) {
    if (montant <= 0) {
        printf("Le montant à créditer : %f doit être >= 0.");
        return;
    }

    // ajout de la nouvelle traction en tête de liste
    bc->liste = ajouterTransaction(idEtu, montant, desc, bc->liste);
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