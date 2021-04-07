# PLD - Compilateur

## Lancer l'image docker

```
./run.sh
```

## Pour compiler dans Docker

```
cd compiler/
./compile_on_docker.sh
```

## Pour lancer les tests

```
cd tests/
./test_if.sh
```

## Fonctionnalités implémentées

 - Déclaration de variable (ex: int a,b,c;)
 - Le seul type géré est "int"
 - Initialisation d'une variable lors de la déclaration (ex: int a=42;)
 - Structure de bloc grâce aux accolades "{}"
 - Opérations arithmétiques de base : '+','-','*','/' et '-' unaire
 - Affectation qui retourne une valeur
 - Gestion des priorités et de l'associativité à gauche par défaut
 - Gestion des parenthèses "()"
 - Une seule fonction : le main --> int main() { ... }
 - La création d'autres fonctions (autre que main) est possible, cependant elles ne seront jamais appelées
 - Expressions : constantes entières, variables, expressions contenant des parenthèses et opérations arithmétiques de bases
 - Gestion des commentaires avec /* ... */

## Navigation dans notre code

Le dossier symbol-table contient les classes Context, Symbol et SymbolTable.
La classe Symbol représente une variable en mémoire avec son type, son nom et son adresse mémoire.
La classe Context représente un contexte d'exécution avec éventuellement un contexte parent, l'ajout d'une variable dans un contexte ne peut se faire que si aucune variable du même nom n'a été déclarée dans ce contexte ou dans un contexte parent.
La classe SymbolTable gère la table des symboles et permet de gérer les contextes courants (ajout de symbole ou récupération de symbole).

## Choix d'implémentation

Lors de la déclaration d'une variable sans affectation, la valeur de celle-ci est initialisée à 0 par soucis de simplicité et aussi car aucune norme n'existe en C et les compilateurs sont libres de faire ce qu'ils veulent.

La gestion de la mémoire n'est pas gérée de façon optimale et le code assembleur produit est plus long que celui de gcc.
Par exemple, l'instruction a=1+2+3 va créer 3 variables temporaires pour chacune des constantes qui seront compilées puis 2 autres vont être créées pour gérer les deux opérations résultant en la création de cinq variables temporaires au total. Nous n'avons pas amélioré ça pour ce livrable car en passant par l'IR plus tard on pourra s'en affranchir.

## Gestion de projet

Nous utilisons la méthode SCRUM et l'outil de gestion de projet JIRA. Le livrable de mi-parcours a constitué un sprint en lui-même.
Nous avons séparer les tâches : la moitié du groupe a travaillé sur le livrable de mi-parcours et l'autre moitié a travaillé pour anticiper les problématiques futurs que sont l'IR et l'AST.
Les deux équipes ont mis en commun leurs travaux pour avoir une base commune pour la suite où nous allons faire l'IR et l'AST en essayant d'anticiper au mieux l'évolution de la grammaire. Nous envisageons de faire 2 sprints : un pour l'élaboration de l'AST et l'IR avec l'ajout de certaines fonctionnalités (fonction, if, while, etc.) et un dernier pour ajouter les dernières fonctionnalités (tableaux, opérations bit à bit et fonctions standards).
Si le temps nous le permet, nous envisageons un dernier sprint pour l'ajout de fonctionnalités bonus.
