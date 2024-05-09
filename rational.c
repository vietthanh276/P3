#include <stdio.h>
#include "rational.h"

/*
 * rational.c
 * Implementation file for Rational number operations
 */


// Calculate the greatest common divisor (GCD) of two integers using Euclid's algorithm
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

// Create a Rational number with the given numerator and denominator
Rational create_rational(const int num, const int denom) {
    Rational rational;
    
    // Assign numerator and denominator
    rational.numerator = num;
    rational.denominator = denom;
    
    // Simplify the rational number
    simplify(&rational);
    
    return rational;
}

// Create a copy of the given Rational number
Rational copy_rational(const Rational* orig) {
    Rational copy;
    
    // Copy numerator and denominator
    copy.numerator = orig->numerator;
    copy.denominator = orig->denominator;
    
    // Simplify the copied rational number
    simplify(&copy);
    
    return copy;
}

// Simplify the given Rational number by dividing the numerator and denominator by their greatest common divisor
void simplify(Rational* rational) {
    // Check if the denominator is negative
    if (rational->denominator < 0) {
        // Store the negative sign with the numerator
        rational->numerator *= -1;
        rational->denominator *= -1;
    }

    // Find the greatest common divisor using the gcd function
    int gcd_value = gcd(abs(rational->numerator), abs(rational->denominator));

    // Simplify the fraction by dividing the numerator and denominator by the GCD
    rational->numerator /= gcd_value;
    rational->denominator /= gcd_value;
}


// Add two Rational numbers
Rational add(const Rational* num1, const Rational* num2) {
    Rational result;

    // Find the least common multiple of the denominators
    int lcm = (num1->denominator * num2->denominator) / gcd(num1->denominator, num2->denominator);

    // Calculate the numerators after converting to the common denominator
    int new_num1 = num1->numerator * (lcm / num1->denominator);
    int new_num2 = num2->numerator * (lcm / num2->denominator);

    // Calculate the sum of the numerators
    result.numerator = new_num1 + new_num2;
    result.denominator = lcm;

    // Simplify the result
    simplify(&result);

    return result;
}

// Subtract one Rational number from another
Rational subtract(const Rational* num1, const Rational* num2) {
    Rational result;

    // Find the least common multiple of the denominators
    int lcm = (num1->denominator * num2->denominator) / gcd(num1->denominator, num2->denominator);

    // Calculate the numerators after converting to the common denominator
    int new_num1 = num1->numerator * (lcm / num1->denominator);
    int new_num2 = num2->numerator * (lcm / num2->denominator);

    // Calculate the difference of the numerators
    result.numerator = new_num1 - new_num2;
    result.denominator = lcm;

    // Simplify the result
    simplify(&result);

    return result;
}

// Multiply two Rational numbers
Rational multiply(const Rational* num1, const Rational* num2) {
    Rational result;

    // Calculate the new numerator and denominator
    result.numerator = num1->numerator * num2->numerator;
    result.denominator = num1->denominator * num2->denominator;

    // Simplify the result
    simplify(&result);

    return result;
}

// Divide one Rational number by another
Rational divide(const Rational* num1, const Rational* num2) {
    Rational result;

    // Check if num2 is zero
    if (num2->numerator == 0) {
        // Division by zero, return an error or handle it as appropriate for your application
        // Here, I'm returning a result with numerator set to 0 and denominator set to 1
        result.numerator = 0;
        result.denominator = 1;
        return result;
    }

    // Calculate the new numerator and denominator by multiplying num1 by the reciprocal of num2
    result.numerator = num1->numerator * num2->denominator;
    result.denominator = num1->denominator * num2->numerator;

    // Simplify the result
    simplify(&result);

    return result;
}

// Print the given Rational number to the specified file stream
void print(FILE* file, const Rational* rational) {
    // Check if the rational number is a whole number
    if (rational->denominator == 1) {
        fprintf(file, "%d", rational->numerator);
    } else {
        fprintf(file, "%d/%d", rational->numerator, rational->denominator);
    }
}

// Check if two Rational numbers are equal
bool equal(const Rational* num1, const Rational* num2) {
    // If either denominator is 1, compare numerators directly
    if (num1->denominator == 1 || num2->denominator == 1) {
        return num1->numerator == num2->numerator;
    }

    // Cross multiply to compare
    int cross_product1 = num1->numerator * num2->denominator;
    int cross_product2 = num2->numerator * num1->denominator;

    // Check if the cross products are equal
    return cross_product1 == cross_product2;
}

// Compare two Rational numbers
int compare(const Rational* num1, const Rational* num2) {
    // If either denominator is 1, compare numerators directly
    if (num1->denominator == 1 || num2->denominator == 1) {
        if (num1->numerator < num2->numerator) {
            return -1;
        } else if (num1->numerator > num2->numerator) {
            return 1;
        } else {
            return 0; // If equal
        }
    }

    // Cross multiply to compare
    int cross_product1 = num1->numerator * num2->denominator;
    int cross_product2 = num2->numerator * num1->denominator;

    // Compare the cross products to determine the result
    if (cross_product1 < cross_product2) {
        return -1;
    } else if (cross_product1 > cross_product2) {
        return 1;
    } else {
        return 0; // If equal
    }
}

