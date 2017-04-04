#include "Recipe.h"
#include <sstream>


Recipe::Recipe()
{
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
    return total + getSalesTax() - getDiscount();
}

float Recipe::getDiscount() {
    float total{ 0.0f };
    for (auto& i : mIngredients) {
        total += i.organic() ? 0.0f : i.getValue() * WELLNESS_DISCOUNT;
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
