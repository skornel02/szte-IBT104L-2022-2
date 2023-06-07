#include "CommonTypes.h"
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void print_char(char c) { printf("%c", c); };

static void print_title(FILE* fp, int maxWidth, int sorszam);
static void print_separator(FILE* fp, int maxWidth);
static void print_tetelek(FILE* fp, int maxWidth, int tetelAmount,
                          PSZ_TETEL** tetelek);
static void print_total(FILE* fp, int maxWidth, OSSZESITES* osszesites);
int getNumbersLength(long int number);

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
}

static void print_title(FILE* fp, int maxWidth, int sorszam) {
    int sorszam_length = getNumbersLength(sorszam);
    int padding = (maxWidth - sorszam_length) / 2;
    for (int i = 0; i < padding; i++) {
        fprintf(fp, " ");
    }
    fprintf(fp, "%d", sorszam);
    int remaining_padding = maxWidth - padding - sorszam_length;
    for (int i = 0; i < remaining_padding; i++) {
        fprintf(fp, " ");
    }
    fprintf(fp, "|\n");
}

static void print_separator(FILE* fp, int maxWidth) {
    for (int i = 0; i < maxWidth; i++) {
        fprintf(fp, "-");
    }
    fprintf(fp, "|\n");
}

static void print_tetelek(FILE* fp, int maxWidth, int tetelAmount,
                          PSZ_TETEL** tetelek) {
    for (int i = 0; i < tetelAmount; i++) {
        char* item_name = tetelek[i]->f_nev;
        int item_quantity = tetelek[i]->f_db;
        long int item_price = tetelek[i]->f_ar;

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
            for (int j = 0; j < space_remaining; j++) {
                fprintf(fp, " ");
            }
            fprintf(fp, "|\n");

            int padding = (maxWidth - item_price_length);
            for (int j = 0; j < padding; j++) {
                fprintf(fp, " ");
            }
            fprintf(fp, "%s|\n", item_price_text);
        } else {
            int padding = (space_remaining - item_price_length);
            for (int j = 0; j < padding; j++) {
                fprintf(fp, " ");
            }
            fprintf(fp, "%s|\n", item_price_text);
        }

        free(item_price_text);
    }
}

void print_total(FILE* fp, int maxWidth, OSSZESITES* osszesites) {
    int total_length = getNumbersLength(osszesites->f_ar) + 3;
    int padding = (maxWidth - total_length);
    int middle_padding = padding - 6;

    for (int i = 0; i < padding; i++) {
        fprintf(fp, " ");
    }
    for (int i = 0; i < total_length; i++) {
        fprintf(fp, "-");
    }
    fprintf(fp, "|\n");

    fprintf(fp, "Total:");
    for (int i = 0; i < middle_padding; i++) {
        fprintf(fp, " ");
    }
    fprintf(fp, "%ld Ft|\n", osszesites->f_ar);
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
