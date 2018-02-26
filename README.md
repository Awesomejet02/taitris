# tAItris
Projet du quatrième semestre de l'EPITA

## Table des matières
* [Présentation du groupe](#présentation-du-groupe-s4masterrace)
* [Présentation du projet](#présentation-du-projet-taitris)
* [Structure du projet](#structure-du-projet)
* [Dépendances](#dépendances)
* [Générer le projet](#générer-le-projet)
* [Utilisation](#utilisation)
* [Ressources et liens](#ressources-et-liens)

## Présentation du groupe: S4MasterRace
* **papini_j** Julien PAPINI <julien.papini@epita.fr>
* **loyau_n** Nicolas LOYAU <nicolas.loyau@epita.fr>
* **murrig_s** Sevan MURRIGUIAN-WATRIN <sevan.murriguian-watrin@epita.fr>
* **michel_k** Thomas MICHELOT <thomas.michelot@epita.fr>

## Présentation du projet: tAItris
Nous sommes S4MasterRace et nous sommes en ce début de S4 à l'EPITA sur le point de commencer un projet en groupe de quatre personnes (et seulement quatre), d'une durée approximative de cinq mois.

Ce projet, qui en ce qui nous concerne se nomme tAItris, dois comporter une part algorithmique importante et obligatoirement être réalisé a l'aide du langage C.

Nous avons donc choisi de partir sur la base du jeu bien connu, Tetris, et d'y ajouter une touche d'intelligence artificielle. Nous avons en tête quelques modes de jeux différents, le premier qui nous permet de jouer a Tetris, bien entendu, un second mode qui nous permet d'entrainer nos intelligences artificielles. Enfin un dernier mode ou l'intelligence artificielle va jouer a notre place et je l'espère obtenir de meilleur score que nous.

Nous avons recherches quelques méthodes qui nous permettraient de résoudre ce problème qui est d'apprendre a une machine a jouer et gagner a Tetris.
Les méthodes retenues sont, premièrement l'algorithme génétique qui se base sur le monde biologique pour obtenir une solution viable au problème posé par essaies successifs, mutations et sélection naturelle.
La seconde méthode qui nous a attirée utilise un réseau de neurones profonds qui par l'utilisation de couches de neurones successives doit arriver a jouer aussi bien si ce n'est mieux qu'un homme.

## Structure du projet
* **bin/** - Exécutables
* **build/** - Build
* **data/** - Données (IA, deep learning, etc...)
* **doc/** - Documentation
	* **html/** - Documentation du code au format html
	* **latex/** - Documentation du code au format latex
	* **pdf/** - PDF (Documentation du code, cahier des charges, rapports de soutenances...)
* **res/** - Ressources (Images, sons, etc...)
* **src/** - Code source

## Dépendances

## Générer le projet
#### Afficher l'aide du Makefile
`make help`

#### Compiler le projet
`make`

#### Déplacer le dossier ressource et de données dans bin
`make resources`

#### Générer la documentation avec doxygen
`make doc`

#### Nettoyer la compilation
`make clean`

## Utilisation
#### Lancer l'exécutable
`make run`

ou

`./bin/tAItris`

#### Sauvegarder les fichiers de données
`make save`

## Ressources et liens
* [Post: Coding a Tetris AI using a Genetic Algorithm](https://luckytoilet.wordpress.com/2011/05/27/coding-a-tetris-ai-using-a-genetic-algorithm/)
* [Vidéo: How to Make an Evolutionary Tetris AI](https://www.youtube.com/watch?v=xLHCMMGuN0Q)
* [Github: How_to_make_an_evolutionary_tetris_bot](https://github.com/llSourcell/How_to_make_an_evolutionary_tetris_bot)
* [Post: TETRIS stacking tutorial](https://www.ryanheise.com/tetris/tetris_stacking.html)
* [Exemple: Tetris AI](https://leeyiyuan.github.io/tetrisai/)
* [Github: Sources Tetris AI](https://github.com/LeeYiyuan/tetrisai)