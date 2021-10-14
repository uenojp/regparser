#include "type.h"

#include <string.h>

char* to_string(PartOfSpeech pos) {
    switch (pos) {
        case START: return "START";
        case DET:   return "DET";
        case NOUN:  return "NOUN";
        case ADJ:   return "ADJ";
        case PREP:  return "PREP";
        case ADV:   return "ADV";
        case VERB:  return "VERB";
        case END:   return "END";
        default:    return "UNKNOWN";
    }
}

PartOfSpeech to_enum(char* pos) {
    if (strcmp(pos, "START") == 0) return START;
    if (strcmp(pos, "DET"  ) == 0) return DET;
    if (strcmp(pos, "NOUN" ) == 0) return NOUN;
    if (strcmp(pos, "ADJ"  ) == 0) return ADJ;
    if (strcmp(pos, "PREP" ) == 0) return PREP;
    if (strcmp(pos, "ADV"  ) == 0) return ADV;
    if (strcmp(pos, "VERB" ) == 0) return VERB;
    if (strcmp(pos, "END"  ) == 0) return END;
    return UNKNOWN;
}
