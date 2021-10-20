#include "test.h"

int main(int argc, char **argv) {
    load_dict("./asset/dictionary");
    load_rule("./asset/rules");

    assert(transit(START, ".") == END);
    assert(transit(DET, "child") == NOUN);
    assert(transit(NOUN, "to") == PREP);
    assert(transit(ADV, "house") == NOUN);

    assert(transit(ADV, "the") == UNKNOWN);
    assert(transit(VERB, "large") == UNKNOWN);
    assert(transit(START, "large") == UNKNOWN);

    return 0;
}