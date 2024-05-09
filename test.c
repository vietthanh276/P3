#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "rational.h"

int read_rational(FILE *f1, int *n1, int *d1, int *n2, int *d2, char op[]) {
    char line[100];
    char *s = fgets(line, 99, f1);
    if (s == NULL) {
        return 0;
    } else {
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
            return -1;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s input.txt output.txt\n", argv[0]);
        return 1;
    }
    
    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("Error: Unable to open input file %s\n", argv[1]);
        return 1;
    }

    FILE *output_file = fopen(argv[argc - 1], "w");
    if (output_file == NULL) {
        printf("Error: Unable to open output file %s\n", argv[argc - 1]);
        fclose(input_file);
        return 1;
    }

    int n1, d1, n2, d2;
    char op[3];
    bool eqResult;
    bool compResult;
    while (read_rational(input_file, &n1, &d1, &n2, &d2, op) > 0) {
        Rational rational1 = create_rational(n1, d1);
        Rational rational2 = create_rational(n2, d2);
        Rational result;
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

        print(output_file, &rational1);
        fprintf(output_file, " %s ", op);
        print(output_file, &rational2);
        fprintf(output_file, "\t: ");
        print(output_file, &result);
        fprintf(output_file, "\n");
    }

    fclose(input_file);
    fclose(output_file);

    return 0;
}
