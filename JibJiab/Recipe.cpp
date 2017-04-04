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
    return total;
}

float Recipe::getSalesTax() {
    float total{ 0.0f };
    for(auto& i : mIngredients) {
        total += (i.m_type() == Produce) ? 0.0f : i.getValue() * SALES_TAX;
    }

    //Round to nearest seven cents
    return roundUtil (total);
}

std::string Recipe::printTotalCost() {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << getTotalCost();
    return stream.str();
}

std::string Recipe::printWellnessDiscount() {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << getDiscount();
    return stream.str();
}

std::string Recipe::printSalesTax() {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << getSalesTax();
    return stream.str();
}
