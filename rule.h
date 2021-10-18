#ifndef RULE_H
#define RULE_H

#include <stdbool.h>

#include "type.h"

#ifndef NUM_RULES
#define NUM_RULES 128
#endif

/* pathから品詞の規則をロードする */
int rule_load(bool rules[NUM_POS][NUM_POS], const char* path);

#endif
