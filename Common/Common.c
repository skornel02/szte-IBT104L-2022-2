#include "Common.h"
#include <stdlib.h>

long int calculate_osszesites(PSZ_TETEL** tetelek, int tetelCount)
{
  long int sum = 0;

  for (int i = 0; i < tetelCount; i++) {
    sum += tetelek[i]->f_ar;
  }

  return sum;
}

void free_nyugta_members(NYUGTA *nyugta) {
    for (int i = 0; i < nyugta->tetelCount; i++) {
        free(nyugta->tetelek[i]->f_nev);
        free(nyugta->tetelek[i]);
    }
    free(nyugta->tetelek);
}

void add_tetel_to_nyugta(NYUGTA* nyugta, PSZ_TETEL* tetel) {
    int currentAmount = nyugta->tetelCount;
    unsigned long int newSize = sizeof(PSZ_TETEL*) * (currentAmount + 1);
    nyugta->tetelek = realloc(nyugta->tetelek, newSize);
    nyugta->tetelek[nyugta->tetelCount] = tetel;
    nyugta->tetelCount++;
}