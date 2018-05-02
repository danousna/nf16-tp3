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

    printf("Calcul du solde total... \n");
    assert(testCalculSoldeTotalNonNul());
    assert(testCalculSoldeTotalNul());

    printf("Credit du compte... \n");
    assert(testCreditCompteVerifTransactionTeteBlock());

    printf("Payer un repas... \n");
    assert(testPayerRepasAssezArgentNouvelleTransaction());
    assert(testPayerRepasPasAssez());

    printf("Affichage historique... \n");
    assert(testHistoriqueAucuneTransaction());
    assert(testHistoriqueMoins5Transactions());
    assert(testHistoriquePlus5HistoriquesChronologique());

    printf("Transfert argent... \n");
    assert(testTransfertPasAssezArgentOrgine());
    assert(testTransfertReussi2TransactionsAttendues());

    printf("Import/Export... \n");
    assert(testImportExportImmuables());
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

    return blockChain->id == 4;
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
    BlockChain blockChain = ajouterBlock(NULL);

    // on passe au jour suivant
    blockChain = ajouterBlock(blockChain);

    assert(totalTransactionEtudiantBlock(10, blockChain) == 0);
    return 1;
}

int testCalculSoldeTotalNonNul() {
    BlockChain blockChain = ajouterBlock(NULL);

    crediter(10, 100, "credit", blockChain);
    crediter(11, 0, "credit", blockChain);
    crediter(12, 100, "credit", blockChain);

    assert(transfert(11, 10, 0.230, "transfert", blockChain) == 0);

    assert(soldeEtudiant(10, blockChain) == 100);
    assert(soldeEtudiant(11, blockChain) == 0);

    // on passe au jour suivant
    blockChain = ajouterBlock(blockChain);

    transfert(10, 12, 20.230, "transfert", blockChain);



    // TODO : check les décimales
    // assert(soldeEtudiant(10, blockChain) == 79.770);
    // assert(soldeEtudiant(11, blockChain) == 101.770);
    // assert(soldeEtudiant(12, blockChain) == 120.460);
    return 1;
}

int testCreditCompteVerifTransactionTeteBlock() {
    BlockChain blockChain = ajouterBlock(NULL);

    assert (
             blockChain->liste->montant == 0
            && blockChain->liste->id == 0
    );
    crediter(10, 100, "credit", blockChain);

    assert(blockChain->liste->id == 10 &&
           blockChain->liste->montant == 100 &&
           strcmp(blockChain->liste->desc, "credit") == 0
    );
    return 1;
}

int testPayerRepasPasAssez() {
    BlockChain blockChain = ajouterBlock(NULL);

    assert(payer(10, 10, "repas à payer", blockChain) == 0);
    return 1;
}

int testPayerRepasAssezArgentNouvelleTransaction() {
    BlockChain blockChain = ajouterBlock(NULL);


    crediter(10, 100, "credit", blockChain);

    assert(payer(10, 10, "repas à payer", blockChain) == 1);

    assert(soldeEtudiant(10, blockChain) == 90);
    return 1;
}

int testHistoriqueMoins5Transactions() {
    BlockChain blockChain = ajouterBlock(NULL);
    crediter(10, 100, "credit", blockChain);
    assert(payer(10, 10, "repas à payer 1", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 2", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 3", blockChain) == 1);

    consulter(10, blockChain);

    return 1;
}

int testHistoriqueAucuneTransaction() {
    BlockChain blockChain = ajouterBlock(NULL);

    consulter(10, blockChain);
    return 1;
}

int testHistoriquePlus5HistoriquesChronologique() {
    BlockChain blockChain = ajouterBlock(NULL);
    crediter(10, 100, "NE DOIT PAS APPARAITRE", blockChain);
    assert(payer(10, 10, "repas à payer 1", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 2", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 3", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 3", blockChain) == 1);
    assert(payer(10, 10, "repas à payer 3", blockChain) == 1);

    consulter(10, blockChain);

    return 1;
}

int testTransfertPasAssezArgentOrgine() {
    BlockChain blockChain = ajouterBlock(NULL);

    crediter(10, 100, "credit", blockChain);
    crediter(11, 0, "credit", blockChain);

    assert(transfert(11, 10, 0.230, "transfert", blockChain) == 0);

    return 1;
}

int testTransfertReussi2TransactionsAttendues() {
    BlockChain blockChain = ajouterBlock(NULL);

    crediter(10, 0, "credit", blockChain);
    crediter(11, 100, "credit", blockChain);

    assert(transfert(11, 10, 100, "transfert", blockChain) == 1);

    assert(soldeEtudiant(10, blockChain) == 100);
    assert(soldeEtudiant(11, blockChain) == 0);

    assert(blockChain->liste->id == 10 &&
            blockChain->liste->montant == 100);

    assert(blockChain->liste->suiv->id == 11 &&
           blockChain->liste->suiv->montant == -100);

    return 1;
}

int testImportExportImmuables() {
    BlockChain blockChain = ajouterBlock(NULL);
    crediter(10, 0, "credit", blockChain);
    crediter(11, 100, "credit", blockChain);
    payer(10, 10, "repas à payer 1", blockChain);
    blockChain = ajouterBlock(blockChain);
    payer(10, 10, "repas à payer 2", blockChain);
    blockChain = ajouterBlock(blockChain);
    crediter(10, 333, "credit du premier jour", blockChain);
    crediter(11, 393, "credit du premier jour", blockChain);


    assert(export("export.txt", blockChain) == 1);
    return 1;
}
