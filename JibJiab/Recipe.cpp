#include "Recipe.h"
#include <sstream>
#include <iostream>


Recipe::Recipe() : mName{""}
{
}

Recipe::Recipe(const std::string& name): mName (name) {
}


Recipe::~Recipe()
{
}

void Recipe::addIngredient(Ingredient i) {
    mIngredients.push_back(i);
}

float Recipe::getTotalCost() {
    float total{ 0.0f };
    for (auto& i : mIngredients) {
        total += i.m_quantity() * i.m_price().m_value();
    }
    return roundUpUtil(total + getSalesTax() - getDiscount(), 0.01f);
}

float Recipe::getDiscount() {
    float total{ 0.0f };
    for (auto& i : mIngredients) {
        total += i.organic() ? i.getValue() * WELLNESS_DISCOUNT : 0.0f;
    }
    return roundUpUtil (total, 0.01f);
}

float Recipe::getSalesTax() {
    float total{ 0.0f };
    for(auto& i : mIngredients) {
        total += (i.m_type() == Produce) ? 0.0f : i.getValue() * SALES_TAX;
    }

    //Round to nearest seven cents
    return roundUpUtil (total, 0.07f);
}

std::string Recipe::printTotalCost() {
    return Money(getTotalCost()).toString();
}

std::string Recipe::printWellnessDiscount() {
    return Money(getDiscount()).toString();
}

std::string Recipe::printSalesTax() {
    return Money(getSalesTax()).toString();
}

void Recipe::printRecipe() const {
    if(mName.empty()) {
        printf("RECIPE Name: 'TOP-Seret\n");
    }
    else {
        printf("RECIPE %s\n", mName.c_str());
    }
    for(auto& i : mIngredients) {
        std::cout << i.toString() << "\n";
    }
    printf("==============================\n\n");
}

std::string Recipe::m_name() const {
    return mName;
}
