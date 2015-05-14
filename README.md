## LA NORME DU BOMBERMAN, #PAGE_A



### Ce qu'il faut faire / ne pas faire

- TOUTES les valeurs sont passées par pointeur ou par référence, sauf les types de base (`int`, `char`, ...) et sont en `const`.
  Si besoin d'une valeur non-const, on enlève le `const`, mais par défaut on le met.

- TOUS les attributs sont en `private` ou en `protected`, AUCUNE exception.

- TOUTES les méthodes sont en `private` ou en `protected` par défaut. Les deux seules exceptions c'est pour les getters et
  les fonctions qui démarrent l'object (genre `runLevel`).

- AUCUN `char*`, `int*`, etc... Les seuls `new` qu'on fait c'est sur des classes.

- AUCUN `define`, peu importe la raison. On utilise un `enum` à la place.


### Comment on code ? (syntaxe)

- Le symbole pointeur `*` est sur le type, pas sur le nom de la variable : `MaClasse* monobjet` à la place de `MaClasse *monobjet`

- Dans le header d'une classe, on a en premier la définition des types spécifiques à la classe (enum et co.),
  puis la définition des méthodes publiques (saut de ligne entre contructeur / destructeur et les autres méthodes),
  puis la définition des méthodes protected,
  puis la définition des méthodes private,
  puis la définition des attributs protected,
  puis la définition des attributs private.
  Avec un saut de ligne entre chaque nouvelle "section".

```
#ifndef ITEM_HH
#define	ITEM_HH

#include "Observer.hpp"
#include "Position.hpp"
#include "Clock.hpp"

class Item
{
public:
	Item(Position const &);
	virtual ~Item() = 0;

	Position	position() const;
	Position	prevPosition() const;
	void		toConfig(Config &) const;

private:
	virtual void tick(Subject*) = 0;

protected:
	Position    _position;
	Position    _prevPosition;

	bool        _clockInit;
	seconds_t   _spawnTime;
};

#endif	/* ITEM_HH */
```

- Dans le header d'une classe, le nom de tous les attributs est aligné.

- Pour les méthodes dans le .cpp, on met le type de retour, un saut de ligne, et le prototype de la fonction.

- Pour les constructeurs, on va à la ligne avant la liste d'initialisation.

- Les fichiers headers sont nommés .hpp s'ils sont templatés, .hh autrement.


### Divers

- Quand un truc ne compile pas ou fait planter le programme au démarrage, tu ne le push pas sur git.

- Pour gérer les évènements, on demandes à Antoine comment ça se passe (si tu sais pas déjà), et tu ne fais pas de truc à ta sauce.

- LE PLUS IMPORTANT : Quand vous bloquez, demandez de l'aide ! Le but est de ne pas perdre de temps en restant bloqué sur une petite erreur qu'un autre verrait tout de suite

