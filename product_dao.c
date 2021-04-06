#include "product_dao.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define STR_SZ 60

struct SProductDAO {
    char filename[STR_SZ];
};

ProductDAO ProductDAO_create(char* filename) {
    ProductDAO new = (ProductDAO) malloc(sizeof (struct SProductDAO));
    strncpy(new->filename, filename, STR_SZ);

    return new;
}

void ProductDAO_write(ProductDAO _this, Product p) {
    FILE *fp = fopen(_this->filename, "ab");
    if (!fp) {
        printf("Cannot create or open file.\n");
        return;
    }

    fwrite(p, getDataSize(), 1, fp);
    fclose(fp);
}

Product ProductDAO_read(ProductDAO _this, int position) {
    FILE *fp = fopen(_this->filename, "rb");
    if (!fp) {
        printf("Could not open file.\n");
        return NULL;
    }

    int read = fseek(fp, (long) getDataSize() * position, SEEK_SET);
    if (read != 0) {
        printf("Could not seek to position.\n");
        fclose(fp);
        return NULL;
    }

    Product readP = Product_create(0, "", 0);
    fread(readP, getDataSize(), 1, fp);
    fclose(fp);

    return readP;
}

void ProductDAO_writeAll(ProductDAO _this, Product* products, int count) {
    FILE *fp = fopen(_this->filename, "wb");
    if (!fp) {
        printf("Cannot create or open file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(*(products + i), getDataSize(), 1, fp);
    }

    fclose(fp);
}

Product* ProductDAO_readAll(ProductDAO _this, int *count) {
    FILE *fp = fopen(_this->filename, "rb");
    if (!fp) {
        printf("Could not open file.\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    int products = size / getDataSize();

    fseek(fp, 0, SEEK_SET);
    Product *array = (Product *) malloc(sizeof(Product) * products);

    for (int i = 0; i < products; i++) {
        array[i] = Product_create(0, "", 0);
        fread(array[i], getDataSize(), 1, fp);
    }

    *count = products;
    return array;
}

void ProductDAO_delete(ProductDAO _this) {
    free(_this);
}