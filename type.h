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

typedef struct {
    char* word;
    PartOfSpeech pos;
} WordPos;


char* to_string(PartOfSpeech pos);

PartOfSpeech to_enum(char* pos);

#endif
