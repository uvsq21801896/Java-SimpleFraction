# Exercices build

Le projet intial contient uniquement des sources Java.
Le répertoire `src` contient les sources de la classe `Compte`.
Le répertoire `test` contient les sources de la classe de test JUnit `CompteTest`.

## Build avec `maven` (présentiel)
Dans cet exercice, vous allez transformer un projet Java en un projet `maven`.

Il pourra être nécessaire de [configurer](http://maven.apache.org/guides/mini/guide-proxies.html) le proxy (http://wwwcache.uvsq.fr:3128 par exemple à l'UVSQ) pour accéder au dépôt central de Maven.

1. Copier les fichiers `Compte.java` et `CompteTest.java` du TD précédent à la place des sources actuelles ;
1. Créez un nouveau projet Maven avec le plugin `archetype` en sélectionnant l’archétype `maven-archetype-quickstart` (groupe `fr.uvsq.tod`, artéfact `compte`, package `fr.uvsq.tod.compte`) ;
    1. dans quel répertoire le projet Maven a-t'il été créé ?
        > Dans le répertoire 'compte'.
    1. dans quels répertoires se trouvent les sources et les sources des test ?
        > Dans le répertoire 'src' et ensuite 'main' pour les sources puis 'test' pour les sources des test.
    1. dans quel fichier se trouve la description du projet ?
        > Dans le fichier 'predefininedExternalAnnotation'
    1. exécuter Maven dans le répertoire créé
        ```bash
        # RÉPONDRE ICI
        ```
1. Corriger la structure pour Maven
    1. déplacer le fichier de description Maven à la racine du projet Java
    1. déplacer les répertoires des sources et des tests Maven dans `/src`
    1. déplacer les classes `Compte` et `CompteTest` à l'emplacement adéquat
    1. supprimer le sous-répertoire créé par Maven ainsi que les sous-répertoires du projet Java devenus inutile
    1. exécuter Maven dans le répertoire du projet Java
    1. si l'exécution se déroule normalement, valider les changements avec `git`
1. Modifier le `.gitignore` pour un projet Maven (cf. [Maven.gitignore](https://github.com/github/gitignore/blob/master/Maven.gitignore) sur github)
1. Modifier la configuration du projet de la façon suivante :
    1. si nécessaire, ajouter une propriété précisant l'encodage des fichiers du projet (cf. [FAQ](https://maven.apache.org/general.html))
    1. modifier la version des sources Java et des `.class` pour utiliser la version *1.8* de Java
    1. utiliser la version *4.13.1* de JUnit
1. Modifier le POM pour intégrer les éléments suivants :
    1. génération de la documentation [Javadoc](http://maven.apache.org/plugins/maven-javadoc-plugin/)
    1. vérification des conventions de codage avec [checkstyle](http://maven.apache.org/plugins/maven-checkstyle-plugin/)
1.  Modifier le POM pour que le jar généré soit exécutable :
    1. ajouter un `main` à la classe `Compte` qui exécutera quelques méthodes de la classe et affichera les résultats
    1. en utilisant le plugin [assembly](http://maven.apache.org/plugins/maven-assembly-plugin/) (ou le plugin [shade](https://maven.apache.org/plugins/maven-shade-plugin/))
1. Ajouter une bibliothèque au projet :
    1. ajouter la bibliothèque [Log4j](http://logging.apache.org/log4j/2.x/index.html) comme dépendance du projet
    1. remplacer les affichages du `main` par des appels à l'API de *logging* (cf. [Log4j 2 API](http://logging.apache.org/log4j/2.x/manual/api.html))
    1. générer une archive du projet contenant ses dépendances (*uber-jar*)
1. Intégrer [Maven wrapper](https://github.com/takari/maven-wrapper) au projet
    1. quelle est l'utilité de ce plugin ?
        > RÉPONDRE ICI
    1. quelle commande doit-on utiliser dorénavant pour générer un `jar` du projet ?
        ```bash
        # RÉPONDRE ICI
        ```

## Découverte de JUnit 5 (distanciel)
L'objectif de cette section est de découvrir la nouvelle version de JUnit ([JUnit 5](https://junit.org/junit5/)).
Pour cela, vous allez écrire une fonction permettant de traduire un nombre en [chiffres romains](https://fr.wikipedia.org/wiki/Num%C3%A9ration_romaine) en un nombre en numération décimale.
De plus, vous respecterez le plus strictement possible une approche TDD.

> En particulier, ne cherchez pas un algorithme dès le départ mais essayez de le construire de manière incrémentale test après test.

> Vous validez les changements après chaque cycle

Le squelette de la classe et de la classe de test se trouvent dans [RomanNumeralsConverter](src/fr/uvsq/tod/kata/RomanNumeralsConverter.java) et [RomanNumeralsConverterTest](test/fr/uvsq/tod/kata/RomanNumeralsConverterTest.java).
Les tests utilisent JUnit 4 et vont évoluer vers JUnit 5 durant l'exercice.
L'article [Migrating from JUnit 4 to JUnit 5](https://blogs.oracle.com/javamagazine/migrating-from-junit-4-to-junit-5-important-differences-and-benefits) détaille les changements entre les deux frameworks.

1. Le premier test `shouldConvertTheDigitI`
    1. exécuter le test
    1. compléter **à minima** la méthode `convert` pour que le test passe
    1. en utilisant les capacités de *refactoring* de votre IDE, améliorer la lisibilité de la façon suivante
        * renommer le paramètre `i` en `aRomanNumer`
        * renommer la méthode `convert` en `toDecimal`
    1. réexécuter le test
1. Modifier le projet pour utiliser JUnit 5 dans `RomanNumeralsConverterTest`
    1. ajouter les bibliothèques JUnit 5 au projet
    1. modifier les `import`
    1. vérifier que le test fonctionne comme attendu
1. Ajouter des tests pour les autres chiffres romains (`I`, `V`, `X`, `L`, `C`, `D`, `M`) ainsi que pour une chaîne vide, la valeur `null` ou une chaîne malformée
    * pour chaque nouveau test, respecter le cycle TDD (écriture du test, vérification de l'échec, implémentation, vérification du succès, refactoring si nécessaire)
    * Les cas d'erreur seront signalés avec une exception `IllegalArgumentException` (cf. [Assert an Exception is Thrown in JUnit 4 and 5](https://www.baeldung.com/junit-assert-exception))
1. Réduire le nombre de tests précédents en utilisant des [tests paramétrés](https://junit.org/junit5/docs/current/user-guide/#writing-tests-parameterized-tests)
1. Si la méthode `toDecimal` utilise une structure de contrôle conditionnelle (`if`, `switch`), la remplacer par l'utilisation d'une [`Map`](https://docs.oracle.com/en/java/javase/11/docs/api/java.base/java/util/Map.html) puis exécuter les tests pour vérifier que la modification n'a pas changé le comportement de la méthode
1. Compléter l'implémentation en suivant le même processus
1. Après avoir fait la partie présentielle, intégrer les sources de cet exercice au *build* Maven 
