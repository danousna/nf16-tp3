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

int testCalculSoldeTotalNul(BlockChain blockChain);
int testCalculSoldeTotalNonNul(BlockChain blockChain);

int testCreditCompteVerifTransactionTeteBlock(BlockChain blockChain);

int testPayerRepasPasAssez(BlockChain blockChain);
int testPayerRepasAssezArgentNouvelleTransaction(BlockChain blockChain);

int testHistoriqueMoins5Transactions(BlockChain blockChain);
int testHistoriqueAucuneTransaction(BlockChain blockChain);
int testHistoriquePlus5HistoriquesChronologique(BlockChain blockChain);

int testTransfertPasAssezArgentOrgine(BlockChain blockChain);
int testTransfertReussi2TransactionsAttendues(BlockChain blockChain);

int testImportExportImmuables(BlockChain blockChain);

#endif //NF16_TP3_TESTS_H
