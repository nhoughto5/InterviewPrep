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

float Recipe::getGrossTotal() {
    float total{ 0.0f };
    for (auto& i : mIngredients) {
        total += i.m_quantity() * i.m_price().m_value();
    }
    return total;
}

float Recipe::getDiscount() {
    return 0.0f;
}

float Recipe::getSalesTax() {
    float total{ 0.0f };
    for(auto& i : mIngredients) {
        total += (i.m_type() == Produce) ? 0.0f : i.getValue() * SALES_TAX;
    }
    return 0;
}

std::string Recipe::printTotalCost() {
    //std::stringstream stream;
    //stream << std::fixed << std::setprecision(2) << getTotal();
    //return stream.str();
    return {};
}

std::string Recipe::printWellnessDiscount() {
    return {};
}

std::string Recipe::printSalesTax() {


    return {};
}
