#include <time.h>
#include "blockchain.h"

BlockChain bc;

T_Transaction *ajouterTransaction(int idEtu, float montant, char *desc, T_Transaction *listeTransaction) {
    T_Transaction *new = malloc(sizeof(T_Transaction));

    // empilage de la transaction
    new->suiv = listeTransaction;
    // init transation
    new->id = idEtu;
    new->montant = montant;
    strcpy(new->desc, desc);

    return new;
}

BlockChain ajouterBlock(BlockChain bc) {
    T_Block *newB = malloc(sizeof(T_Block));

    // bc pointe vers le dernier block.
    if (bc == NULL) {
        newB->id = 0;
        newB->suiv = NULL;
        printf("Block #%d -> ", newB->id);
    } else {
        newB->id = bc->id + 1;
        newB->suiv = bc;
        printf("Block #%d -> ", newB->id);
    }

    newB->liste = NULL;

    return newB;
}

float totalTransactionEtudiantBlock(int idEtu, T_Block *b) {
    float total = 0;
    T_Transaction *next = b->liste;

    while (next != NULL) {
        if (next->id == idEtu) {
            total += next->montant;
        }
        next = next->suiv;
    }
    return total;
}

float soldeEtudiant(int idEtu, BlockChain bc) {
    T_Block *currentBlock = bc;
    float solde = 0;

    do {
        T_Transaction *transaction = currentBlock->liste;
        while (transaction != NULL) {
            if (transaction->id == idEtu)
                solde += transaction->montant;

            transaction = transaction->suiv;
        }
        currentBlock = currentBlock->suiv;
    } while (currentBlock != NULL);

    return solde;
}

void crediter(int idEtu, float montant, char *desc, BlockChain bc) {
    if (montant <= 0) {
        printf("Le montant à créditer : %f doit être >= 0.", montant);
        return;
    }

    // ajout de la nouvelle transaction en tête de liste
    bc->liste = ajouterTransaction(idEtu, montant, desc, bc->liste);
}

int payer(int idEtu, float montant, char *desc, BlockChain bc) {
    if (montant < 0) {
        printf("Erreur : Le montant à payer ne peut pas être négatif. \n");
        return 0;
    }

    if (soldeEtudiant(idEtu, bc) < montant) {
        printf("Erreur : Le compte source ne peut satisfaire le montant à payer. \n");
        return 0;
    } else {
        // On débite de - le montant du solde de l'étudiant.
        bc->liste = ajouterTransaction(idEtu, -montant, desc, bc->liste);
        return 1;
    }
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
    printf(" - solde : %f EATCoin\n", soldeEtudiant(idEtu, bc));
    printf("--- affichage des %i dernières transations ---\n", historyBacktrack);

    T_Transaction *next = bc->liste;
    if (next == NULL) {
        historyBacktrack = 0;
    }
    while (historyBacktrack > 0) {
        if (next->id == idEtu) {
            afficherTransaction(next);
            historyBacktrack--;
        }

        if (next->suiv != NULL) {
            next = next->suiv;

            // vérification si nous sommes arrivés à la fin
            // des transactions du bloc, si tel est le cas, on passe
            // au bloc suivant
            if (next->suiv == NULL) {
                // si on a atteint le premier bloc, on sort
                if (currentBlock->suiv == NULL) {
                    historyBacktrack = 0;
                } else {
                    next = currentBlock->suiv->liste;
                }
            }
        } else {
            historyBacktrack = 0;
        }
    }
    printf("--- fin de l'affichage ---\n");

}

int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc) {
    if (payer(idSource, montant, desc, bc) == 1) {
        crediter(idDestination, montant, desc, bc);
        return 1;
    } else {
        return 0;
    }
}

void afficherTransaction(T_Transaction *transaction) {
    printf("Transaction\n");
    printf(" - idEtu : %i\n", transaction->id);
    printf(" - montant : %f EATCoin\n", transaction->montant);
    //printf(" - bloc : #%i\n", block->id);
    printf(" - description :\n");
    printf("   \"%s\"\n", transaction->desc);
}

T_Block *getBlock(int id, BlockChain bc) {
    T_Block *currentBlock = bc;

    do {
        if (currentBlock->id == id)
            return currentBlock;
        currentBlock = currentBlock->suiv;
    } while (currentBlock != NULL);

    return NULL;
}

void liberer() {
    printf("Libération de l'espace mémoire...\n");

    while (bc != NULL) {
        T_Block *block_suiv = bc->suiv;

        if (bc->liste != NULL) {
            while (bc->liste->suiv != NULL) {
                printf("Libération de la transaction (%d, %f)\n", bc->liste->id, bc->liste->montant);

                T_Transaction *transaction_suiv = bc->liste->suiv;

                // free(bc->liste->id);
                // free(bc->liste->montant);
                // free(bc->liste->desc);
                free(bc->liste);

                bc->liste = transaction_suiv;
            }
        }

        //free(&bc->id);
        free(bc);

        bc = block_suiv;
    }
}

void DatePlusDays(struct tm *date, int days) {
    const time_t ONE_DAY = 24 * 60 * 60;

    // Seconds since start of epoch
    time_t date_seconds = mktime(date) + (days * ONE_DAY);

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime(&date_seconds);;
}

/**
 * Export du fichier, retourne 1 si succès, 0 sinon.
 *
 * @param fileName
 * @param blockChain
 * @return
 */
int exporter(char *fileName, BlockChain blockChain) {
    FILE *file = fopen(fileName, "w");

    if (file == NULL) {
        printf("Disc full or no permission\n");
        return 0;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if (blockChain != NULL) {
        do {
            T_Transaction *transaction = blockChain->liste;

            while (transaction != NULL) {

                // Rendre joli.
                if (tm.tm_mday < 10)
                    fprintf(file, "0%d/", tm.tm_mday);
                else
                    fprintf(file, "%d/", tm.tm_mday);

                // Rendre joli.
                if (tm.tm_mon + 1 < 10)
                    fprintf(file, "0%d/", tm.tm_mon + 1);
                else
                    fprintf(file, "%d/", tm.tm_mon + 1);

                fprintf(file, "%d;%d;%.2f;%s\n", tm.tm_year + 1900, transaction->id,
                        transaction->montant, transaction->desc);

                transaction = transaction->suiv;
            }

            blockChain = blockChain->suiv;

            DatePlusDays(&tm, -1);
        } while (blockChain != NULL);
    }


    fclose(file);
    return 1;
}

/**
 * Import du fichier, retourne 1 si succès, 0 sinon.
 *
 * @param fileName
 * @param blockChain
 * @return
 */
BlockChain importer(char *fileName) {

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("No file found\n");
        return 0;
    }


    BlockChain blockChain = ajouterBlock(NULL);

    int max_lenght = 999;
    char str[max_lenght];
    // lecture du fichier et création de la liste chainée
    if (file) {
        char *str = NULL;
        ssize_t read;
        size_t len = 0;
        while (read = getline(&str, &len, file) != -1) {

            char day[3];
            strcpy(day, str);
            day[2] = '\0';

            char month[3];
            strcpy(month, str + 3);
            month[2] = '\0';

            char year[5];
            strcpy(year, str + 6);
            year[4] = '\0';

            int id;
            float montant;
            char description[255];

            int posL = 0;
            // 0 = id
            // 1 = montant
            // 2 = description

            int pos = 11;

            char temp[max_lenght];
            strcpy(temp, "");
            for (; pos < max_lenght; ++pos) {
                if (str[pos] == '\n') {
                    strcpy(description, temp);
                    break;
                } else if (str[pos] == ';') {
                    // on regarde dans quoi on cale le temp
                    switch (posL) {
                        case 0:
                            id = atoi(temp);
                            break;
                        case 1:
                            montant = atof(temp);
                            break;
                    }

                    // reinitialisation du temp
                    strcpy(temp, "");
                    ++posL;
                } else {
                    strncat(temp, &str[pos], 1);
                }
            }

            printf("%d/%d/%d;%d;%f;%s\n", atoi(day), atoi(month), atoi(year), id, montant, description);
        }
        fclose(file);
    }


    // lecture de la liste chainée et ajout des transactions / blocs
}