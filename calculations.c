#include <stdio.h>
#include "calculations.h"
#include "history.h"
#define MAX_RESISTORS 20

static void inputResistors(double *resistors, int n);
static double calculateSeries(double *resistors, int n);
static double calculateParallel(double *resistors, int n);

//Ohm's Law Calculator

void ohmsLawMenu(void) {
    int choice;
    double V, I, R;

    while (1) {
        printf("\n------ Ohm's Law Calculator ------\n");
        printf("1. Solve for Voltage  (V = I * R)\n");
        printf("2. Solve for Current  (I = V / R)\n");
        printf("3. Solve for Resistance (R = V / I)\n");
        printf("4. Return to main menu\n");
        printf("----------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1: // V
                printf("Enter I (A): ");
                if (scanf("%lf", &I) != 1) { printf("Invalid.\n"); break; }
                printf("Enter R (Ohm): ");
                if (scanf("%lf", &R) != 1) { printf("Invalid.\n"); break; }
                V = I * R;
                printf("V = %.4f V\n", V);
                saveToHistory("Ohm's Law: calculated V");
                break;

            case 2: // I
                printf("Enter V (V): ");
                if (scanf("%lf", &V) != 1) { printf("Invalid.\n"); break; }
                printf("Enter R (Ohm): ");
                if (scanf("%lf", &R) != 1) { printf("Invalid.\n"); break; }
                if (R == 0) {
                    printf("Error: R cannot be zero.\n");
                } else {
                    I = V / R;
                    printf("I = %.6f A\n", I);
                    saveToHistory("Ohm's Law: calculated I");
                }
                break;

            case 3: // R
                printf("Enter V (V): ");
                if (scanf("%lf", &V) != 1) { printf("Invalid.\n"); break; }
                printf("Enter I (A): ");
                if (scanf("%lf", &I) != 1) { printf("Invalid.\n"); break; }
                if (I == 0) {
                    printf("Error: I cannot be zero.\n");
                } else {
                    R = V / I;
                    printf("R = %.4f Ohm\n", R);
                    saveToHistory("Ohm's Law: calculated R");
                }
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
}

//Power Calculator

void powerMenu(void) {
    int choice;
    double P, V, I, R;

    while (1) {
        printf("\n--------- Power Calculator ---------\n");
        printf("1. P = V * I\n");
        printf("2. P = I^2 * R\n");
        printf("3. P = V^2 / R\n");
        printf("4. Return to main menu\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            int c; while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        if (choice == 4) {
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter V (V): ");
                if (scanf("%lf", &V) != 1) { printf("Invalid.\n"); break; }
                printf("Enter I (A): ");
                if (scanf("%lf", &I) != 1) { printf("Invalid.\n"); break; }
                P = V * I;
                printf("P = %.4f W\n", P);
                saveToHistory("Power: P = V * I");
                break;

            case 2:
                printf("Enter I (A): ");
                if (scanf("%lf", &I) != 1) { printf("Invalid.\n"); break; }
                printf("Enter R (Ohm): ");
                if (scanf("%lf", &R) != 1) { printf("Invalid.\n"); break; }
                P = I * I * R;
                printf("P = %.4f W\n", P);
                saveToHistory("Power: P = I^2 * R");
                break;

            case 3:
                printf("Enter V (V): ");
                if (scanf("%lf", &V) != 1) { printf("Invalid.\n"); break; }
                printf("Enter R (Ohm): ");
                if (scanf("%lf", &R) != 1) { printf("Invalid.\n"); break; }
                if (R == 0) {
                    printf("Error: R cannot be zero.\n");
                } else {
                    P = (V * V) / R;
                    printf("P = %.4f W\n", P);
                    saveToHistory("Power: P = V^2 / R");
                }
                break;

            default:
                printf("Invalid choice.\n");
        }
    }
}

//Series Resistor Calculator

void seriesResistorMenu(void) {
    int n;
    double resistors[MAX_RESISTORS];
    double result;

    printf("\nHow many resistors in series? ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter a number.\n");
        return;
    }
    if (n <= 0 || n > MAX_RESISTORS) {
        printf("Invalid count. Must be between 1 and %d.\n", MAX_RESISTORS);
        return;
    }

    inputResistors(resistors, n);
    result = calculateSeries(resistors, n);

    printf("Series equivalent resistance: %.4f Ohm\n", result);
    saveToHistory("Series resistance calculated");
}

//Parallel Resistor Calculator

void parallelResistorMenu(void) {
    int n;
    double resistors[MAX_RESISTORS];
    double result;

    printf("\nHow many resistors in parallel? ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter a number.\n");
        return;
    }
    if (n <= 0 || n > MAX_RESISTORS) {
        printf("Invalid n. Must be between 1 and %d.\n", MAX_RESISTORS);
        return;
    }

    inputResistors(resistors, n);
    result = calculateParallel(resistors, n);

    if (result <= 0) {
        printf("Error: no valid resistor values.\n");
    } else {
        printf("Parallel equivalent resistance: %.4f Ohm\n", result);
        saveToHistory("Parallel resistance calculated");
    }
}

//Voltage Divider

void voltageDividerMenu(void) {
    double Vin, R1, R2, Vout;

    printf("\nVoltage Divider Calculator\n");
    printf("Enter Vin (V): ");
    if (scanf("%lf", &Vin) != 1) { printf("Invalid.\n"); return; }

    printf("Enter R1 (Ohm): ");
    if (scanf("%lf", &R1) != 1) { printf("Invalid.\n"); return; }

    printf("Enter R2 (Ohm): ");
    if (scanf("%lf", &R2) != 1) { printf("Invalid.\n"); return; }

    if (R1 + R2 == 0) {
        printf("Error: R1 + R2 cannot be zero.\n");
        return;
    }

    Vout = Vin * (R2 / (R1 + R2));
    printf("Vout = %.4f V\n", Vout);
    saveToHistory("Voltage divider calculated");
}

//Unit Converter  (Ohm / kOhm / MOhm)

void unitConverterMenu(void) {
    double value;
    int choice;

    printf("\nUnit Converter\n");
    printf("1. Ohm  -> kOhm\n");
    printf("2. Ohm  -> MOhm\n");
    printf("3. kOhm -> Ohm\n");
    printf("4. MOhm -> Ohm\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        return;
    }

    printf("Enter value: ");
    if (scanf("%lf", &value) != 1) {
        printf("Invalid value.\n");
        return;
    }

    switch (choice) {
        case 1:
            printf("%.4f Ohm = %.4f kOhm\n", value, value / 1000.0);
            break;
        case 2:
            printf("%.4f Ohm = %.4f MOhm\n", value, value / 1e6);
            break;
        case 3:
            printf("%.4f kOhm = %.4f Ohm\n", value, value * 1000.0);
            break;
        case 4:
            printf("%.4f MOhm = %.4f Ohm\n", value, value * 1e6);
            break;
        default:
            printf("Invalid option.\n");
            return;
    }

    saveToHistory("Unit conversion used");
}

//Input resistor array

static void inputResistors(double *resistors, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("Enter R%d (Ohm): ", i + 1);
        if (scanf("%lf", &resistors[i]) != 1) {
            printf("Invalid input, using 0.\n");
            resistors[i] = 0.0;
        }
    }
}

//Calculate series equivalent

static double calculateSeries(double *resistors, int n) {
    double sum = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        sum += resistors[i];
    }
    return sum;
}

//Calculate parallel equivalent

static double calculateParallel(double *resistors, int n) {
    double reciprocalSum = 0.0;
    int i;
    for (i = 0; i < n; i++) {
        if (resistors[i] <= 0) {
            printf("Warning: R%d <= 0 ignored.\n", i + 1);
            continue;
        }
        reciprocalSum += 1.0 / resistors[i];
    }
    if (reciprocalSum == 0.0) {
        return -1.0;
    }
    return 1.0 / reciprocalSum;
}
