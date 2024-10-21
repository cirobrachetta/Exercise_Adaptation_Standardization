#pragma once
#include <iostream>
using namespace std;
#include <vector>
#include "sqlite3.h"
#include "Article.hpp"

class Order {
private:
    string code;               // Código del pedido
    string customerCode;       // Código del cliente
    vector<Article> articles;  // Artículos del pedido

public:
    // Constructor
    Order(string code, string customerCode);

    // Métodos
    void attachArticle(Article article);  // Agregar artículo al pedido
    void saveToDB(sqlite3* db);           // Guardar pedido en la base de datos
};