#pragma once
#include <string>
#include "sqlite3.h"
#include <iostream>
using namespace std;

class Customer {
private:
    string code;
    string name;
    string address;

public:
    // Constructor
    Customer(string code, string name, string address);

    // Métodos
    void saveToDB(sqlite3* db);  // Inserta un cliente en la base de datos

    // Getters
    string getCode() const;
    string getName() const;
    string getAddress() const;
};
