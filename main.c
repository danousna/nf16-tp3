#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"
#include "interface.h"

int main()
{
    // Création de la blockchain.
    BlockChain bc = getBlockChain();

    // Seed de la blockchain.  
    bc = ajouterBlock(bc);
    bc = ajouterBlock(bc);
    bc = ajouterBlock(bc);

    crediter(1, 10, "Salut", bc);
    crediter(1, 10, "C'est la richesse !", bc);
    crediter(1, 10, "Encore plus", bc->suiv);
    crediter(1, 10, "C'est fini", bc->suiv->suiv);

    afficherMenu();
    
    return 0;
}