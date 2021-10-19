#include "regparser.h"

int rule_load(bool rules[NUM_POS][NUM_POS], const char* path) {
    if (rules == NULL) {
        fprintf(stderr, "rule_load: null error\n");
        return 1;
    }

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

    return 0;
}
