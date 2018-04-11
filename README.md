# NF16 - TP3 - BlockChain

### Todo :
- complexité des fonctions demandées (Léo)
- export/import fichiers (Léo)

Le but de ce TP est d'implémenter une BlockChain simplifiée. Une blockchain permet le stockage d'informations (pas forcément financières) de manière décentralisée. C'est une base de données distribuée. L'intérêt de cette technologie est qu'elle est pratiquement impossible à hacker.

## Choix d'architecture

### Organisation du projet
Du point de vue de l'organisations du projet, nous avons choisis de séparer celui-ci en trois fichiers. 

Le premier étant `blockchain.c` qui contient toutes les fonctions nécessaires au fonctionnement de la blockchain (dans le cadre d'une architecture MVC, ce serait le modèle).

Le second est `interface.c` qui agit comme l'interface entre l'utilisateur et la blockchain. Il contient toutes les fonctions permettant d'utiliser les 10 options demandées (ce fichier agit comme controller et comme vue).

Le dernier est le `main.c`  qui popule la blockchain et utilise les fonctions d'interface pour afficher le menu.

### Fonctions supplémentaires
#### `blockchain.c`
Deux fonctions en plus : 
- `T_Block *getBlock(int id, BlockChain bc);` qui permet de récupérer plus simplement un block en renseignant son `id`. Cette fonction nous est utile dans le fichier interface pour afficher les transactions d'un block spécifique.
- `void liberer();` qui permet de libérer l'espace mémoire occupé par la blockchain. Cette fonction parcourt la blockchain et toutes les transactions et libère celles-ci puis le block correspondant. Elle est appelée dans le `main.c` avec un `atexit()` ce qui permet, en cas d'arrêt normal du programme, de libérer la mémoire. 

#### `interface.c`

Mise à part les fonctions correspondant aux 10 options et la fonction d'affichage du menu, nous avons crée une fonction `void boucle();` qui permet de demandé à l'utilisateur si il veut quitter ou non à la fin de chacune des options. On réaffiche le menu si il souhaite continuer.

## Complexité des fonctions


