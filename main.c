#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"
#include "interface.h"
#include "tests.h"

int main()
{
    // initTests();

    atexit(liberer );

    // Déclaration de la blockchain en variable externe.
    extern BlockChain bc;

    // Block initial.
    bc = ajouterBlock(NULL);
    
    // Seed de la blockchain.
    bc = ajouterBlock(bc);
    bc = ajouterBlock(bc);
    crediter(1, 10, "Salut", bc);
    crediter(1, 10, "C'est la richesse !", bc);
    crediter(1, 10, "Encore plus", bc->suiv);
    crediter(2, 300, "Encore plus", bc->suiv);

    afficherMenu();
    
    return 0;
}