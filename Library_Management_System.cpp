#include <bits/stdc++.h>

using namespace std;

// Structure of a book
struct Book
{
    int id;
    string title;
    string author;
    bool isAvailable;
};

// Vector of books in the library
vector<Book> library;

// Map for recording the details of the issuer
unordered_map<int, string> issuer_map;

// Function to add a new book to the library
void addBook()
{
    Book newBook;
    cout << endl
         << "Enter book ID: ";
    while (!(cin >> newBook.id))
    {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear();
        cin.ignore();
    }
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    newBook.isAvailable = true;
    library.push_back(newBook);

    // Sorting books by book ID after adding
    sort(library.begin(), library.end(), [](const Book &a, const Book &b)
         { return a.id < b.id; });
    cout << "Book added successfully!" << endl;
}

// Function to set issuer name by using ID
void setIssuerName(int id, string &name)
{
    issuer_map[id] = name;
}

// Function to get the name of the issuer by using ID
string getIssuerName(int id)
{
    auto it = issuer_map.find(id);
    if (it != issuer_map.end())
    {
        return it->second;
    }
    return "";
}

// Function to search for a book
void searchBook()
{
    int id;
    cout << "Enter book ID: ";
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear();
        cin.ignore();
    }

    // Binary search for book by ID
    int low = 0, high = library.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (library[mid].id == id)
        {
            cout << "ID: " << library[mid].id << endl;
            cout << "Title: " << library[mid].title << endl;
            cout << "Author: " << library[mid].author << endl;
            cout << "Availability: " << (library[mid].isAvailable ? "Available" : "Issued") << endl;
            if (!library[mid].isAvailable)
            {
                string name = getIssuerName(id);
                cout << "Issued to: " << name << endl;
            }
            return;
        }
        else if (library[mid].id < id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    cout << "Book not found!" << endl;
}

// Function to issue a book
void issueBook()
{
    int id;
    cout << endl
         << "Enter book ID: ";
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear();
        cin.ignore();
    }
    for (Book &book : library)
    {
        if (book.id == id && book.isAvailable)
        {
            cout << "Enter student name: ";
            cin.ignore();
            string studentName;
            getline(cin, studentName);
            book.isAvailable = false;
            setIssuerName(id, studentName);
            cout << "Book issued successfully!" << endl;
            return;
        }
    }
    cout << "Book not found or already issued!" << endl;
}

// Function to return a book
void returnBook()
{
    int id;
    cout << endl
         << "Enter book ID: ";
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear();
        cin.ignore();
    }
    for (Book &book : library)
    {
        if (book.id == id && !book.isAvailable)
        {
            book.isAvailable = true;
            issuer_map.erase(id); // Remove the issuer information
            cout << "Book returned successfully!" << endl;
            return;
        }
    }
    cout << "Book not found or not issued!" << endl;
}

// Function to merge two halves for merge sort
void merge(vector<Book> &arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Book> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i].id <= R[j].id)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Book> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Function to list all books
void listBooks()
{
    // No need to sort here if books are already sorted
    cout << endl
         << "List of all books:" << endl;
    for (const Book &book : library)
    {
        cout << "ID: " << book.id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Availability: " << (book.isAvailable ? "Available" : "Issued") << endl;
        if (!book.isAvailable)
        {
            string name = getIssuerName(book.id);
            cout << "Issued to: " << name << endl;
        }
        cout << endl;
    }
}

// Function to delete a book
void deleteBook()
{
    int id;
    cout << endl
         << "Enter book ID: ";
    while (!(cin >> id))
    {
        cout << "Invalid input. Please enter a valid ID." << endl;
        cin.clear();
        cin.ignore();
    }
    for (auto it = library.begin(); it != library.end(); ++it)
    {
        if (it->id == id)
        {
            library.erase(it);
            cout << "Book deleted successfully!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

// Main function
int main()
{
    int choice;
    while (true)
    {
        cout << "Library Management System" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Search for a book" << endl;
        cout << "3. Issue a book" << endl;
        cout << "4. Return a book" << endl;
        cout << "5. List all books" << endl;
        cout << "6. Delete a book" << endl;
        cout << "7. Exit" << endl
             << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            issueBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            listBooks();
            break;
        case 6:
            deleteBook();
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
        cout << endl;
    }
    return 0;
}
