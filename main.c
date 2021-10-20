#include "regparser.h"

int main() {
    const char sentence[] = "the child runs quickly to large house.";

    if (load_dict("./asset/dictionary") != 0)
        return 1;
    if (load_rule("./asset/rules") != 0)
        return 1;
    if (parse(sentence) != 0)
        return 1;

    return 0;
}
