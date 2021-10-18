#include "regparser.h"

int main() {
    const char sentence[] = "the child runs quickly to large house.";

    parser_t* parser;
    if (parser_init(&parser, "dictionary", "rules") != 0) {
        return 1;
    }
    parser_parse(parser, sentence);
    parser_free(parser);

    return 0;
}
