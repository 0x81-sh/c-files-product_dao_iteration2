#include "product.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct SProduct {
    int id;
    char name[30];
    double price;
};

Product Product_create(int id, char *name, double price) {
    Product created = (Product) calloc(sizeof(struct SProduct), 1);

    created->id = id;
    created->price = price;
    strcpy(created->name, name);

    return created;
}

void Product_print(Product _this) {
    printf("[%d] %s : %lf", _this->id, _this->name, _this->price);
}

void Product_delete(Product _this) {
    free(_this);
}

int Product_getId(Product _this) {
    return _this->id;
}

double Product_getPrice(Product _this) {
    return _this->price;
}

void Product_setPrice(Product _this, double newPrice) {
    _this->price = newPrice;
}

char *Product_getName(Product _this) {
    return _this->name;
}

void Product_setName(Product _this, char *newName) {
    strcpy(_this->name, newName);
}

int getDataSize () {
    return sizeof (struct SProduct);
}

bool Product_compare(Product a, Product b) {
    bool isSame = true;

    if (a->id != b->id) isSame = false;
    if (strcmp(a->name, b->name) != 0) isSame = false;
    if (a->price != b->price) isSame = false;

    return isSame;
}