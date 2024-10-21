#include "./sqlite/include/Order.hpp"
#include <iostream>
using namespace std;

// Constructor
Order::Order(string code, string customerCode)
    : code(code), customerCode(customerCode) {}

// Agregar artículo al pedido
void Order::attachArticle(Article article) {
    articles.push_back(article);
}

// Guardar el pedido en la base de datos
void Order::saveToDB(sqlite3* db) {
    // Inserta el pedido en la tabla `Order`
    string sql = "INSERT INTO `Order` (code, customer_code) VALUES ('" + code + "', '" + customerCode + "');";
    char* errorMsg;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al insertar pedido: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    } else {
        cout << "Pedido insertado correctamente." << endl;
    }

    // Inserta cada artículo en la tabla intermedia Order_Article
    for (const auto& article : articles) {
        sql = "INSERT INTO Order_Article (order_code, article_code) VALUES ('" + code + "', '" + article.getCode() + "');";
        rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);

        if (rc != SQLITE_OK) {
            cerr << "Error al insertar artículo en Order_Article: " << errorMsg << endl;
            sqlite3_free(errorMsg);
        } else {
            cout << "Artículo '" << article.getCode() << "' insertado en Order_Article." << endl;
        }
    }
}
