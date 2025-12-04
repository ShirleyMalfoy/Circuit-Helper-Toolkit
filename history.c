#include <stdio.h>
#include "history.h"

void saveToHistory(const char *entry) {
    FILE *f = fopen("history.txt", "a");
    if (!f) {
        printf("Could not open history.txt for writing.\n");
        return;
    }
    fprintf(f, "%s\n", entry);
    fclose(f);
}

void viewHistory(void) {
    FILE *f = fopen("history.txt", "r");
    if (!f) {
        printf("No history found yet.\n");
        return;
    }

    printf("\n---- Calculation History ----\n");

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }

    fclose(f);
}
