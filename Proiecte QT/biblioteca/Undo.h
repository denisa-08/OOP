//
// Created by Denisa on 14.04.2022.
//
#pragma once
#include "Book.h"
#include "BookRepo.h"

class ActionUndo {
public:

    virtual void doUndo() = 0;
    //destructorul este virtual

    virtual ~ActionUndo() = default;
};

class UndoAdd : public ActionUndo {
    Book addedBook;
    BookRepo& repo;

public:
    UndoAdd(BookRepo& repo, const Book& b): repo { repo }, addedBook{ b } {}

    void doUndo() override {
        repo.delete_book(addedBook);
    }
};

class UndoDelete : public ActionUndo {
    Book deletedBook;
    BookRepo& repo;

public:
    UndoDelete(BookRepo& repo, const Book& b): repo { repo }, deletedBook{ b }{}

    void doUndo() override {
        repo.store(deletedBook);
    }
};

class UndoUpdate : public ActionUndo {
    Book updatedBook;
    Book new_book;
    BookRepo& repo;

public:
    UndoUpdate(BookRepo& repo, const Book& b, const Book& new_book): repo { repo }, updatedBook{ b }, new_book{ new_book } {}

    void doUndo() override {
        repo.update(new_book, updatedBook);
    }
};
