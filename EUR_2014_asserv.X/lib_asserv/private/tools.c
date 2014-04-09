#include "tools.h"

// Renvoyer une valeur comprise entre inf et sup
float limit_float(float valeur, float inf, float sup){
    if (valeur < inf) return inf;
    else if (valeur > sup) return sup;
    else return valeur;
}

long int limit_int(long int valeur, long int inf, long int sup){
    if (valeur < inf) return inf;
    else if (valeur > sup) return sup;
    else return valeur;
}