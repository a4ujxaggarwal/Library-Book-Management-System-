#include <iostream>
#include <string>
using namespace std;

struct Book {
    int id;
    string title, author, status;
    Book* next;
    Book(int i, string t, string a) {
        id = i; title = t; author = a; status = "Available"; next = NULL;
    }
};

struct Trans {
    int id; string action;
    Trans* next;
    Trans(int i, string a) { id = i; action = a; next = NULL; }
};

class Library {
    Book* head;
    Trans* top;
public:
    Library() { head = NULL; top = NULL; }

    void insertBook() {
        int id; string t, a;
        cout << "Enter Book ID: "; cin >> id; cin.ignore();
        cout << "Enter Title: "; getline(cin, t);
        cout << "Enter Author: "; getline(cin, a);
        Book* b = new Book(id, t, a);
        if (!head) head = b;
        else { Book* temp = head; while (temp->next) temp = temp->next; temp->next = b; }
        cout << "Book Added!\n";
    }

    Book* search(int id) {
        for (Book* t = head; t; t = t->next)
            if (t->id == id) return t;
        return NULL;
    }

    void issueBook() {
        int id; cout << "Enter Book ID to issue: "; cin >> id;
        Book* b = search(id);
        if (!b) cout << "Not found!\n";
        else if (b->status == "Issued") cout << "Already issued!\n";
        else { b->status = "Issued"; push(id, "ISSUE"); cout << "Book Issued!\n"; }
    }

    void returnBook() {
        int id; cout << "Enter Book ID to return: "; cin >> id;
        Book* b = search(id);
        if (!b) cout << "Not found!\n";
        else if (b->status == "Available") cout << "Not issued!\n";
        else { b->status = "Available"; push(id, "RETURN"); cout << "Book Returned!\n"; }
    }

    void push(int id, string act) {
        Trans* t = new Trans(id, act);
        t->next = top; top = t;
    }

    void undo() {
        if (!top) { cout << "Nothing to undo!\n"; return; }
        Trans* t = top; top = top->next;
        Book* b = search(t->id);
        if (b) {
            if (t->action == "ISSUE") b->status = "Available";
            else b->status = "Issued";
            cout << "Undo done for Book " << b->id << "!\n";
        }
        delete t;
    }

    void showBooks() {
        if (!head) { cout << "No books!\n"; return; }
        for (Book* t = head; t; t = t->next)
            cout << t->id << " | " << t->title << " | " << t->author << " | " << t->status << endl;
    }
};

int main() {
    Library L; int ch;
    do {
        cout << "\n1.Insert  2.Issue  3.Return  4.Undo  5.Show  6.Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: L.insertBook(); break;
            case 2: L.issueBook(); break;
            case 3: L.returnBook(); break;
            case 4: L.undo(); break;
            case 5: L.showBooks(); break;
            case 6: cout << "Bye!\n"; break;
            default: cout << "Invalid!\n";
        }
    } while (ch != 6);
}
