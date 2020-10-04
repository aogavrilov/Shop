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
    size_t GetSumPrice(size_t count){
        if(count > this->count)
            throw("You would like buy more product then in shop!");
        else
            return count * this->price;
    }
    size_t GetCount(){
        return this->count;
    }
    string GetName(){
        return this->name;
    }
};



class Shop{
    string code;
    string name;
    unordered_map<string, Product> products;
public:
    Shop(string code, string name):code(code), name(name){}
    void AddProducts(Product prod, size_t count, size_t price){
        products.insert(std::unordered_map< string, Product >::value_type (prod.GetCode(), prod));
        //cout << products.find(prod.GetCode())->first;
        products.find(prod.GetCode())->second.Load(count, price);
    }
    size_t isInstance(string code){
        if(products.count(code) == 0)
            return 0;
        return 1;
    }
    size_t GetPrice(string code){
        //isInstance?
        if(products.count(code) == 0)
            throw("Object isn't Instance!");
        return products.find(code)->second.GetPrice();
    }
    string GetName(){
        return this->name;
    }
    void Buy(size_t count){
        size_t sum = 0;
        for(auto iter = products.begin(); iter != products.end(); iter++){
            if(sum < count){
                if(iter->second.GetCount() > 0){
                    size_t x = (count - sum) / iter->second.GetPrice();
                    if(x > iter->second.GetCount())
                        x = iter->second.GetCount();
                    sum += x * iter->second.GetPrice();
                    cout << iter->second.GetName() <<": " << x << endl;
                }
            } else break;
        }
    }

    int Buy(vector<string> prods, vector<size_t> counts){
        if(prods.size() != counts.size())
            throw("Some exception!");
        for(size_t i = 0; i < prods.size(); i++){
            size_t count = products.find(prods[i])->second.GetCount();
            if(count < counts[i]){
                return -1;
            }
        }
        size_t sum = 0;
        for(size_t i = 0; i < prods.size(); i++){
            size_t count = products.find(prods[i])->second.GetCount();
            sum += products.find(prods[i])->second.GetSumPrice(count);
            products.find(prods[i])->second.Get(count);
        }
        return sum;
    }

    int GetPriceOnVector(vector<string> prods, vector<size_t> counts){
        if(prods.size() != counts.size())
            throw("Some exception!");
        for(size_t i = 0; i < prods.size(); i++){
            size_t count = products.find(prods[i])->second.GetCount();
            if(count < counts[i]){
                return -1;
            }
        }
        size_t sum = 0;
        for(size_t i = 0; i < prods.size(); i++){
            size_t count = products.find(prods[i])->second.GetCount();
            sum += products.find(prods[i])->second.GetSumPrice(count);
        }
        return sum;
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
    string FindShopWithCheepestProduct(string const code){
        vector<Shop>::iterator iter = visible_shops.begin();
        size_t minPrice = iter->GetPrice(code);
        string ShopName = iter->GetName();
        for(; iter != visible_shops.end(); iter++){
            if(iter->isInstance(code) == 0)
                continue;
            if (iter->GetPrice(code) < minPrice) {
                minPrice = iter->GetPrice(code);
                ShopName = iter->GetName();
            }
        }
        cout << minPrice << endl;
        return ShopName;
    }
    string FindCheepestShowVector(vector<string> prods, vector<size_t> counts){
        size_t sum = 0;
        string name;
        for(auto iter = visible_shops.begin(); iter != visible_shops.end(); iter++){
            int shop_sum = iter->GetPriceOnVector(prods, counts);
            if(shop_sum == -1)
                continue;
            if(sum == 0){
                sum = shop_sum;
                name = iter->GetName();
            }
            if(sum > shop_sum){
                sum = shop_sum;
                name = iter->GetName();
            }

        }
        return name;
    }
};

int main() {
    Shop first = Shop("123", "Ikea");
    Shop second = Shop("1233", "Ikea2");
    Shop third = Shop("1233", "Ikea3");
    Product notebooks = Product("54637284", "Notebook");
    Product paper = Product("54637281", "Paper");
    first.AddProducts(notebooks, 100, 20);
    first.AddProducts(paper, 5, 30);
    second.AddProducts(paper, 100, 50);

    second.AddProducts(notebooks, 100, 10);
    second.AddProducts(paper, 5, 300);

    third.AddProducts(notebooks, 100, 10);
    third.AddProducts(paper, 5, 3);

    first.Buy(290);

    Person person = Person(100);
    person.AddShop(first);
    person.AddShop(second);
    person.AddShop(third);

   // cout << person.FindShopWithCheepestProduct("54637281");
   // cout << first.Buy({"54637284", "54637281"}, {10, 2});
    cout << person.FindCheepestShowVector({"54637284", "54637281"}, {10, 2});
    return 0;
}
