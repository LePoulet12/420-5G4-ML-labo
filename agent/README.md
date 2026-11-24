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

## Interface graphique : livres disponibles

La fenêtre CustomTkinter affiche le titre, l’auteur et l’ISBN des livres
disponibles. Le module pybind11 réutilise le chargement, le filtre et le tri C++.
Le bouton **Actualiser** relit `books.txt` après une sauvegarde dans le CLI.
La fenêtre est en lecture seule.

Dans le devcontainer, depuis la racine du dépôt (reconstruire le conteneur pour
installer les en-têtes Python, si nécessaire) :

```sh
python3 -m venv /tmp/bibliotheque-venv
py=/tmp/bibliotheque-venv/bin/python
"$py" -m pip install -r agent/requirements-gui.txt
cmake -S agent -B agent/build-gui -DBIBLIOTHEQUE_BUILD_PYTHON=ON \
  -DPython_EXECUTABLE="$py"
cmake --build agent/build-gui
PYTHONPATH="$PWD/agent/build-gui" "$py" agent/gui.py --data-dir agent/data
```

La fenêtre nécessite un serveur d’affichage accessible depuis le conteneur.
Le CLI se compile toujours seul avec `cmake -S agent -B agent/build` puis
`cmake --build agent/build`, sans dépendance Python.
