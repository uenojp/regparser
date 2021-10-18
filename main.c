#include "regparser.h"

int main() {
    const char sentence[] = "the child runs quickly to large house.";

    parser_t* parser;
    parser_init(&parser, "dictionary", "rules");
    parser_parse(parser, sentence);
    parser_free(parser);

    return 0;
}
