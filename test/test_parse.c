#include "test.h"

int main(int argc, char **argv) {
    load_dict("./asset/dictionary");
    load_rule("./asset/rules");

    /* transit */
    assert(transit(START, ".") == END);
    assert(transit(DET, "child") == NOUN);
    assert(transit(NOUN, "to") == PREP);
    assert(transit(ADV, "house") == NOUN);

    assert(transit(ADV, "the") == UNKNOWN);
    assert(transit(VERB, "large") == UNKNOWN);
    assert(transit(START, "large") == UNKNOWN);

    /* is_sentence */
    assert(is_sentence("Hi there.") == true);
    assert(is_sentence("Unix never says please.") == true);
    assert(is_sentence("no period sentence") == true);

    assert(is_sentence("") == false);
    assert(is_sentence(".") == false);

    return 0;
}