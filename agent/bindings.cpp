#include <filesystem>
#include <stdexcept>

#include <pybind11/pybind11.h>
#include <pybind11/stl/filesystem.h>

#include "filemanager.h"

namespace py = pybind11;
namespace fs = std::filesystem;

PYBIND11_MODULE(_bibliotheque, module) {
    py::enum_<BookSortOrder>(module, "BookSortOrder")
        .value("CATALOG", BookSortOrder::Catalog)
        .value("TITLE", BookSortOrder::Title)
        .value("AUTHOR", BookSortOrder::Author);

    module.def("list_available_books", [](const fs::path& dataDir, BookSortOrder order) {
        if (!fs::is_directory(dataDir)) {
            throw std::runtime_error("Répertoire de données introuvable : " + dataDir.string());
        }

        const auto booksFile = dataDir / "books.txt";
        Library library;
        FileManager files(booksFile.string(), "");
        if (!fs::is_regular_file(booksFile) || !files.loadBooksFromFile(library)) {
            throw std::runtime_error("Impossible de lire le catalogue : " + booksFile.string());
        }

        py::list rows;
        for (const Book* book : Library::sortBooksForDisplay(library.getAvailableBooks(), order)) {
            py::dict row;
            row["title"] = book->getTitle();
            row["author"] = book->getAuthor();
            row["isbn"] = book->getISBN();
            rows.append(row);
        }
        return rows;
    }, py::arg("data_dir"), py::arg("order") = BookSortOrder::Catalog);
}
