#include "Billentyu.h"
#include <stdio.h>
#include <stdlib.h>

char read_char() {
    char c;
    scanf(" %c", &c);
    getchar();
    return c;
}

char* read_tetel_nev() {
    // Ebben van tárolva az összes input
    Array array = create_array(3);

    char input;
    int lastNum = 0;

    // Addig olvassa a karaktereket, amíg nem kap továbbot
    while ((input = read_char()) != 'x') {
        /*if (!is_correct_input(input)) {
            printf("Blimey!");
            continue;
        }*/

        grow_array(&array);
        check_array(&array, input - '0', lastNum);

        unsigned int numLength = array.items[array.size].numLength;
        array.items[array.size].numbers[numLength] = input - '0';
        lastNum = input - '0';

        int firstNum = array.items[array.size].numbers[0];
        int numCount = 0;
        for (int i = 0; i < 4; ++i) {
            if (array.items[array.size].numbers[i] == firstNum) {
                numCount++;
            } else {
                break;
            }
        }

        array.items[array.size].character = map_number_to_char(firstNum, numCount);
        array.items[array.size].numLength++;

        // TODO: Kiírni a beolvasott összes számot
        // TODO: Kiírni az átváltott összes karaktert
    }

    return join_tetel_nev(&array);
}

int read_tetel_db() {
    int tetel_db;
    printf("Kerem adja meg a tetel darabszamat:\n");
    scanf("%d", &tetel_db);
    return tetel_db;
}

long int read_tetel_ar() {
    long int tetel_ar;
    printf("Kerem adja meg a tetel arat:\n");
    scanf("%ld", &tetel_ar);
    return tetel_ar;
}

Array create_array(unsigned int size) {
    Array array;
    array.items = malloc(size * sizeof(CONTAINER));
    array.size = -1;
    array.free = size;

    return array;
}

char map_number_to_char(unsigned short number, unsigned short shift) {
    char map[10][4] = {
            {' '},
            {'a', 'b', 'c'},
            {'d', 'e', 'f'},
            {'g', 'h', 'i'},
            {'j', 'k', 'l'},
            {'m', 'n', 'o'},
            {'p', 'q', 'r', 's'},
            {'t', 'u', 'v'},
            {'w', 'x', 'y', 'z'},
    };
    char actualChar = map[number-1][shift-1];

    return actualChar;
}

void check_array(Array *array, int input, int lastNum) {
    int isThreeDigits =  ((input >= 1 && input <= 6) || (input == 8)) && array->items[array->size].numLength == 3;
    int isFourDigits = (input == 7 || input == 9) && array->items[array->size].numLength == 4;

    if (input != lastNum || isThreeDigits  || isFourDigits) {
        array->size++;
        array->free--;
    }
}

void grow_array(Array* array) {
    // Tömb növelése, ha nincs már hely
    if (array->free == 0) {
        Array *tmp = malloc(array->size * sizeof(CONTAINER));;
        tmp->items = realloc(array->items, (array->size * 2) * sizeof(CONTAINER));
        if (tmp == NULL) {
            printf("Blimey! Something went horribly wrong!");
            free(tmp);
            free(array);
            exit(-1);
        } else {
            array = tmp;
            array->free = array->size * 2;
            tmp = NULL;
        }
    }
}

char* join_tetel_nev(Array* array) {
    char* tetel_nev = malloc((array->size * sizeof(char)));

    for (int i = 0; i < array->size + 1; ++i) {
        tetel_nev[i] = array->items[i].character;
        printf("%c", tetel_nev[i]);
    }

    tetel_nev[array->size + 1] = '\0';

    return tetel_nev;
}

int is_correct_input(int input) {
    return input < '0' || input > '9';
}