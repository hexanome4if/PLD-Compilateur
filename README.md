# PLD - Compilateur

/!\ Aucune fonctionnalité n'a été ajoutée ou modifiée depuis la démonstration qui a été effectuée mercredi 7 avril. Cependant, le code a été un petit peu refactorisé afin de l'harmoniser. La grammaire n'a pas été modifiée et accepte donc certaines expressions qui ne sont en fait pas encore implémentées.

Certaines fonctionnalités n'ont pas été testées de manière exhaustive et peuvent donc présenter des bugs.

## Accès rapide

- [Documentation utilisateur](#documentation-utilisateur)
- [Fonctionnalités implémentées et choix d'implémentation](#fonctionnalités-implémentées-et-choix-dimplémentation)
- [Documentation développeur](#documentation-développeur)
- [Gestion de projet](#gestion-de-projet)
- [Intégration continue](#intégration-continue)

## Documentation utilisateur

### Utilisation basique

Ifcc permet de compiler un fichier C en Assembleur.

Pour ce faire, il suffit de lancer la commande :

```
./ifcc <nom du fichier c>
```

Qui aura pour effet d'afficher sur la sortie standard le code Assembleur généré. Les erreurs et les warnings éventuels sont affichés sur la sortie d'erreur.

Il est donc possible de récupérer ce code Assembleur pour le mettre dans un fichier .s de cette façon :

```
./ifcc <nom du fichier c> > <nom du fichier s>
```

Ensuite vous pouvez générer un fichier .o avec la commande :

```
as -o <nom du fichier o> <nom du fichier s>
```

Finalement vous pouvez générer un exécutable avec la commande :

```
gcc <nom du fichier o>
```

Que vous pourrez ensuite lancez comme vous le souhaitez.

### Optimisations

Afin d'optimiser le code Assembleur généré, vous pouvez utiliser l'option `-O`.

```
./ifcc <nom du fichier c> -O
```

### Visualisation de l'AST

Vous pouvez ajouter l'option `-AST` lorsque vous utilisez **ifcc** afin de visualiser l'AST généré ce qui peut être pratique lors du débogage.

Voici un exemple :

```
./ifcc <nom du fichier c> -AST
```

### Visualisation de l'IR

Cette fonctionnalité n'a pas été implémentée mais c'est une amélioration qui serait très intéressante surtout si le projet grossit. L'objectif serait de pouvoir visualiser l'IR en ajoutant une option (par exemple `-IR`) pour pouvoir débugger plus facilement.

Voici comment cela pourrait être fait :

```
./ifcc <nom du fichier c> -IR
```

La difficulté ici serait de trouver une représentation claire de l'IR étant donné que c'est un graphe. Une méthode serait peut-être d'afficher simplement les blocs dans l'ordre où ils sont stockés dans la classe _CFG_.

## Fonctionnalités implémentées et choix d'implémentation

Voici une liste des fonctionnalités implémentées :

- Types de données
  - int (32 bits)
  - int64_t (64 bits)
  - char (8 bits)
  - short (32 bits)
  - long (64 bits)
- Définitions de fonctions et de procédures avec plus ou moins de 6 paramètres
- Déclaration et initialisation de variables
  - Déclaration dans n'importe quel bloc
  - Initialisation lors de leur déclaration ou non
  - Déclaration et initialisation de plusieurs variables du même type grâce à une seule instruction (une seule ligne)
- Structures de contrôle
  - If, else
  - While
- Expressions
  - constante entière
  - caractère
  - variable
  - opérations
    - addition (+)
    - soustraction (-)
    - multiplication (\*)
    - division (/)
    - moins unaire (-)
    - parenthèses (())
  - affectation
- Affectation
- Tableaux à une dimension
- Utilisation des fonctions standard putchar et getchar
- Commentaires (// et /\* \*/)

### Types de données

Pour l'instant seulement des types de données représentant des entiers ont été implémentés.

Les types de données en 8 et en 64 bits n'ont pas été beaucoup testés et peuvent donc présenter des bugs.

### Définitions de fonctions et de procédures

Vous pouvez définir des fonctions ou des procédures avec autant de paramètres que vous le souhaitez.

Deux fonctions (ou procédures) ne peuvent pas avoir le même nom même si elles ont des signatures différentes, cela entraîne une erreur lors de la compilation.

Pour définir des procédures, il faut utiliser le mot clé **void**.

Une fonction doit forcément retourner une valeur avec une instruction **return** sinon une erreur va être lancée lors de la compilation.

Une procédure ne doit jamais retourner de valeur avec l'instruction **return** sinon une erreur va être lancée lors de la compilation.

Les deux règles précédentes sont des choix d'implémentations qui ont été choisis pour simplifier notre compilateur et ne pas avoir de cas ambigus à gérer.

Bugs connus :

- La présence de plusieurs **return** dans une fonction n'a pas l'effet auquel on pourrait s'attendre. En effet, l'instruction **return** n'arrête pas l'exécution de la fonction si l'on a deux **return**, la valeur retournée sera donc celle du deuxième.

### Déclaration et initialisation de variables

Notre compilateur laisse la possibilité de déclarer des variables à n'importe quel endroit dans un bloc. Il n'est donc pas possible pour l'instant de créer des variables globales.

`int a;`

Une variable peut être initialisée avec n'importe quelle expression au moment de sa déclaration.

`int a = 2;`

L'utilisation d'une variable non initialisée entraîne une erreur de compilation.

Plusieurs variables peuvent être déclarées et initialisées en même temps.

`int a = 2, b = c, d = 2 * 5, e;`

### Structures de contrôle

Pour l'instant, nous avons implémenté le **if...else** et la boucle **while**.

L'utilisation de **else if** n'est pas permise.

La condition dans le if et dans le while doit être une expression dont le résultat sera comparé avec 0.

Bugs connus

- La présence d'un _return_ dans un bloc et juste après ce bloc entraîne une erreur.

```c
if (a) {
    return 2;
} else {
    return 1;
}
return 3;
```

Ce programme retournera toujours 3.

### Expressions

La gestion des expressions arithmétiques de base est fonctionnelle (addition, multiplication, division, soustraction).

Le moins unaire a un problème de priorité ce qui le rend inutilisable dans une expression complexe sans l'utilisation de parenthèses.

Les expressions bitwise sont acceptées par notre grammaires (`&`, `^`, `|`) mais ne sont pas gérées par la suite et entraîneront donc sans doute des erreurs et ne renverront dans tous les cas pas le bon résultat.

La négation est acceptée par notre grammaire mais n'est pas gérée (`!`).

Les opérateurs paresseux (`||`, `&&`) sont acceptés par notre grammaire mais ne sont pas gérées par la suite.

Les expressions de comparaisons ont été implémentées (`==`, `!=`, `>`, `<`) mais n'ont pas été testées et peuvent donc présenter de nombreux bugs.

Nous savons qu'il y a un problème avec les opérateurs `>` et `<` mais nous n'avons pas plus d'informations pour l'instant (voir test _30_comparison_inf_sup.c_ qui ne passe pas).

L'affectation est fonctionnelle et peut être utilisée dans les expressions.

### Affectation

Comme précisé précédemment, l'affectation peut être utilisée dans une expression, mais elle peut aussi être utilisée comme une instruction.

`a = 2;`

La partie après le égal doit être une expression mais aucune autre restriction n'est imposée.

### Tableaux à une dimension

La gestion des tableaux à une dimension est entièrement fonctionnelle.

Il est donc possible de définir un tableau

`int a[4]={5, 4, 2, 6};`

La partie de définition des données initiale est optionnelle tant que la taille est spécifiée.

La taille du tableau est optionnelle tant que le tableau est initialisé.

La spécification d'une taille différente du nombre de données initiales entraînera la suppression des éléments en trop.

Les tableaux peuvent utiliser n'importe quel type défini plus haut.

Il est possible d'affecter une valeur dans une case d'un tableau

`a[1] = 5`

Ici le **1** et le **5** sont des expressions qui peuvent être de la forme que vous voulez.

L'affectation à un tableau ne retourne pas de valeurs et ne peut donc pas être utilisée dans une expression.

Dans les expressions, il est possible d'accéder à un élément d'un tableau.

`b = a[1]`

Il est possible d'utiliser cette notation dans une expression plus complexe sans problème.

Bugs connus :

- Retourner la valeur d'un élément d'un tableau qui n'est pas un entier de 32 bits entraîne un comportement anormal.

```c
char tab[1];

tab[0] = 12;

return tab[0];
```

Cette exemple ne retourne pas **12** contrairement à ce que l'on s'attend.
Ceci est dû à une conversion de type qui n'est pas bien gérée au niveau de la traduction en Assembleur x86.

- L'accès à la dernière case du tableau quand la taille n'a pas été fournie explicitement. On soupçonne qu'on alloue une case mémoire en moins.

```c
int tab[]={1,2,3,4,5,6};

return tab[5];
```
- Ceci n'est pas véritablement un bug mais plutôt un comportement normal qu'on juste pas bien cadré par manque de temps. Quand on "tronque" le tableau et que l'on tente d'accéder au contenu des cases qui n'ont pas été gardées, on a des résultats que l'on ne contrôle pas et notre compilateur ne lève pas de warning.

```c
int tab[3]={1,2,3,4,5,6};
return tab[4];
```

- Pareil quand le tableau n'est pas tronqué mais que, au contraire, la définition explicite n'intialise pas toutes les cases, GCC remplit par des zéros mais notre compilateur n'implémente pas de convention similaire et ce comportement n'est pas bien géré.

```c
int a[10] = {1,2,3,4} ;
return a[6];
```

### Utilisation des fonctions standard **putchar** et **getchar**

Il est possible d'utiliser les fonctions standard **putchar** et **getchar** afin d'intéragir avec l'utilisateur.

La fonction **putchar** n'est plus fonctionnelle et renvoie une erreur _Segmentation fault_ depuis l'ajout des dernières fonctionnalités. Nous n'avons pas encore pu investiguer la question.

### Commentaires

Les deux types de commentaires (ligne simple et multi-lignes) sont gérés.

```c
// This is a single line comment

/*
This is a multi
line comment
*/
```

## Documentation développeur

### Accéder à la plateforme de développement

Afin de faciliter le développement et pour que tous les développeurs travaillent dans le même environnement, nous recommandons l'utilisation de Docker. Voici comment s'y prendre :

#### Lancer l'image docker

```
./run.sh
```

#### Pour compiler dans Docker

```
cd compiler/
./compile_on_docker.sh
```

#### Pour lancer les tests

```
cd tests/
./test_if.sh
```

### Architecture du projet

Le projet est découpé en deux dossiers : _compiler_ et _tests_.

Tout le code se trouve dans le dossier _compiler_ et les différents tests se trouvent dans le dossier _tests_.

#### Les sources (dossier _compiler_)

Ce dossier contient toutes les sources du projet.

Tout d'abord, il y a un fichier _ifcc.g4_ qui sert de définition pour la grammaire que notre compilateur accepte.

Vous trouverez ensuite un fichier _main.cpp_ qui contient la gestion des différents paramètres fournis au compilateur ainsi que tout le processus menant à la génération du code assembleur à savoir :

- Parsing du fichier C en entrée
- Constitution de la table des symboles
- Vérification des erreurs
- Génération de l'AST
- Optimisation facultative de l'AST
- Génération de l'IR depuis l'AST
- Transformation de l'AST en Assembleur x86

Nous allons voir juste après comment sont gérées ces différentes parties.

Finalement, vous trouverez un fichier _Makefile_ qui permet la compilation du projet en un exécutable nommé _ifcc_.

##### Parsing du fichier C en entrée

Afin de parser le fichier en entrée, nous utilisons la librairie Antlr4 qui nous génère un arbre et qui retourne des erreurs si des problèmes par rapport à la grammaire sont détectés.

##### Constitution de la table des symboles

La table des symboles est constituée à partir d'un visiteur présent dans le fichier _visitors/SymbolVisitor.(h|cpp)_.

Dans ce visiteur, nous pouvons "visiter" chaque nœud de l'arbre généré par Antlr4. Avec cette technique, nous constituons une table des symboles complètes comprenant à la fois les différentes fonctions définies dans le code et les différentes variables. Chacun de ces symboles n'est valide que dans un certain contexte représenté par la classe définie dans le fichier _symbols-management/Context.h_.

Pour faire simple, la table des symboles repose principalement sur trois classes :

- Symbol définie dans le fichier _symbols-management/Symbol.h_, une classe abstraite définissant un symbole
- Context définie dans le fichier _symbols-management/Context.h_, une classe représentant un contexte d'exécution et comprenant une liste de symboles. Un contexte possède un contexte parent et une liste de contextes enfants. Un symbole définit dans un contexte est utilisable dans ce contexte ainsi que dans tous les descendants de ce contexte.
- SymbolTable définie dans le fichier _symbols-management/SymbolTable.h_, une classe contenant le contexte courant ainsi que le contexte principal (root) et permettant d'accéder ou de créer des symboles, ainsi que des contextes.

Dans le dossier _symbols-management_ vous trouverez également deux autres fichier nommés _FuncSymbol.h_ et _VarSymbol.h_ qui sont en fait des spécialisations de la classe _Symbol_ et qui définissent les attributs propres à un symbole de type **fonction** et un symbole de type **variable**, libre à vous d'en ajouter d'autres si cela est pertinent.

Finalement, le dossier contient un fichier _type.h_ qui définit les différents types de données disponibles (char, int, double, ...), et différentes fonctions en lien avec ces types. Ce fichier n'est pas forcément bien placé, libre à vous de lui trouver une place plus pertinente.

##### Vérifications des erreurs

Certaines erreurs sont directement gérées au moment de la création de la table des symboles car elles sont directement en lien avec celle-ci. Par exemple, les erreurs de symboles utilisés sans avoir été déclarés ou de symboles déclarés plusieurs fois sont gérées à cet endroit.

Les autres erreurs sémantiques doivent être gérées par le visiteur _visitors/ErrorVisitor.(h|cpp)_. Dans chacun des visiteurs, il est possible d'appeler une méthode nommée _throwError()_ qui prend en paramètre un pointeur vers un objet de la classe _AbstractError_ définie dans le fichier _error-management/AbstractError.h_.

Cette méthode permet d'ajouter une nouvelle erreur qui pourra ensuite être affichée à l'utilisateur. Ensuite libre à vous d'arrêter l'exécution du visiteur ou de poursuivre en fonction de la gravité de l'erreur.

Pour définir une nouvelle erreur, il suffit de se rendre dans le dossier _error-management_ et de créer une nouvelle class spécialisant la class _AbstractError_ et implémentant la méthode _getMessage()_ qui doit renvoyer une chaîne de caractères explicite pour l'utilisateur. Des exemples d'implémentations sont disponibles dans les dossiers _error-management/func_ et _error-management/symbol_.

Lorsque une erreur est enregistrée via la méthode _throwError()_, elle est ajoutée dans un objet de la classe _ErrorManager_ définie dans le fichier _error-management/ErrorManager.h_ qui va ensuite fournir différentes méthodes pour traiter les éventuelles erreurs.
Cet objet peut être récupéré depuis un visiteur en appelant la méthode _getErrorManager()_ définie dans le fichier _visitors/BaseVisitor.h_.

##### Génération de l'AST

Nous utilisons encore le principe des visiteurs pour générer l'AST. Le visiteur que nous utilisons est définit dans les fichiers _visitors/AstVisitor.(h|cpp)_.

L'AST (Abstract Syntax Tree) permet de représenter le code de l'utilisateur (code C) par un arbre un peu comme celui généré par Antlr4 mais nous allons pouvoir faire différentes optimisations sur celui-ci vu que nous pouvons l'implémenter comme bon nous semble.

Les différentes classes pour réprésenter l'AST sont disponibles dans le dossier _ast_, libre à vous d'en ajouter.
Dans ce dossier, nous pouvons trouver une classe _Ast_ définit dans les fichiers _Ast.(h|cpp)_ qui représente la racine de notre arbre et contient une liste de nœuds (_Node_) qui sont en fait les fonctions définies par l'utilisateur.
Il faudrait ajouter à cette liste les affectations des variables globales hors des fonctions.

Comme précisé précédemment, il est possible de visualiser l'AST en ajouter l'option **-AST** lors de l'utilisation du compilateur. Ce qui permet de débugger plus facilement.

##### Optimisation facultative de l'AST

Nous avons laissé la possibilité à l'utilisateur de choisir si il souhaite que le code Assembleur produit soit optimisé ou non.
Pour l'instant, toutes les optimisations sont faites au niveau de l'AST, mais dans le futur, il faudrait envisager des optimisations au niveau de l'IR également.

Dans un souci de simplicité, les optimisations de l'AST sont implémentées directement au sein de l'AST mais si le projet grossit, il serait plus pertinent de créer de nouvelles classes responsables uniquement de ces optimisations afin de décharger l'AST.

Pour l'instant, nous offrons deux optimisations différentes :

- Suppressions des symboles inutilisés
- Calcul des expressions à l'avance si possible

Il serait intéressant de regrouper ces deux optimisations car elles sont complémentaires. Pour l'instant nous exécutons la première avant d'exécuter la deuxième. Il serait plus intelligent de faire l'inverse car en calculant les expressions, nous pouvons ne plus utiliser certains symboles qui ne vont donc pas être supprimés.

Pour supprimer les symboles non utilisés, nous utilisons une méthode sur les instructions (classe abstraite _Instr_) nommée _removeUnusedSymbols()_ qui prend en paramètre une fonction permettant de supprimer l'instruction si besoin et le contexte actuel. Cette méthode retourne un entier représentant le nombre d'instructions supprimées. Cette méthode doit parcourir l'arbre jusqu'en bas mais ne concerne seulement les instructions et pas les expressions. Cette méthode n'a un réel impact que dans la classe _Aff_ qui va vérifier si la variable affectée est bien utilisée et se supprimer elle-même si ce n'est pas le cas.

Pour que cette optimisation fonctionne bien, il faut absolument que les symboles utilisés soient bien marqués comme tel au niveau de leur définition dans le visiteur _SymbolVisitor_ en appelant la méthode _used()_ à chaque fois que le symbole est utilisé.

Pour calculer les expressions à l'avance, nous avons tout d'abord besoin de calculer le graphe de dépendance des différentes variables, pour ce faire, une méthode est définie à la fois pour les instructions et les expression nommée _computeVarDependencies()_ qui génère le graphe directement dans la classe _VarSymbol_.

Ensuite, il est possible d'appeler la méthode _calculateExpressions()_ sur les différents noeuds (_Node_) qui va parcourir l'AST complètement et appeler la méthode _getGuessedValue()_ sur les expressions qui renverra soit le mot clé _"undefined"_ soit la valeur trouvée. Au niveau des nœuds, il est alors possible de remplacer l'expression de base par une constante dans le cas où une valeur à été devinée.

Les optimisations n'ont pas encore été implémentés au niveau des tableaux et des opérateurs de comparaisons.

Pour plus de clareté sur ces deux améliorations, nous vous recommandons de regarder l'implémentation des différentes méthodes présentées ci-dessus pour mieux comrpendre le processus. Il est aussi intéressant de regarder les méthodes dans la classe _Ast_ pour voir d'où proviennent les appels.

##### Génération de l'IR à partir de l'AST

Une fois que l'AST a été généré (et peut être optimisé), nous pouvons générer l'IR (Intermediate Representation). L'IR est un graphe représentant les différents blocs qui vont ensuite constituer le code Assembleur.

Notre IR se base sur deux classes :

- _BasicBlock_ (définie dans les fichiers _ir/BasicBlock.(h|cpp)_)
- _IRInstr_ (définie dans les fichiers _ir/IRInstr.(h|cpp)_)

Le graphe est représenté uniquement par les _BasicBlock_ qui vont contenir des _IRInstr_. Un _BasiBlock_ représente une suite d'_IRInstr_. Pour chaîner les _BasicBlock_ entre eux, la classe possède deux attributs nommés _exit_true_ et _exit_false_ contenant un pointeur vers un autre bloc.

Pour générer l'IR, différentes classes sont définies dans le dossier _ir/generator_ ces classes vont permettre le parcours de l'AST et la génération de l'IR, libre à vous d'en ajouter des nouvelles.

Les _IRInstr_ représentent des instructions très simples qui se traduisent très facilement en Assembleur.

Finalement, l'IR peut se résumer par une liste de _BasicBlock_ qui va être stockée dans la classe _CFG_ définie dans les fichiers _ir/CFG.(h|cpp)_.

Nous vous recomandons d'aller parcourir rapidement le code des différents fichiers présents dans le dossier _ir_ afin de mieux comprendre comment est générée et comment fonctionne notre IR.

##### Transformation de l'IR en Assembleur x64

Toute la traduction de l'IR en Assembleur est située dans le dossier _assembly-translation_. Une classe abstraite nommée _Translator_ définit les méthodes qui doivent être implémentées pour générer le code Assembleur lors du parcours de l'IR.

Pour l'instant nous n'avons implémenté que la classe _X86Translator_ qui permet de générer du code Assembleur x86 mais libre à vous d'ajouter d'autre classe spécialisant _Translator_ pour gérer d'autre langages Assembleur (arm, msp430, ...).

Nous vous recommandons de regarder les méthodes définies dans la classe _Translator_ et de regarder rapidement l'implémentation faites dans la classe _X86Translator_ afin de bien comprendre le processus de traduction.

#### Les tests

La gestion de nos tests est loin d'être optimale et une refactorisation est nécessaire avant de continuer le projet.

Si vous vous rendez dans le dossier _tests_ vous trouverez un autre dossier _tests_ contenant l'ensemble des tests et un fichier _test_if.sh_ qui permet de lancer les tests.

Lorsque vous lancez les tests avec la commande `./test_if.sh` un dossier _pld-test-output_ est généré avec les résultats.

Pour l'instant, notre dossier _tests_ ne contient qu'un dossier _Init_ qui contient tous nos tests. Il faudrait plutôt avoir un dossier pour les tests de chacune des fonctionnalités.

Il faudrait aussi que l'on ai beaucoup plus de tests afin de ne pas manquer certaines fonctionnalités.

Un fichier de test n'est rien d'autre qu'un fichier C qui va être compilé à la fois par notre compilateur (`ifcc`) et par `gcc`. La sortie de notre compilateur doit être la même que celle de `gcc`.

## Gestion de projet

Nous utilisons la méthode SCRUM et l'outil de gestion de projet JIRA.

Le livrable de mi-parcours a constitué un sprint en lui-même.
Nous avons séparé les tâches : la moitié du groupe a travaillé sur le livrable de mi-parcours et l'autre moitié a travaillé pour anticiper les problématiques futures que sont l'IR et l'AST.

Les deux équipes ont mis en commun leurs travaux pour avoir une base commune pour la suite où nous allons faire l'IR et l'AST en essayant d'anticiper au mieux l'évolution de la grammaire.

Après la livraison du livrable de mi-parcours, nous avons séparé le groupe en trois équipes dès que possible avec une première qui travaillait sur la génération de l'AST, une deuxième sur la génération de l'IR et une troisième sur la génération de l'Assembleur x86.

Une fois que les trois équipes ont réussi à se resynchroniser au niveau du livrable de mi-parcours, donc avec les mêmes fonctionnalités qu'à mi-parcours mais avec notre nouvelle architecture. Nous avons constitué de nouvelles équipes pour travailler en parallèle sur les nouvelles fonctionnalités.

Les nouvelles fonctionnalités étaient :

- Gestion des fonctions
- Gestion des structures de contrôle
- Ajout des nouveaux types
- Ajout des tableaux
- Ajout des opérateurs de comparaisons
- Ajout des opérateurs bit à bit
- Ajout des fonctions standard putchar et getchar

Nous avons réussi à implémenter la majeure partie de ces fonctionnalités mais nous n'avons pas bien testé notre code par manque de temps ce qui nous a mis dans une situation délicate où nous avions beaucoup de fonctionnalités mais avec des bugs.

Dans le futur il faudrait peut-être commencer par écrire les tests (faire du TDD) afin de se forcer à avoir des tests explicites et ne pas repousser à plus tard.

Nous avons également fait une grosse refactorisation trois jours avant la démonstration ce qui n'a pas forcément aidé l'équipe à court terme. Ce genre de refactorisation aurait dû être faite plus tôt, après la présentation ou avec toute l'équipe afin qu'il y ait moins de confusion.

## Intégration continue

Nous utilisons GitLab pour gérer l'intégration continue et tester notre code.

Un pipeline est déclenché à chaque fois que des modifications sont apportées sur la branche `master`.

Notre groupe avait l'habitude de travailler avec GitHub et nous ne souhaitions pas tout bousculer. Nous avons donc choisi de mettre notre code sur GitHub mais de créer un miroir sur GitLab afin de bénéficier de l'intégration continue offerte par GitLab tout en utilisant GitHub.

Voici les adresses des deux dépots :

- GitLab : https://gitlab.insa-lyon.fr/hexaordinaire/pld-compilateur

  Nécessite d'être connecté au VPN de l'INSA

- GitHub : https://github.com/hexanome4if/PLD-Compilateur
