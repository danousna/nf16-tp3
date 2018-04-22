//
// Created by youtous on 21/04/18.
//

#include <assert.h>
#include "tests.h"

void initTests() {
    extern BlockChain bc;

    printf("Ajout du premier block de la blockChain... \n");
    assert(testBlockPremierId());

    printf("Ajout de blocks de la blockChain... \n");
    assert(testBlockSuivantId());

    printf("Ajout de la toute première transaction de la blockChain... \n");
    assert(testAjoutPremiereTransaction());

    printf("Ajout de plusieurs transactions dans la blockChain... \n");
    assert(testAjoutAutreTransactions());

    printf("Calcul du solde étudiant... \n");
    assert(testSommeCoinsJourneeEtudiantPasDeTransaction());
    assert(testSommeCoinsJourneeEtudiant());
}

int testAjoutPremiereTransaction() {
    BlockChain blockChain = ajouterBlock(NULL);

    // verification de l'initialisation
    assert(blockChain->suiv == NULL);
    assert(blockChain->liste->suiv == NULL);

    blockChain->liste = ajouterTransaction(0, 10, "Première transaction", blockChain->liste);
    // vérification qu'il n'y a qu'un seul block et qu'il ne contienne que notre transaction.

    assert (
            strcmp(blockChain->liste->desc, "Première transaction") == 0
            && blockChain->liste->montant == 10
            && blockChain->liste->id == 0
    );

    return 1;
}

int testAjoutAutreTransactions() {
    BlockChain blockChain = ajouterBlock(NULL);

    // verification de l'initialisation
    assert(blockChain->suiv == NULL);
    assert(blockChain->liste->suiv == NULL);

    blockChain->liste = ajouterTransaction(0, 10, "Première transaction", blockChain->liste);
    blockChain->liste = ajouterTransaction(1, 30, "Deuxième transaction", blockChain->liste);
    blockChain->liste = ajouterTransaction(2, 40, "Troisième transaction", blockChain->liste);

    assert (
            strcmp(blockChain->liste->desc, "Troisième transaction") == 0
            && blockChain->liste->montant == 40
            && blockChain->liste->id == 2
    );

    assert (
            strcmp(blockChain->liste->suiv->desc, "Deuxième transaction") == 0
            && blockChain->liste->suiv->montant == 30
            && blockChain->liste->suiv->id == 1
    );

    assert (
            strcmp(blockChain->liste->suiv->suiv->desc, "Première transaction") == 0
            && blockChain->liste->suiv->suiv->montant == 10
            && blockChain->liste->suiv->suiv->id == 0
    );

    return 1;
}

int testBlockPremierId() {
    BlockChain blockChain = ajouterBlock(NULL);

    // verification de l'initialisation
    assert(blockChain->suiv == NULL);
    assert(blockChain->id == 0);

    // verification liste vide transactions
    assert(blockChain->liste->suiv == NULL);
    assert(blockChain->liste->montant == 0);
    return 1;
}

int testBlockSuivantId() {
    BlockChain blockChain = ajouterBlock(NULL);
    blockChain = ajouterBlock(blockChain); // 1
    blockChain = ajouterBlock(blockChain); // 2
    blockChain = ajouterBlock(blockChain); // 3
    blockChain = ajouterBlock(blockChain); // 4

    return  blockChain->id == 4;
}

int testSommeCoinsJourneeEtudiantPasDeTransaction() {
    BlockChain blockChain = ajouterBlock(NULL);

    assert(totalTransactionEtudiantBlock(0, blockChain) == 0);
    assert(totalTransactionEtudiantBlock(3, blockChain) == 0);

    return 1;
}

int testSommeCoinsJourneeEtudiant() {
    BlockChain blockChain = ajouterBlock(NULL);

    crediter(3, 1000, "Init j1", blockChain);

    // on passe au jour suivant
    blockChain = ajouterBlock(blockChain);

    crediter(0, 1000, "Init j2", blockChain);
    crediter(2, 1000, "Init j2", blockChain);
    crediter(2, 1000, "Init j2", blockChain);
    crediter(2, 1000, "Init j2", blockChain);

    assert(totalTransactionEtudiantBlock(0, blockChain) == 1000);
    assert(totalTransactionEtudiantBlock(3, blockChain) == 0);
    assert(totalTransactionEtudiantBlock(2, blockChain) == 3000);

    return 1;
}

int testCalculSoldeTotalNul() {
    return 0;
}

int testCalculSoldeTotalNonNul() {
    return 0;
}

int testCreditCompteVerifTransactionTeteBlock() {
    return 0;
}

int testPayerRepasPasAssez() {
    return 0;
}

int testPayerRepasAssezArgentNouvelleTransaction() {
    return 0;
}

int testHistoriqueMoins5Transactions() {
    return 0;
}

int testHistoriqueAucuneTransaction() {
    return 0;
}

int testHistoriquePlus5HistoriquesChronologique() {
    return 0;
}

int testTransfertPasAssezArgentOrgine() {
    return 0;
}

int testTransfertReussi2TransactionsAttendues() {
    return 0;
}

int testImportExportImmuables() {
    return 0;
}
