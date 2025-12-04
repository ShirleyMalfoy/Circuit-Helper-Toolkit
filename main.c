#include <stdio.h>
#include <stdlib.h>      // 为了 exit()
#include "calculations.h"
#include "history.h"

int main(void) {
    int choice;

    while (1) {
        printf("\n==============================\n");
        printf("       Circuit Helper Toolkit\n");
        printf("==============================\n");
        printf("1. Ohm's Law Calculator\n");
        printf("2. Power Calculator\n");
        printf("3. Series Resistor Calculator\n");
        printf("4. Parallel Resistor Calculator\n");
        printf("5. Voltage Divider Calculator\n");
        printf("6. Unit Converter (Ohm/kOhm/MOhm)\n");
        printf("7. View Calculation History\n");
        printf("8. Exit\n");
        printf("==============================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            return 0;
        }

        switch (choice) {
            case 1: ohmsLawMenu();        break;
            case 2: powerMenu();          break;
            case 3: seriesResistorMenu(); break;
            case 4: parallelResistorMenu(); break;
            case 5: voltageDividerMenu(); break;
            case 6: unitConverterMenu();  break;
            case 7: viewHistory();        break;
            case 8:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Please enter a number from 1 to 8.\n");
        }
    }
}
