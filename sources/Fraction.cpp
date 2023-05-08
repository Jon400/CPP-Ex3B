#include "Fraction.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <limits>

using namespace ariel;

/*
Inline implementation of the Fraction class
*/

ariel::Fraction::Fraction(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    if (numerator == 0){
        this->numerator = 0;
        this->denominator = 1;
        return;
    }

    int sign = 1;
    int numerator_sign = numerator;
    int denominator_sign = denominator;
    if (numerator_sign < 0){
        sign *= -1;
        numerator_sign *= -1;
    }
    if (denominator_sign < 0){
        sign *= -1;
        denominator_sign *= -1;
    }

    int gcd = ariel::gcd(numerator_sign, denominator_sign);
    this->numerator = sign *  (numerator_sign / gcd);
    this->denominator = denominator_sign / gcd;

    //std::cout << "numerator_sign: " << *this << std::endl;
}

ariel::Fraction::Fraction(float f)
{
    Fraction r = ariel::convert_float_to_fraction(f);
    *this = r;
}

Fraction& ariel::Fraction::operator=(const Fraction & r)
{
    this->numerator = r.numerator;
    this->denominator = r.denominator;
    return *this;
}


Fraction& ariel::Fraction::operator=(const float & f)
{
    Fraction f_to_r = Fraction(f);
    *this = f_to_r;
    return *this;
}

Fraction ariel::Fraction::operator+(const Fraction & r) const
{
    if ((float)(this->numerator + r.numerator) != (float)(this->numerator) + (float)(r.numerator)){
        throw std::overflow_error("Overflow detected");
    }
    if ((float)(this->denominator + r.denominator) != (float)(this->denominator) + (float)(r.denominator)){
        throw std::overflow_error("Overflow detected");
    }
    int gcd = ariel::gcd(this->denominator, r.denominator);
    int lcm = (this->denominator * r.denominator) / gcd;
    return Fraction(this->numerator * (lcm / this->denominator) + r.numerator * (lcm / r.denominator), lcm);
}

Fraction ariel::Fraction::operator+(const float & f) const
{
    Fraction f_to_r = Fraction(f);
    int gcd = ariel::gcd(this->denominator, f_to_r.denominator);
    int lcm = (this->denominator * f_to_r.denominator) / gcd;
    return Fraction(this->numerator * (lcm / this->denominator) + f_to_r.numerator * (lcm / f_to_r.denominator), lcm);
}

Fraction ariel::operator+(const float & f, const Fraction & r)
{
    Fraction f_to_r = Fraction(f);
    int gcd = ariel::gcd(f_to_r.denominator, r.denominator);
    int lcm = (f_to_r.denominator * r.denominator) / gcd;
    return Fraction(f_to_r.numerator * (lcm / f_to_r.denominator) + r.numerator * (lcm / r.denominator), lcm);
}

Fraction ariel::Fraction::operator-(const Fraction & r) const
{
    int gcd = ariel::gcd(this->denominator, r.denominator);
    int lcm = (this->denominator * r.denominator) / gcd;
    if ((((float)this->numerator / (float)this->denominator) - ((float)r.numerator / (float)r.denominator)) < (float)std::numeric_limits<int>::min() ||
        (((float)this->numerator / (float)this->denominator) - ((float)r.numerator / (float)r.denominator)) > (float)std::numeric_limits<int>::max()){
        throw std::overflow_error("Overflow detected");
    }
    return Fraction(this->numerator * (lcm / this->denominator) - r.numerator * (lcm / r.denominator), lcm);
}

Fraction ariel::Fraction::operator-(const float & f) const
{
    Fraction f_to_r = Fraction(f);
    int gcd = ariel::gcd(this->denominator, f_to_r.denominator);
    int lcm = (this->denominator * f_to_r.denominator) / gcd;
    return Fraction(this->numerator * (lcm / this->denominator) - f_to_r.numerator * (lcm / f_to_r.denominator), lcm);
}

Fraction ariel::operator-(const float & f, const Fraction & r)
{
    Fraction f_to_r = Fraction(f);
    int gcd = ariel::gcd(f_to_r.denominator, r.denominator);
    int lcm = (f_to_r.denominator * r.denominator) / gcd;
    return Fraction(f_to_r.numerator * (lcm / f_to_r.denominator) - r.numerator * (lcm / r.denominator), lcm);

    return Fraction(f - (r.numerator/r.denominator));
}

Fraction ariel::Fraction::operator*(const Fraction & r) const
{   
    // Handling overflow
    if (r.numerator != 0){
        if ((int)((this->numerator * (float)r.numerator)/r.numerator) != (int)this->numerator){
            throw std::overflow_error("Overflow detected");
        }
    }
    if (r.denominator != 0){
        if ((int)((this->denominator * (float)r.denominator)/r.denominator) != (int)this->denominator){
            throw std::overflow_error("Overflow detected");
        }
    }
    return Fraction(this->numerator * r.numerator, this->denominator * r.denominator);
}

Fraction ariel::Fraction::operator*(const float & f) const
{
    Fraction f_to_r = Fraction(f);
    return Fraction(this->numerator * f_to_r.numerator, this->denominator * f_to_r.denominator);
}

Fraction ariel::operator*(const float & f, const Fraction & r)
{
    Fraction f_to_r = Fraction(f);
    return Fraction(f_to_r.numerator * r.numerator, f_to_r.denominator * r.denominator);
}

Fraction ariel::Fraction::operator/(const Fraction & r) const
{
    // Handling overflow
    if (((float)this->numerator * (float)r.denominator) > (float)std::numeric_limits<int>::max() ||
        ((float)this->numerator * (float)r.denominator) < (float)std::numeric_limits<int>::min() ||
        ((float)this->denominator * (float)r.numerator) > (float)std::numeric_limits<int>::max() ||
        ((float)this->denominator * (float)r.numerator) < (float)std::numeric_limits<int>::min()){
        throw std::overflow_error("Overflow detected");

    }
    if (r == 0){
        throw std::runtime_error("Denominator cannot be zero");
    }
    return Fraction(this->numerator * r.denominator, this->denominator * r.numerator);

}

Fraction ariel::Fraction::operator/(const float & f) const
{
    // denominator cannot be zero runtime exception
    if (f == 0){
        throw std::runtime_error("Denominator cannot be zero");
    }
    Fraction f_to_r = Fraction(f);
    return Fraction(this->numerator * f_to_r.denominator, this->denominator * f_to_r.numerator);
}

Fraction ariel::operator/(const float & f, const Fraction & r)
{
    // denominator cannot be zero runtime exception
    if (r == 0){
        throw std::runtime_error("Denominator cannot be zero");
    }
    Fraction f_to_r = Fraction(f);
    return Fraction(f_to_r.numerator * r.denominator, f_to_r.denominator * r.numerator);
}

bool ariel::Fraction::operator==(const Fraction & r) const
{
    return (this->numerator == r.numerator) && (this->denominator == r.denominator);
}

bool ariel::Fraction::operator==(const float & f) const
{
    Fraction r_to_f = Fraction((int)(this->numerator/(float)this->denominator * 1000)/1000.0);
    Fraction f_to_r = Fraction(f);
    return (r_to_f.numerator == f_to_r.numerator) && (r_to_f.denominator == f_to_r.denominator);
}

bool ariel::operator==(const float & f, const Fraction & r)
{
    Fraction r_to_f = Fraction(std::round(r.numerator/(float)r.denominator * 1000)/1000);
    Fraction f_to_r = Fraction(f);
    return (f_to_r.numerator == r_to_f.numerator) && (f_to_r.denominator == r_to_f.denominator);
}

bool ariel::Fraction::operator>(const Fraction & r) const
{
    return ((float)this->numerator/this->denominator) > ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator>(const float & f) const
{
    return ((float)this->numerator/this->denominator) > f;
}

bool ariel::operator>(const float & f, const Fraction & r)
{
    return f > ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator<(const Fraction & r) const
{
    return ((float)this->numerator/this->denominator) < ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator<(const float & f) const
{
    return ((float)this->numerator/this->denominator) < f;
}

bool ariel::operator<(const float & f, const Fraction & r)
{
    return f < ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator>=(const Fraction & r) const
{
    return ((float)this->numerator/this->denominator) >= ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator>=(const float & f) const
{
    return ((float)this->numerator/this->denominator) >= f;
}

bool ariel::operator>=(const float & f, const Fraction & r)
{
    return f >= ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator<=(const Fraction & r) const
{
    return ((float)this->numerator/this->denominator) <= ((float)r.numerator/r.denominator);
}

bool ariel::Fraction::operator<=(const float & f) const
{
    return ((float)this->numerator/this->denominator) <= f;
}

bool ariel::operator<=(const float & f, const Fraction & r)
{
    return f <= ((float)r.numerator/r.denominator);
}

Fraction& ariel::Fraction::operator++()
{
    this->numerator += this->denominator;
    return *this;
}

Fraction ariel::Fraction::operator++(int dummy)
{
    int prev_numerator = this->numerator;
    this->numerator += this->denominator;
    return Fraction(prev_numerator, this->denominator);
}

Fraction& ariel::Fraction::operator--()
{
    this->numerator -= this->denominator;
    return *this;
}

Fraction ariel::Fraction::operator--(int dummy)
{
    int prev_numerator = this->numerator;
    this->numerator -= this->denominator;
    return Fraction(prev_numerator, this->denominator);
}

std::ostream& ariel::operator<<(std::ostream & output, const Fraction & r)
{
    int numerator, denominator;
    if (r.numerator < 0)
    {
        numerator = -r.numerator;
    }
    else
    {
        numerator = r.numerator;
    }

    if (r.denominator < 0)
    {
        denominator = -r.denominator;
    }
    else
    {
        denominator = r.denominator;
    }
    if(r < 0)
    {
        return (output << '-' << numerator << '/' << denominator);
    }
    return (output << numerator << '/' << denominator);
}

std::ostream &ariel::operator<<(std::ostream & output, const float & f)
{
    Fraction f_to_r = Fraction(f);
    return (output << f_to_r.numerator << '/' << f_to_r.denominator);
}

int getAndCheckNextCharIs(std::istream& input, char expectedChar) {
    char actualChar;
    input >> actualChar;

    if (actualChar!=expectedChar) {
        input.putback(actualChar);
        return 0;
    }

    return 1;
}


std::istream& ariel::operator>>(std::istream & input, Fraction & r)
{
    //---------------------------------------------
    int numerator = 0, denominator = 0;

    // remember place for rewinding
    std::ios::pos_type startPosition = input.tellg();

    if (!(input >> numerator) || (!(input >> denominator) && !(getAndCheckNextCharIs(input, ',') && !(getAndCheckNextCharIs(input, ' ')) 
        && !(getAndCheckNextCharIs(input, '/')))))
    {
        throw std::runtime_error("Invalid string format");
    } 
    else if (denominator == 0)
    {
        throw std::runtime_error("Invalid string format");
    }
    else
    {
        r = Fraction(numerator, denominator);
    }

    return input;
}

std::istream &ariel::operator>>(std::istream & input, float & f)
{
    //---------------------------------------------
    double num = 0;

    // remember place for rewinding
    std::ios::pos_type startPosition = input.tellg();

    if ( (!(input >> num)) ) {
        // rewind on error
        auto errorState = input.rdstate(); // remember error state
        input.clear(); // clear error so seekg will work
        input.seekg(startPosition); // rewind
        input.clear(errorState); // set back the error flag
    } else {
        f = num;
    }

    return input;
}

int ariel::Fraction::getNumerator() const
{
    return this->numerator;
}

int ariel::Fraction::getDenominator() const
{
    return this->denominator;
}

// Returns the greatest common divisor of a and b, using euclid's recursive algorithm
int ariel::gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}

// Covert float to fraction with precision of 3 decimal places
Fraction ariel::convert_float_to_fraction(float f)
{
    if (f>=0)
    {
        return Fraction((int)(f * 1000), 1000);
        
    }
    else
    {
        return Fraction((int)(f * 1000), 1000);
    }
}

