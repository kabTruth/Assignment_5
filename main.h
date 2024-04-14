#ifndef MAIN_H
#define MAIN_H
#include<string>
#include<map>
#include<list>
#include<set>
#include<cmath>
#include<iostream>
#include<bits/stdc++.h>


class Product {
private:
    std::string _productID;
    std::string _name;
    float _price;

public:
    Product(const std::string& productID, const std::string& name, float price)
        : _productID(productID), _name(name), _price(price) {}

    const std::string& getProductID() const { return _productID; }
    const std::string& getName() const { return _name; }
    float getPrice() const { return _price; }
};

class Order {
private:
    std::list<Product> _orderedProducts;

public:
    void addProduct(const Product& product) {
        _orderedProducts.push_back(product);
    }

    const std::list<Product>& getOrderedProducts() const {
        return _orderedProducts;
    }
};

class Customer {
private:
    std::string _customerID;
    std::string _customerName;
    std::map<std::string, Order> _orders;

public:
    Customer(const std::string& customerID, const std::string& customerName)
        : _customerID(customerID), _customerName(customerName) {}

    void placeOrder(const std::string& orderID, const Order& order) {
        _orders.insert_or_assign(orderID, order);
    }

    float getTotalExpenditure() const {
        float total = 0.0;
        for (const auto& pair : _orders) {
            for (const auto& product : pair.second.getOrderedProducts()) {
                total += product.getPrice();
            }
        }
        return total;
    }

    const std::map<std::string, Order>& getOrders() const { // Return const reference to std::map
        return _orders;
    }

    const std::string& getCustomerID() const {
        return _customerID;
    }
};

class StoreSystem {
private:
    std::map<std::string, Product> _inventory; // Use std::map instead of std::unordered_map
    std::map<std::string, Customer> _customers; // Use std::map instead of std::unordered_map

public:
    void addProductToInventory(const Product& product) {
        _inventory.insert_or_assign(product.getProductID(), product);
    }

    void addCustomer(const Customer& customer) {
        _customers.insert_or_assign(customer.getCustomerID(), customer);
    }

    void placeOrderForCustomer(const std::string& customerID, const std::string& orderID, const Order& order) {
        auto customerIter = _customers.find(customerID);
        if (customerIter != _customers.end()) {
            customerIter->second.placeOrder(orderID, order);
        } else {
            std::cout << "Customer not found!\n";
        }
    }

    std::list<std::string> getProductsOrderedByCustomer(const std::string& customerID) const {
        std::list<std::string> products;
        auto customerIter = _customers.find(customerID);
        if (customerIter != _customers.end()) {
            for (const auto& pair : customerIter->second.getOrders()) {
                for (const auto& product : pair.second.getOrderedProducts()) {
                    products.push_back(product.getProductID());
                }
            }
        } else {
            std::cout << "Customer not found!\n";
        }
        return products;
    }

    float getTotalExpenditureOfCustomer(const std::string& customerID) const {
        auto customerIter = _customers.find(customerID);
        if (customerIter != _customers.end()) {
            return customerIter->second.getTotalExpenditure();
        } else {
            std::cout << "Customer not found!\n";
            return 0.0;
        }
    }

    std::list<std::string> getCustomersWhoPurchasedProduct(const std::string& productID) const {
        std::list<std::string> customers;
        for (const auto& pair : _customers) {
            for (const auto& orderPair : pair.second.getOrders()) {
                for (const auto& product : orderPair.second.getOrderedProducts()) {
                    if (product.getProductID() == productID) {
                        customers.push_back(pair.first);
                        break;
                    }
                }
            }
        }
        return customers;
    }

    void listProductsInInventory() const {
        std::cout << "Products in inventory:\n";
        for (const auto& pair : _inventory) {
            const Product& product = pair.second;
            std::cout << "Product ID: " << product.getProductID() << ", Name: " << product.getName()
                      << ", Price: ugx" << product.getPrice() << "\n";
        }
    }
};

#endif // MAIN_H
