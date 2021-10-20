#ifndef RULE_H
#define RULE_H

#include <stdbool.h>

#include "dict.h"
#include "type.h"

#ifndef NUM_RULES
#define NUM_RULES 128
#endif

/* pathから品詞の規則をロードする */
int load_rule(const char* path);

bool has_rule(const PartOfSpeech state, const PartOfSpeech pos);

#endif
