#include "test.h"

int main() {
    bool rules[NUM_POS][NUM_POS] = {0};
    rule_load(rules, "rules");

    assert(rules[START][DET] == true);
    assert(rules[START][NOUN] == true);
    assert(rules[NOUN][NOUN] == false);
    assert(rules[ADJ][ADJ] == false);
    assert(rules[ADJ][VERB] == false);
    assert(rules[VERB][ADV] == true);

    return 0;
}