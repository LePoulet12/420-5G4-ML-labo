# Repository guide

## C++ library CLI (`agent/`)

- From the repo root: `cmake -S agent -B agent/build && cmake --build agent/build`. CMake 3.21+ builds the C++17 `bibliotheque` executable from `agent/main.cpp` and the other top-level `.cpp` files. The checked-in VS Code CMake setting points to a machine-specific absolute path; use the explicit `-S agent` command.
- There are no CTest targets. For a smoke test, copy `agent/data/` to a scratch directory, then run `./agent/build/bibliotheque -d <scratch-data-dir>` and enter `0` to exit. Even a normal exit rewrites `books.txt` and `users.txt`, so don't point `-d` at the tracked fixtures. The CLI does not need the devcontainer's X11 forwarding.

## ML notebooks

- Start each kernel in its notebook's directory: paths such as `data/`, `modele/`, and `images/` are relative to the working directory. There is no tracked Python dependency manifest; the ignored `apprentissage/.venv/` is local setup.
- In `apprentissage/`, `partie3_predictions.ipynb` loads the tracked `modele/modele_pokemon.mod` written by `partie3_entrainement.ipynb`. The training notebook reads `data/dataset.csv` as tab-separated despite its extension.
- In `analyse_image/`, `test_model.ipynb` runs inference using the tracked model JSON and `.weights.h5` plus sample images. It can run without retraining; `classification.ipynb` needs the Fashion-MNIST train and test CSVs under the ignored `analyse_image/data/` and can overwrite the tracked model files.
