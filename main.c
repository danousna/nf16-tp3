#include <stdio.h>
#include "tp3.h"



BlockChain getBlockChain()
{
    static BlockChain bc;

    if(bc == NULL) {
        bc = ajouterBlock(bc);
    }

    return bc;
}

int main()
{
    BlockChain bc = getBlockChain();

    crediter(1, 10, "Salut", bc);
    crediter(1, 10, "C'est la richesse !", bc);
    crediter(1, 10, "Encore plus", bc);
    crediter(1, 10, "C'est fini", bc);

    consulter(1, bc);

    return 0;
}