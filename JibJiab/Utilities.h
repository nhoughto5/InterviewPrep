#ifndef UTILITIES_H
#define UTILITIES_H
#pragma once
#include <math.h>
#include <iomanip>

enum IngredientType {Produce, Meat, Pantry, Other};
const float SALES_TAX = 0.086f;
const int ROUND_TO = 7;

inline float roundUtil(float money) {
    return (roundf(money / 0.07f) * 0.07f);
}
#endif // !UTILITIES_H


