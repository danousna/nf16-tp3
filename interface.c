#include "interface.h"
#include <limits.h>

BlockChain bc;

void afficherMenu() {
    int choix = 0;

    printf("\n====== Bienvenue sur EATCoins ======\n\nEntrez le numéro correspondant à la fonction :\n\n");
    printf("1. Afficher la liste des blocs de la BlockChain.\n");
    printf("2. Afficher toutes les transactions d'un bloc.\n");
    printf("3. Afficher toutes les transactions du jour d'un étudiant.\n");
    printf("4. Afficher l'historique d'un étudiant.\n");
    printf("5. Créditer un compte.\n");
    printf("6. Payer un repas.\n");
    printf("7. Transférer des EATCoins entre deux étudiants.\n");
    printf("8. Quitter\n");
    printf("9. Exporter toutes les transactions vers un fichier.\n");
    printf("10. Importer des transactions depuis un fichier.\n\n");

    do {
        printf("Choix : ");
        scanf("%d", &choix);
        while ((getchar()) != '\n');
    } while (choix < 1 || choix > 10);

    printf("\n");

    switch (choix) {
        case 1:
            printf("=== Affichage des blocks de la blockchain ===\n\n");
            afficherBlocks();
            printf("\n");
            boucle();
            break;
        case 2:
            printf("=== Affichage des transactions d'un Block ===\n\n");
            afficherTransactionsBlock();
            printf("\n");
            boucle();
            break;
        case 3:
            printf("=== Affichage des transactions du jour d'un étudiant ===\n\n");
            afficherTransactionsEtuJour();
            printf("\n");
            boucle();
            break;
        case 4:
            printf("=== Affichage de l'historique d'un étudiant ===\n\n");
            afficherHistoriqueEtu();
            printf("\n");
            boucle();
            break;
        case 5:
            printf("=== Créditer un compte ===\n\n");
            crediterCompte();
            printf("\n");
            boucle();
            break;
        case 6:
            printf("=== Payer un repas ===\n\n");
            payerRepas();
            printf("\n");
            boucle();
            break;
        case 7:
            printf("=== Transfert de EATCoins ===\n\n");
            transfertEtu();
            printf("\n");
            boucle();
            break;
        case 8:
            exit(0);
            break;
        case 9:
            printf("=== Exportation des transactions ===\n\n");
            exporterTransactions();
            printf("\n");
            boucle();
            break;
        case 10:
            printf("=== Importation de transactions ===\n\n");
            importerTransactions();
            printf("\n");
            boucle();
            break;
        default:
            printf("Erreur : choix non reconnu.\n");
            printf("\n");
            break;
    }
}

void boucle() {
    char choix;

    printf("Quitter ? (y/n) : ");
    scanf("%c", &choix);
    while ((getchar()) != '\n');

    if (choix == 'n')
        afficherMenu();
    else
        exit(0);
}

void afficherBlocks() {
    T_Block *currentBlock = bc;

    do {
        printf("Block #%d\n", currentBlock->id);
        currentBlock = currentBlock->suiv;
    } while (currentBlock != NULL);
}

void afficherTransactionsBlock() {
    int choix = 0;

    printf("Tous les blocks :\n\n");
    afficherBlocks();
    printf("\n");

    do {
        printf("Choix : ");
        scanf("%d", &choix);
        while ((getchar()) != '\n');
    } while (choix < 0 || choix > bc->id);

    printf("\n");
    printf("Affichage des transactions du Block #%d :\n", choix);

    T_Block *block = getBlock(choix, bc);

    T_Transaction *transaction = block->liste;



    while (transaction != NULL) {
        afficherTransaction(transaction);
        transaction = transaction->suiv;
    }
}

void afficherTransactionsEtuJour() {
    int choix = 0;

    printf("Le Block du jour : %d\n", bc->id);

    do {
        printf("ID de l'étudiant : ");
        scanf("%d", &choix);
        while ((getchar()) != '\n');
    } while (choix < 0 || choix > INT_MAX);

    printf("\n");
    printf("Affichage des transactions de l'étudiant %d pour le Block #%d :\n", choix, bc->id);

    T_Transaction *transaction = bc->liste;

    do {
        if (transaction->id == choix)
            afficherTransaction(transaction);
        transaction = transaction->suiv;
    } while (transaction != NULL);
}

void afficherHistoriqueEtu() {
    int choix = 0;

    do {
        printf("ID de l'étudiant : ");
        scanf("%d", &choix);
        while ((getchar()) != '\n');
    } while (choix < 0 || choix > INT_MAX);

    printf("\n");

    consulter(choix, bc);
}

void crediterCompte() {
    int id = 0;
    float montant = 0;
    char desc[255];

    do {
        printf("ID de l'étudiant : ");
        scanf("%d", &id);
        while ((getchar()) != '\n');
    } while (id < 0 || id > INT_MAX);

    printf("\n");

    do {
        printf("Montant à créditer : ");
        scanf("%f", &montant);
        while ((getchar()) != '\n');
    } while (montant < 0);

    printf("\n");

    printf("Description : \n");
    fgets(desc, 255, stdin);

    crediter(id, montant, desc, bc);

    afficherTransaction(bc->liste);
}

void payerRepas() {
    int id = 0;
    float montant = 0;
    char desc[255];

    do {
        printf("ID de l'étudiant : ");
        scanf("%d", &id);
        while ((getchar()) != '\n');
    } while (id < 0 || id > INT_MAX);

    printf("\n");

    do {
        printf("Montant à payer : ");
        scanf("%f", &montant);
        while ((getchar()) != '\n');
    } while (montant < 0);

    printf("\n");

    printf("Description : \n");
    fgets(desc, 255, stdin);

    if (payer(id, montant, desc, bc))
        afficherTransaction(bc->liste);
}

void transfertEtu() {
    int id1 = 0, id2 = 0;
    float montant = 0;
    char desc[255];

    do {
        printf("ID de l'étudiant 1 : ");
        scanf("%d", &id1);
        while ((getchar()) != '\n');
    } while (id1 < 0 || id1 > INT_MAX);

    printf("\n");

    do {
        printf("ID de l'étudiant 2 : ");
        scanf("%d", &id2);
        while ((getchar()) != '\n');
    } while (id2 < 0 || id2 > INT_MAX);

    printf("\n");

    do {
        printf("Montant à transférer : ");
        scanf("%f", &montant);
        while ((getchar()) != '\n');
    } while (montant < 0);

    printf("\n");

    printf("Description : \n");
    fgets(desc, 255, stdin);

    if (transfert(id1, id2, montant, desc, bc))
        afficherTransaction(bc->liste);
}

void exporterTransactions() {
    char fichier[100];

    printf("Nom du fichier : \n");
    fgets(fichier, 100, stdin);

    if (exporter(fichier, bc))
        printf("Exportation réussie.\n");
}

void importerTransactions() {
    char fichier[100];

    printf("Nom du fichier .txt à importer : \n");
    scanf("%100s", fichier);
    while ((getchar()) != '\n');

    BlockChain bc;

    if (bc = importer(fichier)) {
        printf("Importation réussie.\n");
    }
}