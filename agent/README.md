# Construire le projet
Vous pouvez utiliser un dev container de base C++ de VScode.
Le projet utilise cmake, pensez à l'inclure dans votre dev container.

Voici les lignes de commandes pour compiler le projet:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

# Répertoire data

Il contient 2 fichiers `books.txt`et `users.txt` que vous pouvez utilisez pour tester votre code.
Pour ca il suffit de donner chemin vers le repertoire data avec l'application `bibliotheque -d <chemin verrs data>`

## Journal d’activités

Le CLI crée `activity.log` au démarrage dans le répertoire donné par `-d`,
ou dans le répertoire courant sans `-d`. Les ajouts et suppressions de livres,
les emprunts et les retours réussis sont ajoutés au fichier avec l’heure locale.
Un retour consigne le livre tel qu’il était avant le retour pour conserver le
nom de l’emprunteur. Les entrées restent disponibles après chaque session.
