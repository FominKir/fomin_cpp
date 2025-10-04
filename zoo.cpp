#include <iostream>
#include <map>
#include <vector>

class Animal{
    
    public:

    virtual ~Animal() = default;
    
    virtual void feed(FoodStorage storage) = 0;
};

class FoodStorage{

    public:

    std::map <std::string, int> storage;

    int getFood(std::string foodName, int foodAmount){
        if(foodAmount <= storage[foodName]){
            storage[foodName] -= foodAmount;
            return 0;
        }
        else{
            std::cout << "Not enough " << foodName << std::endl;
            return -1;
        }
    }

};

class Zoo{

    std::vector<Animal*> animals;
    FoodStorage storage;

    public:
    void feed(){
        for(auto& a: animals){
            a->feed(storage);
        }
    }

};

class Cat: public Animal{

    std::map <std::string, int> feedType;

    void feed(FoodStorage storage){
        bool isFed = false;
        for(const auto& [foodName, foodAmount] : feedType){
            if(storage.getFood(foodName, foodAmount)==0){
                isFed = 1;
                break;}
        }
        if(isFed){
            std::cout << "Animal is fed" << std::endl;
        }
        else {
            std::cout << "Animal is not fed" << std::endl;
        }
    }


};
