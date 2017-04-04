#include "Money.h"
#include <sstream> // stringstream
#include <string>


Money::Money(): mValue (0) {
}

Money::Money(float value) : mValue (value) {
}

Money::Money(const Money& other) : mValue (other.mValue) {
}

Money::Money(Money&& other) noexcept : mValue (other.mValue) {
}

Money& Money::operator=(const Money& other) {
    if (this == &other)
        return *this;
    mValue = other.mValue;
    return *this;
}

Money& Money::operator=(Money&& other) noexcept {
    if (this == &other)
        return *this;
    mValue = other.mValue;
    return *this;
}

std::string Money::toString() const {
    std::stringstream stream;
    stream << std::fixed << std::setprecision (2) << mValue;
    return "$" + stream.str();
}

float Money::m_value() const {
    return mValue;
}

void Money::set_m_value(const float value) {
    mValue = value;
}

Money& Money::operator+=(const Money& m) {
    this->mValue += m.m_value();
    return *this;
}

Money& Money::operator-=(const Money& m) {
    this->mValue -= m.m_value();
    return *this;
}

Money& Money::operator+=(const float& f) {
    this->mValue += f;
    return *this;
}

Money& Money::operator-=(const float& f) {
    this->mValue -= f;
    return *this;
}

Money& Money::operator*=(const Money& m) {
    this->mValue *= m.m_value();
    return *this;
}

Money& Money::operator/=(const Money& m) {
    this->mValue /= m.m_value();
    return *this;
}

Money& Money::operator*=(const float& f) {
    this->mValue *= f;
    return *this;
}

Money& Money::operator/=(const float& f) {
    this->mValue /= f;
    return *this;
}

Money operator*(const Money& m1, const Money& m2) {
    return Money(m1.m_value() * m2.m_value());
}
Money operator*(const Money& m1, const float &f) {
    return Money(m1.m_value() * f);
}
Money operator/(const Money& m1, const Money& m2) {
    return Money(m1.m_value() / m2.m_value());
}
Money operator/(const Money& m1, const float &f) {
    return Money(m1.m_value() / f);
}
Money operator+(const Money& m1, const Money& m2) {
    return Money (m1.m_value() + m2.m_value());
}
Money operator+(const Money& m1, const float &f) {
    return Money(m1.m_value() + f);
}
Money operator+(const float &f, const Money& m1) {
    return Money(m1.m_value() + f);
}

Money operator-(const Money& m1, const Money& m2) {
    return Money (m1.m_value() - m2.m_value());
}
Money operator-(const Money& m1, const float &f) {
    return Money(m1.m_value() - f);
}
Money operator-(const float &f, const Money& m1) {
    return Money(m1.m_value() + f);
}