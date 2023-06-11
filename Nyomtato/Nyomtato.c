#include "Nyomtato.h"
#include "Common.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void print_nyugta(int maxWidth, NYUGTA* nyugta) {
    char filename[30];
    sprintf(filename, "%d.txt", nyugta->sorszam);

    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    print_title(fp, maxWidth, nyugta->sorszam);
    print_separator(fp, maxWidth);
    print_tetelek(fp, maxWidth, nyugta->tetelCount, nyugta->tetelek);
    print_total(fp, maxWidth, nyugta->osszesites);
    print_separator(fp, maxWidth);

    fclose(fp);

    printf("%s %s\n","Receipt printed:", filename);
}

static void print_title(FILE* fp, int maxWidth, int sorszam) {
    int sorszam_length = getNumbersLength(sorszam);
    int padding = (maxWidth - sorszam_length) / 2;
    PAD_FILE(fp, padding)
    fprintf(fp, "%d", sorszam);
    int remaining_padding = maxWidth - padding - sorszam_length;
    PAD_FILE(fp, remaining_padding)
    fprintf(fp, "|\n");
}

static void print_separator(FILE* fp, int maxWidth) {
    PAD_FILE_WITH_CHAR(fp, maxWidth, '-')
    fprintf(fp, "|\n");
}

static void print_tetelek(FILE* fp, int maxWidth, int tetelAmount,
                          PSZ_TETEL** tetelek) {
    for (int tetelIndex = 0; tetelIndex < tetelAmount; tetelIndex++) {
        char* item_name = tetelek[tetelIndex]->f_nev;
        int item_quantity = tetelek[tetelIndex]->f_db;
        long int item_price = tetelek[tetelIndex]->f_ar;

        int item_name_length = strlen(item_name);
        int item_quantity_length = getNumbersLength(item_quantity);
        int item_price_length = getNumbersLength(item_price) + 3;

        char* item_price_text = malloc((item_price_length + 1) * sizeof(char));
        sprintf(item_price_text, "%ld Ft", item_price);

        int item_name_and_quantity_length =
            item_name_length + item_quantity_length + 5;
        char* item_name_and_quantity =
            malloc((item_name_and_quantity_length + 1) * sizeof(char));
        sprintf(item_name_and_quantity, "%s %d DB ", item_name, item_quantity);

        // Print the item name
        for (unsigned long j = 0; j < item_name_and_quantity_length; j++) {
            if (j != 0 && j % maxWidth == 0) {
                fprintf(fp, "|\n");
            }
            fprintf(fp, "%c", item_name_and_quantity[j]);
        }

        free(item_name_and_quantity);

        int space_remaining =
            maxWidth - (item_name_and_quantity_length % maxWidth);
        if (space_remaining == maxWidth) {
            fprintf(fp, "|\n");
        }

        if (space_remaining < item_price_length) {
            PAD_FILE(fp, space_remaining)
            fprintf(fp, "|\n");

            int padding = (maxWidth - item_price_length);
            PAD_FILE(fp, padding)
            fprintf(fp, "%s|\n", item_price_text);
        } else {
            int padding = (space_remaining - item_price_length);
            PAD_FILE(fp, padding)
            fprintf(fp, "%s|\n", item_price_text);
        }

        free(item_price_text);
    }
}

void print_total(FILE* fp, int maxWidth, long int osszesites) {
    int total_length = getNumbersLength(osszesites) + 3;
    int padding = (maxWidth - total_length);
    int middle_padding = padding - 6;

    PAD_FILE(fp, padding)
    PAD_FILE_WITH_CHAR(fp, total_length, '-')
    fprintf(fp, "|\n");

    fprintf(fp, "Total:");
    PAD_FILE(fp, middle_padding)
    fprintf(fp, "%ld Ft|\n", osszesites);
}

int getNumbersLength(long int number) {
    int length = 0;
    if (number == 0)
        length = 1;
    else {
        if (number < 0)
            number = -number;
        while (number > 0) {
            length++;
            number /= 10;
        }
    }
    return length;
}
