# NF16 - TP3 - Blockchain
NF16 - TP3 - BlockChain

### Todo :
- complexité des fonctions demandées (Léo) (Natan : j'ai un peu commencé).
- expliquer la modification du prototype de la fonction `float totalTransactionEtudiantBlock(int idEtu, T_Block * b)` (pointeur T_Block au lieu T_Block)

_Le but de ce TP est d'implémenter une BlockChain simplifiée. Une blockchain permet le stockage d'informations (pas forcément financières) de manière décentralisée. C'est une base de données distribuée. L'intérêt de cette technologie est qu'elle est pratiquement impossible à altérer, en effet la liste des transactions étant chaînée, chaque bloc contient la signature numérique du bloc précédent (et par conséquent si l'on modifie un bloc, la signature des blocs change)._

## Choix d'architecture

### Organisation du projet
Du point de vue de l'organisations du projet, nous avons choisis de séparer celui-ci en trois fichiers. 

Le premier étant `blockchain.c` qui contient toutes les fonctions nécessaires au fonctionnement de la blockchain (dans le cadre d'une architecture MVC, ce serait le modèle).

Le second est `interface.c` qui agit comme l'interface entre l'utilisateur et la blockchain. Il contient toutes les fonctions permettant d'utiliser les 10 options demandées (ce fichier agit comme controller et comme vue).

Le dernier est le `main.c`  qui initialise la blockchain et utilise les fonctions d'interface pour afficher le menu.

Lors du développement, nous avons ajouté nos tests dans le fichier `tests.c`, la fonction `initTests();` de ce fichier lance l'ensemble des tests.

### Structure supplémentaire

**Timestamp** est une structure agissant comme un block d'une liste chainée :
```
typedef struct Timestamp {
    long timestamp;
    struct Transaction *transactions;
    struct Timestamp *nextTimestamp;

}
```
Il regroupe la liste des transactions pour un _timestamp_ (date) donné. Nous avons eu besoin de construire une liste ordonnée des transactions lors de l'importation, cette structure nous a permis d'obtenir une solution d'organisation des transactions flexible.

Aussi, notre fichier d'exportation liste les transactions de la plus récente à la plus ancienne. Lors de l'importation, au meilleur cas, le fichier sera trié de la même manière que notre exportation.
Ainsi lors de la lecture ligne par ligne du fichier, on pourra construire notre liste en commençant par les blocs les plus récents pour finir par les plus anciens.
Une fois la liste construite, il suffit de lire de manière linéaire la liste pour reconstruire la blockchain, on s'épargne ainsi un tri car ce dernier est effectué directement lors de la construction de la liste chainée et triée du plus ancien au plus récent (timestamp le plus petit au plus grand).

_timestamp_ : **POSIX timestamp**   Il s'agit du nombre de secondes écoulées depuis le 1er janvier 1970 00:00:00 UTC jusqu'à l'événement à dater, hors secondes intercalaires. (source [Wikipedia - Heure Unix](https://fr.wikipedia.org/wiki/Heure_Unix))

### Fonctions supplémentaires
#### `blockchain.c`
Fonctions supplémentaires : 

- `T_Block *getBlock(int id, BlockChain bc);` qui permet de récupérer plus simplement un block en renseignant son `id`. Cette fonction nous est utile dans le fichier interface pour afficher les transactions d'un block spécifique.

- `void liberer();` qui permet de libérer l'espace mémoire occupé par la blockchain. Cette fonction parcourt la blockchain et toutes les transactions et libère celles-ci puis le block correspondant. Elle est appelée dans le `main.c` avec un `atexit()` ce qui permet, en cas d'arrêt normal du programme, de libérer la mémoire. 

- `void freeTimestamp(T_Timestamp *timestamp); ` de la même manière que `liberer()` cette fonction libère l'espace mémoire utilisé par la liste chainée de Timestamp utilisée lors de l'importation. Elle est appelée dans la fonction `importer(char* fileName)`.

- `int max(int a, int b);` est une fonction utilitaire permettant de retourner le maximum entre 2 entiers.

- `DatePlusDays(struct tm *date, int days);` est une fonction utilitaire permettant de modifier une date en lui ajoutant ou soustrayant un nombre de jours.

- `T_Timestamp *insert(long timestamp, T_Transaction *transaction, T_Timestamp *timestampList);` permet d'insérer un Block de Timestamp dans la liste chainée `timestampList`. Si cette liste est nulle, la liste est créée. Un `T_Timestamp` est une structure sous forme de liste chaînée qui permet de contenir de manière chronologique des transactions.

#### `interface.c`

Mise à part les fonctions correspondant aux 10 options et la fonction d'affichage du menu, nous avons crée une fonction `void boucle();` qui permet de demandé à l'utilisateur si il veut quitter ou non à la fin de chacune des options. On ré-affiche le menu si il souhaite continuer.

#### `tests.c`

Ce fichier contient l'ensemble des tests qui assurent le bon comportement de la Blockchain. Seules les fonctions de `blockchain.c` ont été testées de cette manière. Il est possible de lancer les tests avec la fonction `initTests();` .

## Complexité des fonctions

Nous traiteront uniquement les fonctions relatives à la blockchain et non les fonctions d'interface.
Les fonctions de tests n'ayant qu'une utilité lors de développements, leur complexité ne sera pas abordée non plus.

### ajouterTransaction();

La fonction effectue des affectations simples. La complexité est donc : **O(1)**.

### ajouterBlock();

Pareil, **O(1)**.

### totalTransactionEtudiantBlock();

Soit `n` le nombre de transactions dans le block `b`, avec une boucle while, on aura donc une complexité **O(n)**.

### soldeEtudiant();

Soit `m` le nombre de blocks dans la blockchain `bc`, `n` le nombre de transactions dans ces blocks, la double boucle `while` nous donne une complexité **O(n\*m)**. 

### crediter();

**O(1)**.

### payer();

Dans la condition `if`, on utilise la fonction `soldeEtudiant()`, la complexité est donc : **O(n\*m)**.

### consulter();



### transfert();

**O(n\*m)** à cause de la fonction `soldeEtudiant()`.

### afficherTransaction();

**O(1)**.

### getBlock();

**O(n)**.

### liberer();

**O(n\*m)**.