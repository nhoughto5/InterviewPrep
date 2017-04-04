#pragma once
#include "Ingredient.h"
#include <vector>

class Recipe
{
public:
    Recipe();
    ~Recipe();

    void addIngredient(Ingredient i);
    float getDiscount();
    float getSalesTax();
    float getTotalCost();

    std::string printTotalCost();
    std::string printWellnessDiscount();
    std::string printSalesTax();
private:
    std::vector<Ingredient> mIngredients;
};

