#ifndef TYPE_H
#define TYPE_H

typedef enum {
    UNKNOWN,
    START,
    DET,
    NOUN,
    ADJ,
    PREP,
    ADV,
    VERB,
    END,
} PartOfSpeech;

#define WORD_LEN 128
#define POS_LEN 16
#define NUM_POS 9

char* to_string(PartOfSpeech pos);

PartOfSpeech to_enum(char* pos);

#endif
