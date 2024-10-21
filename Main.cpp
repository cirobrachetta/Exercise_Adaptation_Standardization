#include <iostream>
using namespace std;
#include "./sqlite/include/Customer.hpp"
#include "./sqlite/include/Article.hpp"
#include "./sqlite/include/Order.hpp"

// Crear las tablas en la base de datos
void createTables(sqlite3* db) {
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS Article (
            code TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            price REAL NOT NULL
        );

        CREATE TABLE IF NOT EXISTS Customer (
            code TEXT PRIMARY KEY,
            name TEXT NOT NULL,
            address TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS `Order` (
            code TEXT PRIMARY KEY,
            customer_code TEXT NOT NULL,
            FOREIGN KEY(customer_code) REFERENCES Customer(code)
        );

        CREATE TABLE IF NOT EXISTS Order_Article (
            order_code TEXT NOT NULL,
            article_code TEXT NOT NULL,
            FOREIGN KEY(order_code) REFERENCES `Order`(code),
            FOREIGN KEY(article_code) REFERENCES Article(code),
            PRIMARY KEY (order_code, article_code)
        );
    )";

    char* errorMsg;
    int rc = sqlite3_exec(db, sql, 0, 0, &errorMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al crear tablas: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    } else {
        cout << "Tablas creadas correctamente." << endl;
    }
}

int main() {
    sqlite3* db;
    int rc = sqlite3_open("store.db", &db);

    if (rc) {
        cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << endl;
        return rc;
    }

    createTables(db);

    // Crear e insertar un cliente
    Customer customer("C001", "Juan Perez", "Calle 123");
    customer.saveToDB(db);

    // Crear e insertar un artículo
    Article article("A001", "Laptop", 1200.00);
    article.saveToDB(db);

    // Crear un pedido y asociarlo con el cliente y el artículo
    Order order("O001", "C001");
    order.attachArticle(article);
    order.saveToDB(db);

    sqlite3_close(db);
    return 0;
}

