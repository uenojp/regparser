#include "regparser.h"

static bool rules[NUM_POS][NUM_POS];
static bool loaded = false; /*規則がファイルから読み込まれたらtrueへ*/

int load_rule(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        perror("rule_load: fopen");
        return 1;
    }

    char from[POS_LEN];
    char to[POS_LEN];
    int nscan;
    while ((nscan = fscanf(file, "%16s %16s", from, to)) != EOF) {
        // printf("from: %s to: %s\n", from, to);
        rules[to_enum(from)][to_enum(to)] = true;
    }

    loaded = true;

    return 0;
}

bool has_rule(const PartOfSpeech state, const PartOfSpeech pos) {
    if (!loaded) {
        fprintf(stderr, "haven't loaded rules\n");
        return false;
    }
    return rules[state][pos];
}
