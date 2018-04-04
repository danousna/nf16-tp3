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

    consulter(1, bc);

    return 0;
}