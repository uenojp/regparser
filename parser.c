#include "regparser.h"

int parser_init(parser_t** p, const char* dict_path, const char* rules_path) {
    *p = malloc(sizeof(parser_t));
    if (*p == NULL) {
        perror("parser_init: malloc: ");
        return 1;
    }

    if (dict_load(&((*p)->dict), dict_path) != 0)
        return 1;
    if (rule_load((*p)->rules, rules_path) != 0)
        return 1;

    return 0;
}

int parser_parse(parser_t* p, const char* sentence) {
    if (!is_sentence(sentence))
        return 1;

    /* +1+1 は\0とスペース挿入用 */
    char* copy = (char*)malloc((strlen(sentence) + 1 + 1) * sizeof(char));
    if (copy == NULL) {
        perror("parser_perse: malloc:");
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
    pos = transit(p, pos, token);
    printf("(%s, %s)\n", token, to_string(pos));
    while ((token = strtok(NULL, " ")) != NULL) {
        pos = transit(p, pos, token);
        printf("(%s, %s)\n", to_string(pos), token);
    }

    return 0;
}

void parser_free(parser_t* p) {
    dict_free(p->dict);
    free(p);
}

/* 現在の状態 state と単語 word を受け取り、遷移先を返す
   (state, word) -> state */
PartOfSpeech transit(parser_t* p, PartOfSpeech state, char* word) {
    if (strcmp(word, ".") == 0) {
        return END;
    }

    PartOfSpeech pos = get_part_of_speech(p->dict, word);
    if (pos == UNKNOWN) {
        fprintf(stderr, "%s is not resisterd in dictionary\n", word);
        return UNKNOWN;
    }

    if (p->rules[state][pos])
        return pos;
    else
        return UNKNOWN;
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
            fprintf(stderr, "parser: contains non-alphabetic charactor\n");
            return false;
        }
        /* ピリオドを丁度1つだけ含み、それが文末にあるとき以外は、strを文として認めない */
        if (str[i] == '.' && i != len - 1) {
            fprintf(stderr, "parser: up to 1 sentence\n");
            return false;
        }
    }

    return true;
}
