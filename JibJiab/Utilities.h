#ifndef UTILITIES_H
#define UTILITIES_H
#pragma once
#include <math.h>
#include <iomanip>

enum IngredientType {Produce, Meat, Pantry, Other};
const float SALES_TAX = 0.086f;
const float WELLNESS_DISCOUNT = 0.05f;

inline float roundUpUtil(float money, float round) {
    return (ceil(money / round) * round);
}
#endif // !UTILITIES_H


