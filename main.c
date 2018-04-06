#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"
#include "interface.h"

int main()
{
    atexit(liberer );

    extern BlockChain bc;

    // Seed de la blockchain.  
    bc = ajouterBlock(bc);
    bc = ajouterBlock(bc);
    bc = ajouterBlock(bc);

    crediter(1, 10, "Salut", bc);
    crediter(1, 10, "C'est la richesse !", bc);
    crediter(1, 10, "Encore plus", bc->suiv);

    afficherMenu();
    
    return 0;
}