#pragma once
#include <iostream>
using namespace std;
#include "sqlite3.h"

class Article {
private:
    string code;
    string name;
    double price;

public:
    // Constructor
    Article(string code, string name, double price);

    // Métodos
    void saveToDB(sqlite3* db);  // Inserta un artículo en la base de datos

    // Getters
    string getCode() const;
    string getName() const;
    double getPrice() const;
};