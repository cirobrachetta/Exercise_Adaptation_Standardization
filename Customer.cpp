#include <iostream>
using namespace std;
#include "./sqlite/include/Customer.hpp"


// Constructor
Customer::Customer(string code, string name, string address)
    : code(code), name(name), address(address) {}

// Método para guardar el cliente en la base de datos
void Customer::saveToDB(sqlite3* db) {
    string sql = "INSERT INTO Customer (code, name, address) VALUES ('" + code + "', '" + name + "', '" + address + "');";
    char* errorMsg;
    int rc = sqlite3_exec(db, sql.c_str(), 0, 0, &errorMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error al insertar cliente: " << errorMsg << endl;
        sqlite3_free(errorMsg);
    } else {
        cout << "Cliente insertado correctamente." << endl;
    }
}

// Getters
string Customer::getCode() const { return code; }
string Customer::getName() const { return name; }
string Customer::getAddress() const { return address; }
