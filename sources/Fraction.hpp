#include <iostream>

namespace ariel
{
    class Fraction{
        private:
            int numerator; // represents the numerator in the fraction
            int denominator; // represents the denominator in the fraction
        public:
            Fraction(int, int); // constructor with default denominator and numerator of 1
            Fraction(float); // constructor for floats
            Fraction() = default; // constructor
            Fraction(const Fraction&) = default; // copy constructor
            Fraction(Fraction&&) noexcept = default; // move constructor
            Fraction& operator=(Fraction&&) noexcept = default; // move assignment operator
            ~Fraction() = default; // default destructor 
            Fraction& operator=(const Fraction&); // assignment operator for fractions
            Fraction& operator=(const float&); // assignment operator for floats; 
            //operator float() const; // conversion operator to float
            Fraction operator+(const Fraction&) const; // addition operator for fractions
            Fraction operator+(const float&) const; // addition operator for fraction and float
            friend Fraction operator+(const float&, const Fraction&); // addition operator for float and fraction
            Fraction operator-(const Fraction&) const; // subtraction operator for fractions
            Fraction operator-(const float&) const; // subtraction operator for fraction and float
            friend Fraction operator-(const float&, const Fraction&); // subtraction operator for float and fraction
            Fraction operator*(const Fraction&) const; // multiplication operator for fractions
            Fraction operator*(const float&) const; // multiplication operator for fraction and float
            friend Fraction operator*(const float&, const Fraction&); // multiplication operator for float and fraction
            Fraction operator/(const Fraction&) const; // division operator for fractions
            Fraction operator/(const float&) const; // division operator for fraction and float
            friend Fraction operator/(const float&, const Fraction&); // division operator for float and fraction
            bool operator==(const Fraction&) const; // equality operator for fractions
            bool operator==(const float&) const; // equality operator for float and fraction
            friend bool operator==(const float&, const Fraction&); // equality operator for fraction and float
            bool operator>(const Fraction&) const; // greater than operator for fractions
            bool operator>(const float&) const; // greater than operator for fraction and float
            friend bool operator>(const float&, const Fraction&); // greater than operator for float and fraction
            bool operator<(const Fraction&) const; // less than operator for fractions
            bool operator<(const float&) const; // less than operator for fraction and float
            friend bool operator<(const float&, const Fraction&); // less than operator for float and fraction
            bool operator>=(const Fraction&) const; // +greater than or equal to operator for fractions
            bool operator>=(const float&) const; // greater than or equal to operator for fraction and float
            friend bool operator>=(const float&, const Fraction&); // greater than or equal to operator for float and fraction
            bool operator<=(const Fraction&) const; // less than or equal to operator for fractions
            bool operator<=(const float&) const; // less than or equal to operator for fraction and float
            friend bool operator<=(const float&, const Fraction&); // less than or equal to operator for float and fraction
            Fraction& operator++(); // prefix increment operator
            Fraction operator++(int); // postfix increment operator
            Fraction& operator--(); // prefix decrement operator
            Fraction operator--(int); // postfix decrement operator
            friend std::ostream& operator<<(std::ostream&, const Fraction&); // output operator for fractions
            friend std::ostream& operator<<(std::ostream&, const float&); // output operator for floats
            friend std::istream& operator>>(std::istream&, Fraction&); // input operator for fractions
            friend std::istream& operator>>(std::istream&, float&); // input operator for floats

            // Getters
            int getNumerator() const;
            int getDenominator() const;

    };

    // friend utility functions
    int gcd(int, int); // returns the greatest common divisor of a and b, to be used to find the reduced form of a fraction
    Fraction convert_float_to_fraction(float); // converts a float to a fraction
}