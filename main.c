#include <stdio.h>
#include <string.h>

#include "type.h"
#include "parser.h"

int main() {
    PartOfSpeech state = START;
    char* sentence[] = {"the", "child", "runs", "quickly", "to", "large", "house", "."};
    for (int i = 0; i < 7; i++) {
        state = transit(state, sentence[i]);
        printf("%-9s   %s\n", sentence[i], to_string(state));
    }

    return 0;
}
