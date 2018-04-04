#include "interface.h"

void afficherMenu()
{
    int choix = 0;

    printf("\n====== Bienvenue sur EATCoins ======\n\nEntrez le numéro correspondant à la fonction :\n\n");
    printf("1. Afficher la liste des blocs de la BlockChain.\n");
    printf("2. Afficher toutes les transactions d'un bloc.\n");
    printf("3. Afficher toutes les transactions du jour pour un étudiant.\n");
    printf("4. Afficher l'historique pour un étudiant.\n");
    printf("5. Créditer un compte.\n");
    printf("6. Payer un repas.\n");
    printf("7. Transférer des EATCoins entre deux étudiants.\n");
    printf("8. Quitter\n");
    printf("9. Exporter toutes les transactions vers un fichier.\n");
    printf("10. Importer des transactions depuis un fichier.\n\n");

    do
    {   
        printf("Choix : ");
        scanf("%d", &choix);
        while ((getchar()) != '\n');
    } while(choix < 1 || choix > 10);

    printf("\n");

    switch (choix)
    {
        case 1:
            afficherBlocks();
            printf("\n");
            break;
        case 2:
            afficherTransactionsBlock();
            printf("\n");
            break;
        case 3:
            afficherTransactionsEtuJour();
            printf("\n");
            break;
        case 4:
            afficherHistoriqueEtu();
            printf("\n");
            break;
        case 5:
            crediterCompte();
            printf("\n");
            break;
        case 6:
            payerRepas();
            printf("\n");
            break;
        case 7:
            transfertEtu();
            printf("\n");
            break;
        case 8:
            exit(0);
            break;
        case 9:
            // Export
            printf("\n");
            break;
        case 10:
            // Import
            printf("\n");
            break;
        default:
            printf("Erreur : choix non reconnu.\n");
            printf("\n");
            break;
    }
}

void afficherBlocks()
{
    BlockChain bc = getBlockChain();

    T_Block *currentBlock = bc;

    printf("=== Affichage des blocks de la blockchain ===\n\n");

    do {
        printf("Block #%d\n", currentBlock->id);
        currentBlock = currentBlock->suiv;
    } while (currentBlock != NULL);    
}

void afficherTransactionsBlock()
{

}

void afficherTransactionsEtuJour()
{

}

void afficherHistoriqueEtu()
{

}

void crediterCompte()
{

}

void payerRepas()
{

}

void transfertEtu()
{

}