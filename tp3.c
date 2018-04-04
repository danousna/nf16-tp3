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

void consulter(int idEtu, BlockChain bc) {
    /**
     * Profondeur de recherche des transactions.
     * Attention, il faudra remonter dans les blocs
     * précédents si le bloc courant ne contient
     * pas assez de transactions.
     *
     * Il est aussi possible qu'un étudiant n'ai pas `historyBacktrack`
     * transactions, dans ce cas (pire cas) on devra remonter toute
     * la blockchain jusqu'au premier block.
     */
    int historyBacktrack = 5;
    T_Block *currentBlock = bc;

    printf("Etudiant #%i : \n", idEtu);
    printf(" - solde : %f EATCoin", soldeEtudiant(idEtu, bc));
    printf("--- affichage des %i dernières transations ---", historyBacktrack);

    T_Transaction *next = bc->liste;
    while (historyBacktrack > 0) {
        if (next->id == idEtu) {
            afficherTransaction(next, currentBlock);
            historyBacktrack--;
        }
        next = next->suiv;

        // vérification si nous sommes arrivés à la fin
        // des transactions du bloc, si tel est le cas, on passe
        // au bloc suivant
        if(next->suiv == NULL) {
            next = currentBlock->suiv->liste;
        }
    }
}

void afficherTransaction(T_Transaction *transaction, T_Block *block) {
    printf("Transaction#%i\n", transaction->id);
    printf(" - montant : %f EATCoin\n", transaction->montant);
    printf(" - bloc : #%i\n", block->id);
    printf(" - description :\n");
    printf("%s\n", transaction->desc);
}


int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc) {

}