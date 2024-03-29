﻿#include "Kaszas.h"
#include "Billentyu.h"
#include "Common.h"
#include "Nyomtato.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int program(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Do be so kind as to specify the maximum width for the printer to use! Eg. "
               "'./%s 50'\n",
               argv[0]);
        return 1;
    }

    char* endptr;
    long int number = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0') {
        fprintf(stderr, "The sepcified parameter is not a correct integer!\n");
        return 1;
    } else if (number < 10) {
        fprintf(
            stderr,
            "The specified width is not wide enough. It should be at least 10 characters long!\n");
        return 1;
    }

    int maxWidth = number > INT_MAX ? INT_MAX : (int)number;
    printf("The specified maximum width: %d\n\n", maxWidth);

    print_greeting();

    int nyugtaCount = 1;
    BEOLVASAS_ALLAPOT allapot = NEV;
#ifdef DEBUG
    printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif

    // Main loop. No exit condition, because we want to run foreveeeeeeeeer.
    for (;;) {
        NYUGTA nyugta;
        nyugta.sorszam = nyugtaCount;
        nyugta.tetelCount = 0;
        nyugta.tetelek = NULL;
        nyugta.osszesites = 0;

        PSZ_TETEL* tetel = malloc(sizeof(PSZ_TETEL));
        tetel->f_nev = NULL;
        tetel->f_db = 0;
        tetel->f_ar = 0;

#ifdef DEBUG
        printf("DEBUG: NYUGTA LETREHOZVA SORSZAM: %d\n", nyugta.sorszam);
#endif

        while (allapot != KOVETKEZO) {
            switch (allapot) {
            default:
                fprintf(stderr, "Hiba történt beolvasás közben, elérhetetlen "
                                "kódrészlet!\n");
                return 1;
            case NEV:
                printf("Enter the name of the item:\n");

                // Remove the old name if it exists
                if (tetel->f_nev != NULL) {
                    free(tetel->f_nev);
                }

                tetel->f_nev = read_tetel_nev();
                allapot = DB;
#ifdef DEBUG
                printf("DEBUG: TETEL NEV: %s\n", tetel->f_nev);
                printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                break;
            case DB:
                printf("Enter the quantity of the item:\n");
                tetel->f_db = read_tetel_num();
                allapot = AR;
#ifdef DEBUG
                printf("DEBUG: TETEL DB: %d\n", tetel->f_db);
                printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                break;
            case AR:
                printf("Enter the price of the item:\n");
                tetel->f_ar = read_tetel_num();
                allapot = MENTES;
#ifdef DEBUG
                printf("DEBUG: TETEL AR: %ld\n", tetel->f_ar);
                printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                break;
            case MENTES:
                print_save_prompt(tetel);

                if (input_should_save()) {
                    add_tetel_to_nyugta(&nyugta, tetel);

                    // create new
                    tetel = malloc(sizeof(PSZ_TETEL));
                    tetel->f_nev = NULL;
                    tetel->f_db = 0;
                    tetel->f_ar = 0;
                } else {
                    free(tetel->f_nev);
                }

                nyugta.osszesites =
                    calculate_osszesites(nyugta.tetelek, nyugta.tetelCount);

#ifdef DEBUG
                printf("DEBUG: NEW OSSZITES: %ld\n", nyugta.osszesites);
#endif

                allapot = ATMENET;
#ifdef DEBUG
                printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
            case ATMENET:
                print_next_action();

                char inputAtmenetChar = '?';
                int tries = 0;
                while (inputAtmenetChar != '1' && inputAtmenetChar != '2' &&
                       inputAtmenetChar != '3' && inputAtmenetChar != '4') {
                    if (tries++ > 0) {
                        printf("Please choose one of the above numbers!\n");
#ifdef DEBUG
                        printf("DEBUG: INVALID MENU INPUT!");
#endif
                    }
                    inputAtmenetChar = read_char();
                }
#ifdef DEBUG
                printf("DEBUG: MENU INPUT VALUE: %c\n", inputAtmenetChar);
#endif

                if (inputAtmenetChar == '1') {
                    allapot = NEV;
#ifdef DEBUG
                    printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                    break;
                } else if (inputAtmenetChar == '2') {
                    print_nyugta(maxWidth, &nyugta);
                    allapot = ATMENET;
#ifdef DEBUG
                    printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                    break;
                } else if (inputAtmenetChar == '3') {
                    allapot = KOVETKEZO;
#ifdef DEBUG
                    printf("DEBUG: ALLAPOT: %d\n", allapot);
#endif
                    break;
                } else {
                    print_goodbye();
#ifdef DEBUG
                    printf("DEBUG: EXITING");
#endif
                    free_nyugta_members(&nyugta);
                    free(tetel);
                    return 0;
                }
            }
        }

        // #freenyugta
        nyugtaCount++;
        allapot = NEV;
        free_nyugta_members(&nyugta);
        free(tetel);
#ifdef DEBUG
        printf("DEBUG: ALLAPOT: %d\n", allapot);
        printf("DEBUG: FREEING OLD NYUGTA");
#endif
    }
}

static void print_greeting() {
    printf(
      "Good day to you, fine sir/madam! \nWelcome to our trusty transaction "
      "contraption. \nKindly brace yourself for an experience smoother than "
      "a well-aged cup of Yorkshire tea. \nSo, how may we assist you today? "
      "\nNeed a pound or two for the trolley? \nOr mayhaps you're here for a "
      "robust rendezvous with your account details? \nFear not, this humble "
      "machine is at your service, ready to assist faster than a fox running "
      "late for tea. \nMind the buttons now, they're a bit ticklish!\n\n");
}

static void print_save_prompt(PSZ_TETEL* tetel) {
    printf("Name of the item: %s\n", tetel->f_nev);
    printf("Quantity: %d\n", tetel->f_db);
    printf("Price: %ld\n", tetel->f_ar);
    printf("Please check the above data and choose "
           "what to do next!\n");
    printf("Would you like to save the data? (y/N)\n");
}

static int input_should_save() {
    char inputSaveChar = '?';
    int tries = 0;
    while (inputSaveChar != 'y' && inputSaveChar != 'N') {
        if (tries++ > 0) {
            printf("Enter either y or N!\n");
#ifdef DEBUG
            printf("DEBUG: SAVE INPUT INVALID VALUE!\n");
#endif
        }
        inputSaveChar = read_char();
    }

#ifdef DEBUG
    printf("DEBUG: SAVE INPUT VALUE: %c\n", inputSaveChar);
#endif

    return inputSaveChar == 'y';
}

static void print_next_action() {
    printf("--------------------\n");
    printf("What would you like to do next?\n");
    printf("1. Add new item\n");
    printf("2. Print \n");
    printf("3. New\n");
    printf("4. Exit\n");
}

static void print_goodbye() {
    printf(
      "\n\nWell, there we are then. \nJob done and dusted, "
      "smoother than a fresh jar of Marmite, wouldn't you "
      "say? \nThank you kindly for using our services. "
      "\nWe've been more chuffed than a bobby with a fresh "
      "truncheon to assist you today. \nRemember, next time "
      "you're in a pickle, or simply need a quid or two, our "
      "trusty machine will be right here waiting. \nJust "
      "don't forget to pop by and say 'ello! \nCheerio now, "
      "and off you trot. \nMind the gap and keep calm and "
      "carry on, as they say!\n");
}
