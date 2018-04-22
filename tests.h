//
// Created by youtous on 21/04/18.
//

#ifndef NF16_TP3_TESTS_H
#define NF16_TP3_TESTS_H

#include "blockchain.h"

void initTests();

int testAjoutPremiereTransaction();
int testAjoutAutreTransactions();

int testBlockPremierId();
int testBlockSuivantId();

int testSommeCoinsJourneeEtudiantPasDeTransaction();
int testSommeCoinsJourneeEtudiant();

int testCalculSoldeTotalNul();
int testCalculSoldeTotalNonNul();

int testCreditCompteVerifTransactionTeteBlock();

int testPayerRepasPasAssez();
int testPayerRepasAssezArgentNouvelleTransaction();

int testHistoriqueMoins5Transactions();
int testHistoriqueAucuneTransaction();
int testHistoriquePlus5HistoriquesChronologique();

int testTransfertPasAssezArgentOrgine();
int testTransfertReussi2TransactionsAttendues();

int testImportExportImmuables();

#endif //NF16_TP3_TESTS_H
