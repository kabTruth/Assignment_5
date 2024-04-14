#include <iostream>
#include "main.h"
#include<cmath>

int main() {
  StoreSystem store;

    
    Product p1("101", "bananas", 8000);
    Product p2("102", "watermelon", 10000);
    Product p3("103", "orange", 5000);

    store.addProductToInventory(p1);
    store.addProductToInventory(p2);
    store.addProductToInventory(p3);


    store.listProductsInInventory();

    
    Customer c1("C001", "Truth");
    Customer c2("C002", "Patricia");

    store.addCustomer(c1);
    store.addCustomer(c2);

    
    Order order1;
    order1.addProduct(p1);
    order1.addProduct(p2);
    store.placeOrderForCustomer(c1.getCustomerID(), "O001", order1);

    Order order2;
    order2.addProduct(p2);
    order2.addProduct(p3);
    store.placeOrderForCustomer(c2.getCustomerID(), "O002", order2);

    Order order3;
    order3.addProduct(p1);
    order3.addProduct(p3);
    store.placeOrderForCustomer(c1.getCustomerID(), "O003", order3);

    
    std::list<std::string> productsByCustomer = store.getProductsOrderedByCustomer("C001");
    std::cout << "Products ordered by customer C001:\n";
    for (const auto& productID : productsByCustomer) {
        std::cout << productID << "\n";
    }

    float totalExpenditure = store.getTotalExpenditureOfCustomer("C002");
    std::cout << "Total expenditure of customer C002: $" << totalExpenditure << "\n";

    std::list<std::string> customersForProduct = store.getCustomersWhoPurchasedProduct("102");
    std::cout << "Customers who purchased product 102:\n";
    for (const auto& customerID : customersForProduct) {
        std::cout << customerID << "\n";
    }
  return 0;
}
