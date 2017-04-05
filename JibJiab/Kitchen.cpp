#include "Kitchen.h"


Kitchen::Kitchen()
{
}


Kitchen::~Kitchen()
{
}

void Kitchen::addIngredient(Ingredient& i) {
    mIngredients.push_back(i);
}

void Kitchen::addRecipe(Recipe& r) {
    mRecipes.push_back(r);
}

std::vector<Ingredient> Kitchen::m_ingredients() const {
    return mIngredients;
}

std::vector<Recipe> Kitchen::m_recipes() const {
    return mRecipes;
}

Ingredient Kitchen::getIngredientByNumber(int i) {
    return mIngredients[i];
}

void Kitchen::initRecipes() {
    Recipe r1("R1");
    r1.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r1.addIngredient(Ingredient(Produce, 1, false, "Lemon", "", Money(2.03f)));
    r1.addIngredient(Ingredient(Pantry, 0.75f, true, "Olive Oil", "cup", Money(1.92f)));
    r1.addIngredient(Ingredient(Pantry, 0.75f, false, "Salt", "teaspoon", Money(0.16f)));
    r1.addIngredient(Ingredient(Pantry, 0.5f, false, "pepper", "teaspoon", Money(0.17f)));
    mRecipes.push_back(r1);

    Recipe r2("R2");
    r2.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r2.addIngredient(Ingredient(Meat, 4, false, "Chicken Breast", "", Money(2.19f)));
    r2.addIngredient(Ingredient(Pantry, 0.5f, true, "Olive Oil", "cup", Money(1.92f)));
    r2.addIngredient(Ingredient(Pantry, 0.5f, false, "Vinegar", "cup", Money(1.26f)));
    mRecipes.push_back(r2);

    Recipe r3("R3");
    r3.addIngredient(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    r3.addIngredient(Ingredient(Produce, 4, false, "Corn", "cup", Money(0.87f)));
    r3.addIngredient(Ingredient(Meat, 4, false, "Bacon", "slices", Money(0.24f)));
    r3.addIngredient(Ingredient(Pantry, 8, false, "Pasta", "ounce", Money(0.31f)));
    r3.addIngredient(Ingredient(Pantry, 0.3333f, true, "Olive Oil", "cup", Money(1.92f)));
    r3.addIngredient(Ingredient(Pantry, 1.25, false, "Salt", "teaspoon", Money(0.16f)));
    r3.addIngredient(Ingredient(Pantry, 0.75, false, "pepper", "teaspoon", Money(0.17f)));
    mRecipes.push_back(r3);
}

void Kitchen::initIngredients() {
    //Produce
    mIngredients.push_back(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    mIngredients.push_back(Ingredient(Produce, 1, false, "Lemon", "", Money(2.03f)));
    mIngredients.push_back(Ingredient(Produce, 1, false, "Corn", "cup", Money(0.87f)));

    // Meat/Poultry
    mIngredients.push_back(Ingredient(Meat, 1, false, "Chicken Breast", "", Money(2.19f)));
    mIngredients.push_back(Ingredient(Meat, 1, false, "Bacon", "slice", Money(0.24f)));

    // Pantry
    mIngredients.push_back(Ingredient(Pantry, 1, false, "Pasta", "ounce", Money(0.31f)));
    mIngredients.push_back(Ingredient(Pantry, 1, true, "Olive Oil", "cup", Money(1.92f)));
    mIngredients.push_back(Ingredient(Pantry, 1, false, "Vinegar", "cup", Money(1.26f)));
    mIngredients.push_back(Ingredient(Pantry, 1, false, "Salt", "teaspoon", Money(0.16f)));
    mIngredients.push_back(Ingredient(Pantry, 1, false, "pepper", "teaspoon", Money(0.17f)));
}

void Kitchen::initKitchen() {
    initIngredients();
    initRecipes();
}
