Bomberman
===================

Ce dépôt contient les sources du Bomberman de mon groupe pour le module C++ de 2e année à Epitech.
Il a été réalisé à Strasbourg en 2015.

----------

Fonctionnalités
-------------

> - Jeu à 2 joueurs en écran partagé
> - Jeu contre intelligence artificielle
> - 3 niveaux de difficulté d'IA (jusqu'à un niveau imbattable)
> - Gestion du score
> - Sauvegarde et chargement des parties
> - Cartes générées aléatoirement et pré-concues
> - Objets bonus
> - Monstre volant bonus
> - Musique et sons
> - Menus dynamiques
> - Fichier de configuration en XML
> - Et plein d'autres trucs !

![Visuel du 42sh](http://antoine.buchser.fr/uploads/projects/thumbnails/bomberman.jpg)

Points intéressants à étudier !
-------------

> - L'architecture globale est faite pour découper entièrement la partie "moteur" de l'affichage graphique, avec une utilisation avancée du design pattern "Observer", il est presque possible de compiler le moteur sans la partie graphique.
> - L'implémentation du design pattern "Observer" est très intéressante car développée pour être extrêmement simple d'utilisation (héritage d'une classe et remplissage d'un tableau évènement <--> action).
> - La factory de menu est évoluée et permet de créer dynamiquement tous les menus que l'on veut et de gérer des workflows entre les différents menus simplement avec des fichiers XML sans toucher au code.
> - L'intelligence artificielle dans sa difficulté la plus simple est développée en LUA.
> - Les fichiers de configuration sont chargés par une classe permettant de stocker simplement les données et de conserver leur type (voir [ici](https://bitbucket.org/AntwaneB/awesome-c-configuration-class)).

Disclaimer
-------------

Si vous êtes étudiant à Epitech, servez vous des concepts utilisés, pas du code, ou la moulinette de triche vous trouvera et vous mettra un -42.