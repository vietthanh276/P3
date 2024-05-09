#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "rational.h"


// Function to read rational numbers and operation from a file
// Returns the number of items successfully read
int read_rational(FILE *f1, int *n1, int *d1, int *n2, int *d2, char op[]) {
    char line[100];
    char *s = fgets(line, 99, f1);
    if (s == NULL) {
        return 0; // Return 0 if end of file is reached
    } else {
        // Parse the line based on different formats
        if (sscanf(line, "%d/%d %s %d/%d", n1, d1, op, n2, d2) == 5) {
            return 5;
        } else if (sscanf(line, "%d %s %d/%d", n1, op, n2, d2) == 4) {
            *d1 = 1;
            return 4;
        } else if (sscanf(line, "%d/%d %s %d", n1, d1, op, n2) == 4) {
            *d2 = 1;
            return 4;
        } else if (sscanf(line, "%d %s %d", n1, op, n2) == 3) {
            *d1 = 1;
            *d2 = 1;
            return 3;
        } else {
            return -1; // Return -1 for invalid input format
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc < 3) {
        printf("Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }

    // Single input file case
    if (argc == 3) {
        // Open input file
        FILE *input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            printf("Error: Unable to open input file %s\n", argv[1]);
            return 1;
        }

        // Open output file
        FILE *output_file = fopen(argv[argc - 1], "w");
        if (output_file == NULL) {
            printf("Error: Unable to open output file %s\n", argv[argc - 1]);
            fclose(input_file);
            return 1;
        }

        // Declare variables
        int n1, d1, n2, d2; // variables for input_file
        char op[3]; // operator for input_file
        bool eqResult;
        bool compResult;
        Rational result; // Declare result here

        // Process input_file
        while (read_rational(input_file, &n1, &d1, &n2, &d2, op) > 0) {
            // Create rational numbers based on input
            Rational rational1 = create_rational(n1, d1);
            Rational rational2 = create_rational(n2, d2);
            // Perform arithmetic operations
            switch (op[0]) {
                case '+':
                    result = add(&rational1, &rational2);
                    break;
                case '-':
                    result = subtract(&rational1, &rational2);
                    break;
                case '*':
                    result = multiply(&rational1, &rational2);
                    break;
                case '/':
                    result = divide(&rational1, &rational2);
                    break;
                default:
                    // Perform comparison operations
                    if (strcmp(op, "==") == 0) {
                        eqResult = equal(&rational1, &rational2);
                        fprintf(output_file, "%d/%d == %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, eqResult ? "true" : "false");
                    } else if (strcmp(op, "!=") == 0) {
                        eqResult = !equal(&rational1, &rational2);
                        fprintf(output_file, "%d/%d != %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, eqResult ? "true" : "false");
                    } else if (strcmp(op, ">") == 0) {
                        compResult = compare(&rational1, &rational2) > 0;
                        fprintf(output_file, "%d/%d > %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op, "<") == 0) {
                        compResult = compare(&rational1, &rational2) < 0;
                        fprintf(output_file, "%d/%d < %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op, ">=") == 0) {
                        compResult = compare(&rational1, &rational2) >= 0;
                        fprintf(output_file, "%d/%d >= %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op, "<=") == 0) {
                        compResult = compare(&rational1, &rational2) <= 0;
                        fprintf(output_file, "%d/%d <= %d/%d\t: %s\n", rational1.numerator, rational1.denominator, rational2.numerator, rational2.denominator, compResult ? "true" : "false");
                    } else {
                        printf("Error: Invalid operator\n");
                        fclose(input_file);
                        fclose(output_file);
                        return 1;
                    }
                    continue;
            }
            // Print operation and result
            print(output_file, &rational1);
            fprintf(output_file, " %s ", op);
            print(output_file, &rational2);
            fprintf(output_file, "\t: ");
            print(output_file, &result);
            fprintf(output_file, "\n");
        }
        // Close files
        fclose(input_file);
        fclose(output_file);

        return 0;
    }

    // Dual input file case
    if (argc == 4) {
        // Open input files
        FILE *input_file1 = fopen(argv[1], "r");
        if (input_file1 == NULL) {
            printf("Error: Unable to open input file %s\n", argv[1]);
            return 1;
        }

        FILE *input_file2 = fopen(argv[2], "r");
        if (input_file2 == NULL) {
            printf("Error: Unable to open input file %s\n", argv[2]);
            fclose(input_file1);
            return 1;
        }

        // Open output file
        FILE *output_file = fopen(argv[argc - 1], "w");
        if (output_file == NULL) {
            printf("Error: Unable to open output file %s\n", argv[argc - 1]);
            fclose(input_file1);
            fclose(input_file2);
            return 1;
        }

        // Declare variables
        int n1_1, d1_1, n2_1, d2_1; // variables for input_file1
        int n1_2, d1_2, n2_2, d2_2; // variables for input_file2
        char op_1[3]; // operator for input_file1
        char op_2[3]; // operator for input_file2
        bool eqResult;
        bool compResult;
        Rational result_1, result_2; // Declare result variables for both input files
        bool defaultCaseEntered = false; // Flag to track if default case is entered

        // Process input_file1
        while (read_rational(input_file1, &n1_1, &d1_1, &n2_1, &d2_1, op_1) > 0) {
            // Process each line of input from both files and write to output
            Rational rational1_1 = create_rational(n1_1, d1_1);
            Rational rational2_1 = create_rational(n2_1, d2_1);
            switch (op_1[0]) {
                // Perform arithmetic operations
                case '+':
                    result_1 = add(&rational1_1, &rational2_1);
                    break;
                case '-':
                    result_1 = subtract(&rational1_1, &rational2_1);
                    break;
                case '*':
                    result_1 = multiply(&rational1_1, &rational2_1);
                    break;
                case '/':
                    result_1 = divide(&rational1_1, &rational2_1);
                    break;
                default:
                    defaultCaseEntered = true;
                    // Perform comparison operations
                    if (strcmp(op_1, "==") == 0) {
                        eqResult = equal(&rational1_1, &rational2_1);
                        fprintf(output_file, "%d/%d == %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, eqResult ? "true" : "false");
                    } else if (strcmp(op_1, "!=") == 0) {
                        eqResult = !equal(&rational1_1, &rational2_1);
                        fprintf(output_file, "%d/%d != %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, eqResult ? "true" : "false");
                    } else if (strcmp(op_1, ">") == 0) {
                        compResult = compare(&rational1_1, &rational2_1) > 0;
                        fprintf(output_file, "%d/%d > %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op_1, "<") == 0) {
                        compResult = compare(&rational1_1, &rational2_1) < 0;
                        fprintf(output_file, "%d/%d < %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op_1, ">=") == 0) {
                        compResult = compare(&rational1_1, &rational2_1) >= 0;
                        fprintf(output_file, "%d/%d >= %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, compResult ? "true" : "false");
                    } else if (strcmp(op_1, "<=") == 0) {
                        compResult = compare(&rational1_1, &rational2_1) <= 0;
                        fprintf(output_file, "%d/%d <= %d/%d\t: %s\n", rational1_1.numerator, rational1_1.denominator, rational2_1.numerator, rational2_1.denominator, compResult ? "true" : "false");
                    } else {
                        printf("Error: Invalid operator\n");
                        fclose(input_file1);
                        fclose(input_file2);
                        fclose(output_file);
                        return 1;
                    }
            }
            // Print operation and result for input_file1
            if (!defaultCaseEntered) {
                print(output_file, &rational1_1);
                fprintf(output_file, " %s ", op_1);
                print(output_file, &rational2_1);
                fprintf(output_file, "\t: ");
                print(output_file, &result_1);
                fprintf(output_file, "\n");
            }
            defaultCaseEntered = false; // Reset the flag for the next iteration
        }


        // Process input_file2
        while (read_rational(input_file2, &n1_2, &d1_2, &n2_2, &d2_2, op_2) > 0) {
                // Process each line of input from input_file2 and write to output
                Rational rational1_2 = create_rational(n1_2, d1_2);
                Rational rational2_2 = create_rational(n2_2, d2_2);
                switch (op_2[0]) {
                    // Perform arithmetic operations
                    case '+':
                        result_2 = add(&rational1_2, &rational2_2);
                        break;
                    case '-':
                        result_2 = subtract(&rational1_2, &rational2_2);
                        break;
                    case '*':
                        result_2 = multiply(&rational1_2, &rational2_2);
                        break;
                    case '/':
                        result_2 = divide(&rational1_2, &rational2_2);
                        break;
                    default:
                        defaultCaseEntered = true;
                        // Perform comparison operations
                        if (strcmp(op_2, "==") == 0) {
                            eqResult = equal(&rational1_2, &rational2_2);
                            fprintf(output_file, "%d/%d == %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, eqResult ? "true" : "false");
                        } else if (strcmp(op_2, "!=") == 0) {
                            eqResult = !equal(&rational1_2, &rational2_2);
                            fprintf(output_file, "%d/%d != %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, eqResult ? "true" : "false");
                        } else if (strcmp(op_2, ">") == 0) {
                            compResult = compare(&rational1_2, &rational2_2) > 0;
                            fprintf(output_file, "%d/%d > %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, compResult ? "true" : "false");
                        } else if (strcmp(op_2, "<") == 0) {
                            compResult = compare(&rational1_2, &rational2_2) < 0;
                            fprintf(output_file, "%d/%d < %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, compResult ? "true" : "false");
                        } else if (strcmp(op_2, ">=") == 0) {
                            compResult = compare(&rational1_2, &rational2_2) >= 0;
                            fprintf(output_file, "%d/%d >= %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, compResult ? "true" : "false");
                        } else if (strcmp(op_2, "<=") == 0) {
                            compResult = compare(&rational1_2, &rational2_2) <= 0;
                            fprintf(output_file, "%d/%d <= %d/%d\t: %s\n", rational1_2.numerator, rational1_2.denominator, rational2_2.numerator, rational2_2.denominator, compResult ? "true" : "false");
                        } else {
                            printf("Error: Invalid operator\n");
                            fclose(input_file1);
                            fclose(input_file2);
                            fclose(output_file);
                            return 1;
                        }
                }
                // Print operation and result for input_file2
                if (!defaultCaseEntered) {
                    print(output_file, &rational1_2);
                    fprintf(output_file, " %s ", op_2);
                    print(output_file, &rational2_2);
                    fprintf(output_file, "\t: ");
                    print(output_file, &result_2);
                    fprintf(output_file, "\n");
                }
                defaultCaseEntered = false; // Reset the flag for the next iteration
            }

        // Close files
        fclose(input_file1);
        fclose(input_file2);
        fclose(output_file);
        return 0;

        }
    return 0;
    }

