#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;

class Product{
    string code;
    string name;
    size_t price = 0;
    size_t count = 0;
public:
    Product(string code, string name) : code(code), name(name){
    }
    void Load(size_t count, size_t price){
        this->price = price;
        this->count = count;
    }
    void Get(size_t count){
        if(count > this->count)
            throw("You would like buy more product then in shop!");
        else
            this->count -= count;
    }
    string GetCode(){
        return this->code;
    }
    size_t GetPrice(){
        return this->price;
    }

};

class Shop{
    string code;
    string name;
    unordered_map<string, Product> products;
public:
    Shop(string code, string name):code(code), name(name){}
    void AddProducts(Product prod, size_t count, size_t price){
        products.insert(make_pair(prod.GetCode(), prod)); //[prod.GetCode()] = prod;
        products[prod.GetCode()].Load(count, price);
    }
    size_t GetPrice(string code){
        //isInstance?
        if(products.count(code) == 0)
            throw("Object isn't Instance!");
        return products[code].GetPrice();
    }
    string GetName(){
        return this->name;
    }

};

class Person{
    size_t money;
    vector<Shop> visible_shops;
public:
    Person(size_t money): money(money){}
    void AddShop(Shop shop){
        visible_shops.push_back(shop);
    }
    string FindShopWithCheepestProduct(string code){
        vector<Shop>::iterator iter = visible_shops.begin();
        size_t minPrice = iter->GetPrice(code);
        string ShopName = iter->GetName();
        for(; iter != visible_shops.end(); iter++){
            if(iter->GetPrice(code) < minPrice){
                minPrice = iter->GetPrice(code);
                ShopName = iter->GetName();
            }
        }
        return ShopName; /// леха , тебе это не надо , беги чел
    }
};

int main() {
    Shop first = Shop("123", "Икея");
    Product notebooks = Product("54637284", "Блокнот");
    first.AddProducts(notebooks, 100, 30);
    Person person = Person(100);
    person.AddShop(first);
    cout << person.FindShopWithCheepestProduct("54637284");
    return 0;
}
