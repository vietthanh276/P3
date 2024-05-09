#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
 * rational.h
 * Header file for Rational number operations
 */

// Define the Rational struct
struct Rational {
    int numerator;      // Numerator of the rational number
    int denominator;    // Denominator of the rational number
};

typedef struct Rational Rational;

// Function prototypes

/*
 * Create a Rational number with the given numerator and denominator.
 * Parameters:
 *   - num: Numerator of the Rational number
 *   - denom: Denominator of the Rational number
 * Returns:
 *   - A Rational number with the given numerator and denominator
 */
Rational create_rational(const int num, const int denom);

/*
 * Create a copy of the given Rational number.
 * Parameters:
 *   - orig: Pointer to the original Rational number to copy
 * Returns:
 *   - A copy of the original Rational number
 */
Rational copy_rational(const Rational* orig);

/*
 * Simplify the given Rational number by dividing the numerator and denominator by their greatest common divisor.
 * Parameters:
 *   - rational: Pointer to the Rational number to simplify
 */
void simplify(Rational* rational);

/*
 * Add two Rational numbers.
 * Parameters:
 *   - num1: Pointer to the first Rational number
 *   - num2: Pointer to the second Rational number
 * Returns:
 *   - The sum of the two Rational numbers
 */
Rational add(const Rational* num1, const Rational* num2);

/*
 * Subtract one Rational number from another.
 * Parameters:
 *   - num1: Pointer to the Rational number to subtract from
 *   - num2: Pointer to the Rational number to subtract
 * Returns:
 *   - The result of subtracting num2 from num1
 */
Rational subtract(const Rational* num1, const Rational* num2);

/*
 * Multiply two Rational numbers.
 * Parameters:
 *   - num1: Pointer to the first Rational number
 *   - num2: Pointer to the second Rational number
 * Returns:
 *   - The product of the two Rational numbers
 */
Rational multiply(const Rational* num1, const Rational* num2);

/*
 * Divide one Rational number by another.
 * Parameters:
 *   - num1: Pointer to the Rational number to divide
 *   - num2: Pointer to the Rational number to divide by
 * Returns:
 *   - The result of dividing num1 by num2
 */
Rational divide(const Rational* num1, const Rational* num2);

/*
 * Print the given Rational number to the specified file stream.
 * Parameters:
 *   - file: Pointer to the file stream where the Rational number will be printed
 *   - rational: Pointer to the Rational number to print
 */
void print(FILE* file, const Rational* rational);

/*
 * Check if two Rational numbers are equal.
 * Parameters:
 *   - num1: Pointer to the first Rational number
 *   - num2: Pointer to the second Rational number
 * Returns:
 *   - true if the two Rational numbers are equal, false otherwise
 */
bool equal(const Rational* num1, const Rational* num2);

/*
 * Compare two Rational numbers.
 * Parameters:
 *   - num1: Pointer to the first Rational number
 *   - num2: Pointer to the second Rational number
 * Returns:
 *   - An integer value indicating the comparison result:
 *       - negative if num1 is less than num2
 *       - zero if num1 is equal to num2
 *       - positive if num1 is greater than num2
 */
int compare(const Rational* num1, const Rational* num2);

/*
 * Calculate the greatest common divisor (GCD) of two integers using Euclid's algorithm.
 * Parameters:
 *   - a: First integer
 *   - b: Second integer
 * Returns:
 *   - The GCD of a and b
 */
int gcd(int a, int b);


