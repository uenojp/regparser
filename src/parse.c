#include "regparser.h"

int parse(const char* sentence) {
    if (!is_sentence(sentence))
        return 1;

    /* +1+1 は\0とスペース挿入用 */
    char* copy = (char*)malloc((strlen(sentence) + 1 + 1) * sizeof(char));
    if (copy == NULL) {
        perror("perse: malloc");
        return 1;
    }
    strcpy(copy, sentence);

    /* 文末のピリオドの前にスペースを挿入する
     * "abc xyz." => "abc xyz ."
     */
    const size_t len = strlen(copy);
    if (copy[len - 1] == '.') {
        copy[len - 1] = ' ';
        copy[len] = '.';
        copy[len + 1] = '\0';
    }

    PartOfSpeech pos = START;

    char* token = strtok(copy, " ");
    pos = transit(pos, token);
    if (pos == UNKNOWN)
        return 1;
    printf("(%s, %s)\n", token, to_string(pos));
    while ((token = strtok(NULL, " ")) != NULL) {
        pos = transit(pos, token);
        printf("(%s, %s)\n", to_string(pos), token);
    }

    free(copy);

    return 0;
}

/* 現在の状態 state と単語 word を受け取り、遷移先を返す
   (state, word) -> state */
PartOfSpeech transit(const PartOfSpeech state, const char* word) {
    if (strcmp(word, ".") == 0) {
        return END;
    }

    PartOfSpeech pos = get_part_of_speech(word);
    if (pos == UNKNOWN) {
        fprintf(stderr, "%s is not resisterd in dictionary\n", word);
        return UNKNOWN;
    }

    if (has_rule(state, pos)) {
        return pos;
    } else {
        fprintf(stderr, "no rule from %s to %s\n", to_string(state), to_string(pos));
        return UNKNOWN;
    }
}

/* strが文であるか確認する
   ここで "文 \in [A-Za-z ]+\. */
bool is_sentence(const char* str) {
    const size_t len = strlen(str);

    if (len == 0 || (len == 1 && str[0] == '.')) {
        fprintf(stderr, "missing sentence\n");
        return false;
    }

    for (size_t i = 0; i < len; i++) {
        /* アルファベット、スペース、ピリオドから構成されていないとき、strを文として認めない */
        if (!(isalpha(str[i]) || strchr(" .", str[i]))) {
            fprintf(stderr, "invalid sentence that contains non-alphabetic characters.\n");
            return false;
        }
        /* ピリオドを丁度1つだけ含み、それが文末にあるとき以外は、strを文として認めない */
        if (str[i] == '.' && i != len - 1) {
            fprintf(stderr, "up to 1 sentence\n");
            return false;
        }
    }

    return true;
}
