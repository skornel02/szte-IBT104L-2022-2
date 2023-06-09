#include "Common.h"
#include <stdlib.h>

OSSZESITES *calculate_osszesites(PSZ_TETEL** tetelek, int tetelCount)
{
  OSSZESITES* osszesites = malloc(sizeof(OSSZESITES));
  osszesites->f_ar = 0;

  for (int i = 0; i < tetelCount; i++) {
    osszesites->f_ar += tetelek[i]->f_ar;
  }

  return osszesites;
}

void free_nyugta_members(NYUGTA *nyugta) {
    for (int i = 0; i < nyugta->tetelCount; i++) {
        free(nyugta->tetelek[i]->f_nev);
        free(nyugta->tetelek[i]);
    }
    if (nyugta->osszesites != NULL) {
      free(nyugta->osszesites);
    }
    free(nyugta->tetelek);
}

void add_tetel_to_nyugta(NYUGTA* nyugta, PSZ_TETEL* tetel) {
    int currentAmount = nyugta->tetelCount;
    int newSize = sizeof(PSZ_TETEL*) * (currentAmount + 1);
    nyugta->tetelek = realloc(nyugta->tetelek, newSize);
    nyugta->tetelek[nyugta->tetelCount] = tetel;
    nyugta->tetelCount++;
}