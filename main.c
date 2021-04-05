#include <stdio.h>
#include <stdlib.h>
#include "product.h"
#include "product_dao.h"

void testAddRead(ProductDAO productDao);
void testReadWriteArray(ProductDAO productDao);

int main() {
    ProductDAO file = ProductDAO_create("test.dat");

    testAddRead(file);
    testReadWriteArray(file);

    printf("All tests ran.\n");
    ProductDAO_delete(file);
    return 0;
}

void testAddRead (ProductDAO productDao) {
    Product testData = Product_create(1, "testProduct", 420.69);
    ProductDAO_write(productDao, testData);

    Product testData2 = ProductDAO_read(productDao, 0);
    bool isSame = Product_compare(testData, testData2);

    if (isSame) printf("Single add/read failed.\n");
    Product_delete(testData);
    Product_delete(testData2);
}

void testReadWriteArray(ProductDAO productDao) {
    Product testArr[3] = {Product_create(1, "test", 2.0),
                          Product_create(2, "test2", 4.0),
                          Product_create(3, "test3", 6.0)};
    ProductDAO_writeAll(productDao, testArr, 3);

    int size = 0;
    bool isSame = true;
    Product *array = ProductDAO_readAll(productDao, &size);

    for (int i = 0; i < 3; i++) {
        if (!Product_compare(testArr[i], array[i])) isSame = false;

        Product_delete(array[i]);
        Product_delete(testArr[i]);
    }

    free(array);
    if (!isSame) printf("Array read/write failed.\n");
}
