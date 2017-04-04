#pragma once
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"

class Kitchen
{
public:
    Kitchen();
    ~Kitchen();

    static void addIngredient(Ingredient& i);
    static void addRecipe(Recipe& r);

    // Getters
    static std::vector<Ingredient> m_ingredients();
    static std::vector<Recipe> m_recipes();

    void initKitchen();
private:
    static std::vector<Ingredient> mIngredients;
    static std::vector<Recipe> mRecipes;
    static void initRecipes();
    static void initIngredients();
};

