#include "Billentyu.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

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

    print_keyboard();
    while ((input = read_char()) != 'x' || (input == 'x' && array.size == 0)) {
        if (input == 'x'  && array.size == 0) {
            printf("The name cannot be empty!\n");
            continue;
        }

        if (!is_correct_input(input)) {
            printf("Blimey! It seems we may have received a faulty input: %c - kindly try one of the inputs indicated on the screen!\n", input);
            continue;
        }

        check_array(&array, input - '0', lastNum);
        grow_array(&array);

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

        clrscr();
        print_keyboard();
        print_numbers(&array);
        print_characters(&array);
    }

    char* tetelNev = array.size >= 0 ? join_tetel_nev(&array) : "";

    free_array(&array);

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

    initialize_array(&array, 0, size);
    array.size = 0;
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

    if (input != lastNum || isThreeDigits  || isFourDigits || input == 1) {
        array->size++;
        array->free--;
    }
}

void grow_array(Array* array) {
    if (array->free == 0) {
        int newSize = (array->size + 1) * 2;
        array->items = realloc(array->items, newSize * sizeof(CONTAINER));
        array->free = array->size * 2;

        initialize_array(array, array->size, newSize);
    }
}

char* join_tetel_nev(Array* array) {
    char* tetel_nev = malloc(((array->size + 1) * sizeof(char)));

    // Tétel név inicializálása, legyen benne valami
    for (int i = 0; i < array->size+1; ++i) {
        tetel_nev[i] = '\0';
    }

    for (int i = 1; i < array->size + 1; ++i) {
        tetel_nev[i-1] = array->items[i].character;
    }

    return tetel_nev;
}

int is_correct_input(char input) {
    return input >= '1' && input <= '9';
}

long int scan_num() {
    char digits[10];

    for (int i = 0; i < 10; ++i) {
        digits[i] = '\0';
    }

    if (scanf("%9s", digits) != 1) {
        return 0;
    }

    // Be nem olvasott karakterek eltakarítása stdin-ről
    int x;
    while((x = getchar()))
    {
        if(x == '\n')
        {
            break;
        }
    }

    // Csak akkor fogadja el az inputot, ha nincs az elején se szöveg
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

void print_numbers(Array *array) {
    for (int i = 0; i < array->size + 1; ++i) {
        for (int j = 0; j < array->items[i].numLength; ++j) {
            printf("%d", array->items[i].numbers[j]);
        }
    }
    printf("\n");
}

void print_characters(Array *array) {
    for (int i = 0; i < array->size + 1; ++i) {
        printf("%c", array->items[i].character);
    }
    printf("\n");
}

void print_keyboard() {
    printf(",------,,------,,------,\n"
           "|  ~1  ||  ~2  ||  ~3  |\n"
           "| ~spc || ~abc || ~def |\n"
           "'------''------''------'\n"
           ",------,,------,,------,\n"
           "|  ~4  ||  ~5  ||  ~6  |\n"
           "| ~ghi || ~jkl || ~mno |\n"
           "'------''------''------'\n"
           ",------,,------,,------,\n"
           "|  ~7  ||  ~8  ||  ~9  |\n"
           "| pqrs || ~tuv || wxyz |\n"
           "'------''------''------'\n"
           "        ,------,\n"
           "        |  ~0  |\n"
           "        | done |\n"
           "        '------'\n");
}

void free_array(Array *array) {
    free(array->items);
}

void initialize_array(Array *array, int start, int end) {
    for (int i = start; i < end; ++i) {
        array->items[i].numLength = 0;
        array->items[i].character = '\0';
        for (int j = 0; j < 4; ++j) {
            array->items[i].numbers[j] = 0;
        }
    }
}