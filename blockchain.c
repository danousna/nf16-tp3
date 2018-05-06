#include "blockchain.h"

BlockChain bc;

/**
 * Ajoute une transaction à la liste de Transactions.
 *
 * @param int idEtu
 * @param float montant
 * @param char *desc
 * @param T_Transaction *listeTransaction
 * @return T_Transaction *
 */
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

/**
 * Ajoute un nouveau bloc à la Blockchain.
 *
 * @param BlockChain bc NULL pour le premier block.
 * @return T_Block *
 */
BlockChain ajouterBlock(BlockChain bc) {
    T_Block *newB = malloc(sizeof(T_Block));

    // bc pointe vers le dernier block.
    if (bc == NULL) {
        newB->id = 0;
        newB->suiv = NULL;
    } else {
        newB->id = bc->id + 1;
        newB->suiv = bc;
    }

    newB->liste = NULL;

    return newB;
}

/**
 * Retourne le montant total de dépenses ou de gains sur une journée.
 *
 * @param int idEtu
 * @param T_Block *b
 * @return float
 */
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

/**
 * Retourne le solde total d'un compte.
 *
 * @param int idEtu
 * @param BlockChain bc
 * @return float
 */
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

/**
 * Permet de créditer un compte d'une certaine somme.
 *
 * Le montant à créditer doit être positif.
 *
 * @param int idEtu
 * @param float montant
 * @param char *desc
 * @param BlockChain bc
 */
void crediter(int idEtu, float montant, char *desc, BlockChain bc) {
    if (montant <= 0) {
        printf("Le montant à créditer : %f doit être >= 0.", montant);
        return;
    }

    // ajout de la nouvelle transaction en tête de liste
    bc->liste = ajouterTransaction(idEtu, montant, desc, bc->liste);
}

/**
 * Permet de réaliser un payement si les fonds du compte payeur
 * le permettent.
 *
 * Le montant à payer est strictement positif.
 *
 * @param int idEtu
 * @param float montant
 * @param char *desc
 * @param BlockChain bc
 * @return int
 */
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

/**
 * Affiche l'historique d'un compte (maximum 5 dernières transactions).
 *
 * @param int idEtu
 * @param BlockChain bc
 */
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

/**
 * Transfert des fonds d'une source vers une destination si les fonds
 * de la source le permettent.
 *
 * @param int idSource
 * @param int idDestination
 * @param float montant
 * @param char *desc
 * @param BlockChain bc
 * @return int
 */
int transfert(int idSource, int idDestination, float montant, char *desc, BlockChain bc) {
    if (payer(idSource, montant, desc, bc) == 1) {
        crediter(idDestination, montant, desc, bc);
        return 1;
    } else {
        return 0;
    }
}

/**
 * Affiche une transaction.
 *
 * @param T_Transaction *transaction
 */
void afficherTransaction(T_Transaction *transaction) {
    printf("Transaction\n");
    printf(" - idEtu : %i\n", transaction->id);
    printf(" - montant : %f EATCoin\n", transaction->montant);
    //printf(" - bloc : #%i\n", block->id);
    printf(" - description :\n");
    printf("   \"%s\"\n", transaction->desc);
}

/**
 * Retourne le Block avec l'id recherché dans la Blockchain.
 *
 * @param int id
 * @param BlockChain bc
 * @return T_Block * | NULL
 */
T_Block *getBlock(int id, BlockChain bc) {
    T_Block *currentBlock = bc;

    do {
        if (currentBlock->id == id)
            return currentBlock;
        currentBlock = currentBlock->suiv;
    } while (currentBlock != NULL);

    return NULL;
}

/**
 * Libère la mémoire du programme.
 */
void liberer() {
    printf("Libération de l'espace mémoire...\n");

    while (bc != NULL) {
        T_Block *block_suiv = bc->suiv;

        if (bc->liste != NULL) {
            while (bc->liste->suiv != NULL) {
                printf("Libération de la transaction (%d, %f)\n", bc->liste->id, bc->liste->montant);

                T_Transaction *transaction_suiv = bc->liste->suiv;

                free(bc->liste);

                bc->liste = transaction_suiv;
            }
        }

        free(bc);

        bc = block_suiv;
    }
}

/**
 * Export du fichier, retourne 1 si succès, 0 sinon.
 *
 * @param char *fileName
 * @param BlockChain blockChain
 * @return int
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
 * @param char *fileName
 * @return BlockChain
 */
BlockChain importer(char *fileName) {

    printf("%s\n", fileName);

    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("No file found\n");
        return 0;
    }


    BlockChain blockChain = NULL;

    int max_length = 999;
    char str[max_length];
    // lecture du fichier et création de la liste chainée
    if (file) {
        char *str = NULL;
        ssize_t read;
        size_t len = 0;

        T_Timestamp *timestampList = NULL;

        while (read = getline(&str, &len, file) != -1) {

            int day = atoi((char[3]) {str[0], str[1], '\0'});
            int month = atoi((char[3]) {str[3], str[4], '\0'});
            int year = atoi((char[5]) {str[6], str[7], str[8], str[9], '\0'});

            int id;
            float montant;
            char description[255];

            int posL = 0;
            // 0 = id
            // 1 = montant
            // 2 = description

            int pos = 11;

            char temp[max_length];
            strcpy(temp, "");
            for (; pos < max_length; ++pos) {
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

            // calcul du timestamp
            struct tm t;
            time_t t_of_day;

            t.tm_year = year;
            t.tm_mon = month;           // Month, 0 - jan
            t.tm_mday = day;          // Day of the month
            t.tm_hour = 0;
            t.tm_min = 0;
            t.tm_sec = 0;
            t.tm_isdst = -1;        // Is DST on? 1 = yes, 0 = no, -1 = unknown
            t_of_day = mktime(&t);

            // création de la transaction
            T_Transaction *transaction = malloc(sizeof(T_Transaction));
            strcpy(transaction->desc, description);
            transaction->id = id;
            transaction->montant = montant;
            transaction->suiv = NULL;

            // ajout à la liste de transactions
            timestampList = insert(t_of_day, transaction, timestampList);
        }
        fclose(file);


        // lecture de la liste chainée et ajout des transactions / blocs
        if (timestampList != NULL) {
            // parcours des timestamps (blocs)
            T_Timestamp *t = timestampList;
            long lastTimestamp = t->timestamp;
            do {
                // calcul de combien de blocs vides à ajouter
                // depuis le dernier timestamp
                int nbDaysSinceLastBlock = max(0, (difftime(t->timestamp, lastTimestamp) / 86400) - 1);
                for (int i = 0; i < nbDaysSinceLastBlock; ++i) {
                    blockChain = ajouterBlock(blockChain);
                }

                // ajout du bloc du jour
                blockChain = ajouterBlock(blockChain);

                // ajout des transactions du jour
                T_Transaction *transactionCurr = t->transactions;
                while (transactionCurr != NULL) {
                    blockChain->liste = ajouterTransaction(transactionCurr->id, transactionCurr->montant,
                                                           transactionCurr->desc, blockChain->liste);

                    T_Transaction *nextT = transactionCurr->suiv;
                    // on libère la mémoire après ajout
                    free(transactionCurr);
                    transactionCurr = nextT;
                }

                lastTimestamp = t->timestamp;
                t = t->nextTimestamp;

            } while (t != NULL);
        }


        // libération des timestamps
        freeTimestamp(timestampList);
    }
    return blockChain;
}

/**
 * Libère la mémoire occupée par les Timestamps, pas par les Transactions
 * car elles peuvent être partagées.
 *
 * @param T_Timestamp *timestamp
 */
void freeTimestamp(T_Timestamp *timestamp) {
    while (timestamp != NULL) {
        T_Timestamp *tempTimestamp = timestamp->nextTimestamp;
        free(timestamp);
        timestamp = tempTimestamp;
    }
}

/**
 * Ajoute la transaction dans son groupe de Timestamp.
 *
 * Les Timestamp sont une liste triée du plus ancien au plus récent.
 * 
 * @param long timestamp
 * @param T_Transaction *transaction
 * @param T_Timestamp *timestampList
 * @return T_Timestamp *
 */
T_Timestamp *insert(long timestamp, T_Transaction *transaction, T_Timestamp *timestampList) {
    if (transaction == NULL) {
        return timestampList;
    }

    // si il n'y a pas de noeud, initialisation
    if (timestampList == NULL) {
        timestampList = malloc(sizeof(T_Timestamp));
        timestampList->timestamp = timestamp;
        timestampList->nextTimestamp = NULL;
        timestampList->transactions = NULL;
    }

    // tant qu'on a un noeud suivant
    // et que le timestamp courant n'est pas celui recherché
    // et que le prochain timestamp est <= à celui recherché
    // alors on avance dans le parcours

    while (timestampList->nextTimestamp != NULL &&
           timestampList->timestamp != timestamp &&
           timestampList->nextTimestamp->timestamp <= timestamp
            ) {
        timestampList = timestampList->nextTimestamp;
    }



    // il existe un noeud avec ce timestamp
    if (timestampList->timestamp == timestamp) {
        // ajout de la transaction en tête de liste

        // ajout du chainage
        // passage en tête de liste
        transaction->suiv = timestampList->transactions;
        timestampList->transactions = transaction;
    } else {
        // sinon on doit créer ce noeud et l'ajouter
        T_Timestamp *timestampListNew = malloc(sizeof(T_Timestamp));
        timestampListNew->timestamp = timestamp;
        timestampListNew->nextTimestamp = timestampList;
        transaction->suiv = NULL;
        timestampListNew->transactions = transaction;

        timestampList = timestampListNew;
    }

    return timestampList;
}

/* Fonctions utilitaires */

/**
 * Retourne le maximum entre deux int.
 *
 * @param int a
 * @param int b
 * @return int
 */
int max(int a, int b) {
    if (a >= b)
        return a;
    else
        return b;
}

/**
 * Permet de manipuler une date en lui ajoutant ou soustrayant un nombre de jours.
 *
 * @param struct tm *date
 * @param int days
 */
void DatePlusDays(struct tm *date, int days) {
    const time_t ONE_DAY = 24 * 60 * 60;

    // Seconds since start of epoch
    time_t date_seconds = mktime(date) + (days * ONE_DAY);

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime(&date_seconds);;
}