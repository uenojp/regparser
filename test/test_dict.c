#include "test.h"

int main(int argc, char** argv) {
    load_dict("./asset/dictionary");

    PartOfSpeech pos;
    char* recieved;

    pos = get_part_of_speech("child");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "NOUN"));

    pos = get_part_of_speech("the");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "DET"));

    pos = get_part_of_speech("foo");
    recieved = to_string(pos);
    assert(!strcmp(recieved, "UNKNOWN"));

    return 0;
}