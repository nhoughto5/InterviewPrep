#include "Ingredient.h"
#include "sstream" // stringstream


Ingredient::Ingredient(): mType (Other),
                          mQuantity (0),
                          mOrganic (false) {
}

Ingredient::Ingredient(IngredientType type, float quantity, bool organic, const std::string& name, const std::string& unit_of_measure, const Money& price): mType (type),
                                                                                                                                                            mQuantity (quantity),
                                                                                                                                                            mOrganic (organic),
                                                                                                                                                            mName (name),
                                                                                                                                                            mUnitOfMeasure (unit_of_measure),
                                                                                                                                                            mPrice (price) {
}

Ingredient::Ingredient(const Ingredient& other): mType (other.mType),
                                                 mQuantity (other.mQuantity),
                                                 mOrganic (other.mOrganic),
                                                 mName (other.mName),
                                                 mUnitOfMeasure (other.mUnitOfMeasure),
                                                 mPrice (other.mPrice) {
}

Ingredient::Ingredient(Ingredient&& other) noexcept: mType (other.mType),
                                                     mQuantity (other.mQuantity),
                                                     mOrganic (other.mOrganic),
                                                     mName (std::move (other.mName)),
                                                     mUnitOfMeasure (std::move (other.mUnitOfMeasure)),
                                                     mPrice (std::move (other.mPrice)) {
}

Ingredient& Ingredient::operator=(const Ingredient& other) {
    if (this == &other)
        return *this;
    mType = other.mType;
    mQuantity = other.mQuantity;
    mOrganic = other.mOrganic;
    mName = other.mName;
    mUnitOfMeasure = other.mUnitOfMeasure;
    mPrice = other.mPrice;
    return *this;
}

Ingredient& Ingredient::operator=(Ingredient&& other) noexcept {
    if (this == &other)
        return *this;
    mType = other.mType;
    mQuantity = other.mQuantity;
    mOrganic = other.mOrganic;
    mName = std::move (other.mName);
    mUnitOfMeasure = std::move (other.mUnitOfMeasure);
    mPrice = std::move (other.mPrice);
    return *this;
}

std::string Ingredient::toString() const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision (2) << mQuantity;
    std::string orgStr = mOrganic ? "organic " : "";
    std::string ofStr = mUnitOfMeasure.empty() ? "" : " of ";
    return stream.str() + " " + mUnitOfMeasure + ofStr + orgStr + mName + " = " + mPrice.toString();
}

IngredientType Ingredient::m_type() const {
    return mType;
}

float Ingredient::m_quantity() const {
    return mQuantity;
}

bool Ingredient::organic() const {
    return mOrganic;
}

std::string Ingredient::m_name() const {
    return mName;
}

std::string Ingredient::m_unit_of_measure() const {
    return mUnitOfMeasure;
}

void Ingredient::set_m_quantity(const float quantity) {
    mQuantity = quantity;
}

void Ingredient::set_m_price(const Money& price) {
    mPrice = price;
}
