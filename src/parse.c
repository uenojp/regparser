#include "regparser.h"

int parse(const char* sentence) {
    if (!is_sentence(sentence)) {
        fprintf(stderr, "invalid sentence\n");
        return 1;
    }

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
    if (pos == UNKNOWN) {
        fprintf(stderr, "invalid rule applied to %s\n", token);
        free(copy);
        return 1;
    }
    printf("(%s, %s)\n", token, to_string(pos));
    while ((token = strtok(NULL, " ")) != NULL) {
        pos = transit(pos, token);
        if (pos == UNKNOWN) {
            fprintf(stderr, "invalid rule applied to %s\n", token);
            free(copy);
            return 1;
        }
        printf("(%s, %s)\n", token, to_string(pos));
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

    return has_rule(state, pos) ? pos : UNKNOWN;
}

/* strが文であるか確認する
   ここで "文 \in [A-Za-z ]+\. */
bool is_sentence(const char* str) {
    const size_t len = strlen(str);

    if (len == 0 || (len == 1 && str[0] == '.'))
        return false;

    for (size_t i = 0; i < len; i++) {
        /* アルファベット、スペース、ピリオドから構成されていないとき、strを文として認めない */
        if (!(isalpha(str[i]) || strchr(" .", str[i])))
            return false;

        /* ピリオドを丁度1つだけ含み、それが文末にあるとき以外は、strを文として認めない */
        if (str[i] == '.' && i != len - 1)
            return false;
    }

    return true;
}
