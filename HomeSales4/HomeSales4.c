#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SALESPERSONS 100

typedef struct {
    char initial;
    double totalSales;
} SalesPerson;

int main() {
    SalesPerson salesPeople[MAX_SALESPERSONS];
    int numSalespersons = 0;
    double grandTotal = 0.0, highestSale = 0.0;
    char topSalesperson = '\0';

    FILE *fpSalespeople = fopen("salespeople.txt", "r");
    if (fpSalespeople == NULL) {
        perror("Error opening salespeople.txt");
        return 1;
    }

    while (fscanf(fpSalespeople, " %c", &salesPeople[numSalespersons].initial) == 1) {
        salesPeople[numSalespersons].initial = toupper(salesPeople[numSalespersons].initial);
        salesPeople[numSalespersons].totalSales = 0.0;
        numSalespersons++;
    }
    fclose(fpSalespeople);

    FILE *fpSales = fopen("sales.txt", "r");
    if (fpSales == NULL) {
        perror("Error opening sales.txt");
        return 1;
    }

    char inputInitial;
    double sale;
    while (fscanf(fpSales, " %c", &inputInitial) == 1) {
        inputInitial = toupper(inputInitial);

        if (inputInitial == 'Z') {
            break;
        }

        if (fscanf(fpSales, " %lf", &sale) != 1) {
            printf("Error: expected sale amount after %c\n", inputInitial);
            continue;
        }

        int found = 0;
        for (int i = 0; i < numSalespersons; i++) {
            if (salesPeople[i].initial == inputInitial) {
                found = 1;
                if (sale < 0) {
                    printf("Error: sale amount must be positive for %c\n", inputInitial);
                    break;
                }

                salesPeople[i].totalSales += sale;
                grandTotal += sale;

                if (salesPeople[i].totalSales > highestSale) {
                    highestSale = salesPeople[i].totalSales;
                    topSalesperson = salesPeople[i].initial;
                }
                break;
            }
        }

        if (!found) {
            printf("Error, invalid salesperson selected, please try again\n");
        }
    }

    fclose(fpSales);

    printf("\nGrand Total: $%.0f\n", grandTotal);
    if (topSalesperson != '\0') {
        printf("Highest Sale: %c\n", topSalesperson);
    } else {
        printf("No sales recorded.\n");
    }

    return 0;
}
