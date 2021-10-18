#include "test.h"

int main(int argc, char** argv) {
    dict_t* dict;

    dict_load(&dict, "dictionary");

    PartOfSpeech pos;
    char* recieved;

    pos = get_part_of_speech(dict, "child");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "NOUN"));

    pos = get_part_of_speech(dict, "the");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "DET"));

    pos = get_part_of_speech(dict, "foo");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "UNKNOWN"));

    dict_free(dict);

    return 0;
}