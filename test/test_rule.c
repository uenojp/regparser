#include "test.h"

int main() {
    load_rule("./asset/rules");

    assert(has_rule(START, DET) == true);
    assert(has_rule(START, NOUN) == true);
    assert(has_rule(NOUN, NOUN) == false);
    assert(has_rule(ADJ, ADJ) == false);
    assert(has_rule(ADJ, VERB) == false);
    assert(has_rule(VERB, ADV) == true);

    return 0;
}