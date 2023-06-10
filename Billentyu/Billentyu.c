#include "Billentyu.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char read_char() {
    char c;
    scanf(" %c", &c);
    getchar();
    return c;
}

char* read_tetel_nev() {
    Array array = create_array(10);

    char input;
    int lastNum = 0;

    while ((input = read_char()) != 'x' || (input == 'x' && array.size == -1)) {
        if (input == 'x'  && array.size == -1) {
            printf("The name cannot be empty!\n");
            continue;
        }

        if (!is_correct_input(input)) {
            printf("Blimey! It seems we may have received a faulty input: %c - kindly try one of the inputs indicated on the screen!\n", input);
            continue;
        }

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

    char* tetelNev = array.size >= 0 ? join_tetel_nev(&array) : "";

    return tetelNev;
}

int read_tetel_num() {
    int tetel_db = 0;

    int ok;
    do {
        tetel_db = scan_num();
        ok = check_num(tetel_db);
    } while (!ok);

    return tetel_db;
}

Array create_array(int size) {
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
    if (array->free == 0) {
        Array *tmp = malloc(array->size * sizeof(CONTAINER));
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

int is_correct_input(char input) {
    return input >= '1' && input <= '9';
}

long int scan_num() {
    char digits[10];

    scanf("%9s", digits);

    // Be nem olvasott karakterek eltakarítása stdin-ről
    int x;
    while((x = getchar()))
    {
        if(x == '\n')
        {
            break;
        }
    }

    // Csak akkor fogadja el az inputot, nincs az elején se szöveg
    int firstDigitIndex = -1;
    for (int i = 0; i < 9; ++i) {
        if (digits[i] >= '0' && digits[i] <= '9') {
            firstDigitIndex = i;
            break;
        }
    }

    if (firstDigitIndex == -1 || firstDigitIndex > 0) {
        return 0;
    }

    // Lapátoljunk össze egy számot a számjegyek alapján
    int digitCount = 0;
    for (int i = 0; i < 9; ++i) {
        if (digits[i] >= '0' && digits[i] <= '9') {
            digitCount++;
        }
    }

    char real[digitCount+1];
    for (int i = 0; i < digitCount; ++i) {
        real[i] = digits[i];
    }
    real[digitCount] = '\0';

    char *ptr;

    return strtol(real, &ptr, 10);
}

int check_num(long int input) {
    if (input <= 0) {
        printf("We seem to be in a slight pickle here. The number kindly provided by You must be at least 1!\n");
        return 0;
    }

    return 1;
}