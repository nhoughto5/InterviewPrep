#include <iostream>
#include <vector>
#include <assert.h>
#include "Utilities.h"
#include "Ingredient.h"
#include "Money.h"
std::vector<Ingredient> getIngredientList() {
    std::vector<Ingredient> ret;

    //Produce
    ret.push_back(Ingredient(Produce, 1, true, "Garlic", "clove", Money(0.67f)));
    ret.push_back(Ingredient(Produce, 1, false, "Lemon", "", Money(2.03f)));
    ret.push_back(Ingredient(Produce, 1, false, "Corn", "cup", Money(0.87f)));

    // Meat/Poultry
    ret.push_back(Ingredient(Meat, 1, false, "Chicken Breast", "", Money(2.19f)));
    ret.push_back(Ingredient(Meat, 1, false, "Bacon", "slice", Money(0.24f)));

    // Pantry
    ret.push_back(Ingredient(Pantry, 1, false, "Pasta", "ounce", Money(0.31f)));
    ret.push_back(Ingredient(Pantry, 1, true, "Olive Oil", "cup", Money(1.92f)));
    ret.push_back(Ingredient(Pantry, 1, false, "Vinegar", "cup", Money(1.26f)));
    ret.push_back(Ingredient(Pantry, 1, false, "Salt", "teaspoon", Money(0.16f)));
    ret.push_back(Ingredient(Pantry, 1, false, "pepper", "teaspoon", Money(0.17f)));

    return ret;
}

void testMoneyClass() {
    Money m0(.7f);
    Money m1(0.67f);
    Money m2(1.56f);
    Money m3;

    // Test toString Method
    assert(m0.toString().compare ("$0.70") == 0);
    assert(m1.toString().compare ("$0.67") == 0);
    assert(m2.toString().compare("$1.56") == 0);

    m3 = m2;
    assert(m2.toString().compare("$1.56") == 0);
    assert(m3.toString().compare("$1.56") == 0);

    m3 += m2;
    assert(m3.toString().compare("$3.12") == 0);

    m3 -= m2;
    assert(m3.toString().compare("$1.56") == 0);

    m3 *= 2.f;
    assert(m3.toString().compare("$3.12") == 0);

    m3 /= 2.f;
    assert(m3.toString().compare("$1.56") == 0);

    std::cout << "All Money class test cases passed\n";
}

int main() {
    testMoneyClass();
    return 0;
}
