import argparse
from pathlib import Path

import customtkinter as ctk

from _bibliotheque import BookSortOrder, list_available_books


class BooksWindow(ctk.CTk):
    SORT_ORDERS = {
        "Ordre du catalogue": BookSortOrder.CATALOG,
        "Titre": BookSortOrder.TITLE,
        "Auteur": BookSortOrder.AUTHOR,
    }

    def __init__(self, data_dir):
        super().__init__()
        self.data_dir = data_dir
        self.title("Bibliothèque — Livres disponibles")
        self.geometry("780x520")

        controls = ctk.CTkFrame(self)
        controls.pack(fill="x", padx=16, pady=16)
        self.sort_menu = ctk.CTkOptionMenu(
            controls, values=list(self.SORT_ORDERS), command=self.refresh
        )
        self.sort_menu.pack(side="left", padx=8, pady=8)
        ctk.CTkButton(controls, text="Actualiser", command=self.refresh).pack(
            side="right", padx=8, pady=8
        )

        self.status = ctk.CTkLabel(self, text="", wraplength=700)
        self.status.pack(padx=16)
        self.books = ctk.CTkScrollableFrame(self, label_text="Titre — Auteur — ISBN")
        self.books.pack(fill="both", expand=True, padx=16, pady=16)
        self.refresh()

    def refresh(self, _selection=None):
        for row in self.books.winfo_children():
            row.destroy()

        order = self.SORT_ORDERS[self.sort_menu.get()]
        try:
            books = list_available_books(self.data_dir, order)
        except (RuntimeError, UnicodeError) as error:
            self.status.configure(text=f"Erreur de chargement : {error}")
            return

        if not books:
            self.status.configure(text="Aucun livre disponible pour emprunt.")
            return

        self.status.configure(text=f"{len(books)} livre(s) disponible(s)")
        for book in books:
            text = f"{book['title']} — {book['author']} — {book['isbn']}"
            ctk.CTkLabel(self.books, text=text, anchor="w", justify="left", wraplength=650).pack(
                fill="x", padx=8, pady=4
            )


def main():
    parser = argparse.ArgumentParser(description="Afficher les livres disponibles.")
    parser.add_argument("--data-dir", "-d", type=Path, required=True)
    args = parser.parse_args()
    BooksWindow(args.data_dir).mainloop()


if __name__ == "__main__":
    main()
