#pragma once
#include "Utilities.h"
#include <string>
#include <iomanip> // setprecision
#include "Money.h"

class Ingredient
{
public:
    // Constructors
	Ingredient();


    Ingredient(IngredientType type, float quantity, bool organic, const std::string& name, const std::string& unit_of_measure, const Money& price);

	~Ingredient();

    // Copy and Move
    Ingredient(const Ingredient& other);
    Ingredient(Ingredient&& other) noexcept;
    Ingredient& operator=(const Ingredient& other);
    Ingredient& operator=(Ingredient&& other) noexcept;

    // Member Methods
    std::string toString() const;


    // Getters
    IngredientType m_type() const;
    float m_quantity() const;
    bool organic() const;
    std::string m_name() const;
    std::string m_unit_of_measure() const;

private:
	IngredientType mType;
	float mQuantity;
	bool mOrganic;
	std::string mName, mUnitOfMeasure;
    Money mPrice;
};

