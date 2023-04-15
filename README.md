# projet_S4

Le make commit fait un push direct avec tous les nouveaux fichiers
    vous avez juste a faire make commit.

La fonction evalBoard evalue l'avancement de notre jeu d'echec.
il utilise les piece->value pour cette evaluation.
En gros plus le nombre de piece adverse ce fait manger plus le score est haut.
Et inversement pour nous, plus on a perdu de piece, plus on a un score faible.
Pour son fonctionnement, la fonction parcours tous le board et additionne ou soustrait les piece.value en fonction de leurs couleurs : on aime pas les pieces noirs :).

Puis pour la ft deepCopy, je vais pas vous faire un tableau mais elle copy juste le board pour pas que les 2 variable soit les même. ce référer au tp de l'année derniere sur le jeu des dames.