#pragma once
#include <vector>
#include "Ingredient.h"
#include "Recipe.h"

class Kitchen
{
public:
    Kitchen();
    ~Kitchen();

    void addIngredient(Ingredient& i);
    void addRecipe(Recipe& r);

    // Getters
    std::vector<Ingredient> m_ingredients() const;
    std::vector<Recipe> m_recipes() const;
    Ingredient getIngredientByNumber(int i);
    void initKitchen();
private:
    std::vector<Ingredient> mIngredients;
    std::vector<Recipe> mRecipes;
    void initRecipes();
    void initIngredients();
};

