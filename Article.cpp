#include <iostream>
using namespace std;
#include "./sqlite/include/Article.hpp"

// Constructor
Article::Article(string code, string name, double price)
    : code(code), name(name), price(price) {}

// Método para guardar el artículo en la base de datos
void Article::saveToDB(sqlite3* db) {
    string sql = "INSERT INTO Article (code, name, price) VALUES ('" + code + "', '" + name + "', " + to_string(price) + ");";
    char* errorMsg;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al insertar artículo: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    } else {
        cout << "Artículo insertado correctamente." << endl;
    }
}

// Getters
string Article::getCode() const { return code; }
string Article::getName() const { return name; }
double Article::getPrice() const { return price; }
