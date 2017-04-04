#pragma once
#include "Ingredient.h"
#include <vector>

class Recipe
{
public:
    Recipe();

    explicit Recipe(const std::string& name);

    ~Recipe();

    void addIngredient(Ingredient i);
    float getDiscount();
    float getSalesTax();
    float getTotalCost();

    std::string printTotalCost();
    std::string printWellnessDiscount();
    std::string printSalesTax();

    void printRecipe() const;


    std::string m_name() const;

private:
    std::vector<Ingredient> mIngredients;
    std::string mName;
};

