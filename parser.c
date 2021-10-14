#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "type.h"

/* 単語の品詞を返す */
/* TODO: dictをより分離して、管理しやすいように。
    選択肢としては、
    - hashmap的なデータ構造をとる(標準にはない)
        - 自作は辛そう
        - 実質アクセスO(1)
    - テキストファイルとして保持して、パース時にそこから読む
        - string -> enum の変換が必要
        - 実装楽だがO(n) */
PartOfSpeech dictionary(const char* word) {
    WordPos dict[7] = {{"the", DET}, {"child", NOUN}, {"runs", VERB}, {"quickly", ADV}, {"to", PREP}, {"large", ADJ}, {"house", NOUN}};
    for (size_t i = 0; i < 7; i++) {
        WordPos wp = dict[i];
        if (strcmp(word, wp.word) == 0)
            return wp.pos;
    }
    return UNKNOWN;
}

/* 現在の状態 state と単語 word を受け取り、遷移先を返す
   (state, word) -> state */
PartOfSpeech transit(PartOfSpeech state, const char* word) {
    if (strcmp(word, ".") == 0) {
        return END;
    }

    PartOfSpeech pos = dictionary(word);
    if (pos == UNKNOWN) {
        fprintf(stderr, "%s is not resisterd in dictionary\n", word);
        return UNKNOWN;
    }

    switch (state) {
        case START:
            switch (pos) {
                case DET:
                case NOUN:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case DET:
            switch (pos) {
                case NOUN:
                case ADJ:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case NOUN:
            switch (pos) {
                case PREP:
                case VERB:
                case ADV:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case ADJ:
            switch (pos) {
                case NOUN:
                    return NOUN;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case PREP:
            switch (pos) {
                case NOUN:
                case ADJ:
                case DET:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case ADV:
            switch (pos) {
                case PREP:
                case NOUN:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case VERB:
            switch (pos) {
                case DET:
                case ADV:
                    return pos;
                default:
                    fprintf(stderr, "no such transition\n");
                    return UNKNOWN;
            }
        case END:
            fprintf(stderr, "up to 1 sentence\n");
            return UNKNOWN;
        default:
            fprintf(stderr, "unreachable case\n");
            return UNKNOWN;
    }
}
